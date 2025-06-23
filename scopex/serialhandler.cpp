#include "serialhandler.h"
#include <QDebug>
#include <QtMath>
#include <QTimer>
#include <QThread>

SerialHandler::SerialHandler(QObject *parent) : QObject(parent),
    m_serial(new QSerialPort(this)),
    m_connected(false),
    m_statusMessage("Ready")
{
    initializeWaveformTables();
    connect(m_serial, &QSerialPort::readyRead, this, &SerialHandler::handleReadyRead);
    connect(m_serial, QOverload<QSerialPort::SerialPortError>::of(&QSerialPort::errorOccurred),
            this, &SerialHandler::handleError);
}

SerialHandler::~SerialHandler()
{
    disconnectPort();
}

void SerialHandler::initializeWaveformTables()
{
    // Initialize sine table (256 values)
    m_sineTable.resize(256);
    for (int i = 0; i < 256; ++i) {
        m_sineTable[i] = static_cast<quint8>(127.5 * (1 + qSin(2 * M_PI * i / 256)));
    }

    // Initialize square table
    m_squareTable.resize(256);
    for (int i = 0; i < 128; ++i) {
        m_squareTable[i] = 5;
        m_squareTable[i+128] = 250;
    }

    // Initialize triangle table
    m_triangleTable.resize(256);
    for (int i = 0; i < 128; ++i) {
        m_triangleTable[i] = static_cast<quint8>(5 + (245 * i / 127));
        m_triangleTable[255-i] = static_cast<quint8>(5 + (245 * i / 127));
    }

    // Initialize ramp up table
    m_rampUpTable.resize(256);
    for (int i = 0; i < 256; ++i) {
        m_rampUpTable[i] = static_cast<quint8>(5 + (250 * i / 255));
    }

    // Initialize ramp down table
    m_rampDownTable.resize(256);
    for (int i = 0; i < 256; ++i) {
        m_rampDownTable[i] = static_cast<quint8>(250 - (250 * i / 255));
    }

    // Default to sine wave
    m_waveformTable = m_sineTable;
}

QStringList SerialHandler::availablePorts() const
{
    QStringList ports;
    const QList<QSerialPortInfo> portInfos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : portInfos) {
        ports.append(info.portName());
    }
    return ports;
}

bool SerialHandler::connected() const
{
    return m_connected;
}

QString SerialHandler::statusMessage() const
{
    return m_statusMessage;
}

void SerialHandler::refreshPorts()
{
    emit portsChanged();
}

bool SerialHandler::connectToPort(const QString &portName)
{
    if (m_connected) {
        disconnectPort();
    }

    m_serial->setPortName(portName);
    m_serial->setBaudRate(QSerialPort::Baud115200);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);

    if (m_serial->open(QIODevice::ReadWrite)) {
        m_connected = true;
        m_statusMessage = tr("Connected to %1").arg(portName);
        emit connectionChanged();
        emit statusChanged(m_statusMessage);
        return true;
    } else {
        m_statusMessage = tr("Error: %1").arg(m_serial->errorString());
        emit statusChanged(m_statusMessage);
        return false;
    }
}

void SerialHandler::disconnectPort()
{
    if (m_serial->isOpen()) {
        m_serial->close();
    }
    m_connected = false;
    m_statusMessage = tr("Disconnected");
    emit connectionChanged();
    emit statusChanged(m_statusMessage);
}

void SerialHandler::setupScope(int triggerMode, int triggerPolarity, int displayMode,
                               double ch1Gain, double ch2Gain, int ch1Offset, int ch2Offset,
                               int triggerLevel, int sampleRate)
{
    if (!m_connected) return;

    // Convert gains to command values (0-5)
    int ch1GainCmd = 1; // Default to 1x
    if (ch1Gain == 0.5) ch1GainCmd = 0;
    else if (ch1Gain == 1.0) ch1GainCmd = 1;
    else if (ch1Gain == 2.0) ch1GainCmd = 2;
    else if (ch1Gain == 4.0) ch1GainCmd = 3;
    else if (ch1Gain == 8.0) ch1GainCmd = 4;
    else if (ch1Gain == 16.0) ch1GainCmd = 5;

    int ch2GainCmd = 1; // Default to 1x
    if (ch2Gain == 0.5) ch2GainCmd = 0;
    else if (ch2Gain == 1.0) ch2GainCmd = 1;
    else if (ch2Gain == 2.0) ch2GainCmd = 2;
    else if (ch2Gain == 4.0) ch2GainCmd = 3;
    else if (ch2Gain == 8.0) ch2GainCmd = 4;
    else if (ch2Gain == 16.0) ch2GainCmd = 5;

    // Set trigger mode (T command)
    QByteArray trigCmd;
    trigCmd.append(0x54); // 'T'
    trigCmd.append(static_cast<char>(triggerMode));
    trigCmd.append(static_cast<char>(0x00));
    sendCommand(trigCmd);

    // Set trigger polarity (P command)
    QByteArray polarityCmd;
    polarityCmd.append(0x50); // 'P'
    polarityCmd.append(static_cast<char>(triggerPolarity));
    polarityCmd.append(static_cast<char>(0x00));
    sendCommand(polarityCmd);

    // Set display mode (F command)
    QByteArray modeCmd;
    modeCmd.append(0x46); // 'F'
    modeCmd.append(static_cast<char>(displayMode));
    modeCmd.append(static_cast<char>(0x00));
    sendCommand(modeCmd);

    // Set gains (G command)
    QByteArray gainCmd;
    gainCmd.append(0x47); // 'G'
    gainCmd.append(static_cast<char>(0x00)); // CH1
    gainCmd.append(static_cast<char>(ch1GainCmd));
    sendCommand(gainCmd);

    gainCmd[1] = static_cast<char>(0x01); // CH2
    gainCmd[2] = static_cast<char>(ch2GainCmd);
    sendCommand(gainCmd);

    // Set offsets (O and o commands)
    QByteArray offsetCmd;
    offsetCmd.append(0x4F); // 'O' for CH1
    offsetCmd.append(static_cast<char>((ch1Offset >> 8) & 0xFF));
    offsetCmd.append(static_cast<char>(ch1Offset & 0xFF));
    sendCommand(offsetCmd);

    offsetCmd[0] = 0x6F; // 'o' for CH2
    offsetCmd[1] = static_cast<char>((ch2Offset >> 8) & 0xFF);
    offsetCmd[2] = static_cast<char>(ch2Offset & 0xFF);
    sendCommand(offsetCmd);

    // Set trigger level (L command)
    QByteArray trigLevelCmd;
    trigLevelCmd.append(0x4C); // 'L'
    trigLevelCmd.append(static_cast<char>((triggerLevel >> 8) & 0xFF));
    trigLevelCmd.append(static_cast<char>(triggerLevel & 0xFF));
    sendCommand(trigLevelCmd);

    // Set sample rate (S command)
    QByteArray sampleRateCmd;
    sampleRateCmd.append(0x53); // 'S'
    sampleRateCmd.append(static_cast<char>(sampleRate));
    sampleRateCmd.append(static_cast<char>(0x00));
    sendCommand(sampleRateCmd);
}

void SerialHandler::runCapture(bool continuous)
{
    if (!m_connected) {
        // Generate some test data for demonstration
        generateTestData();
        return;
    }

    QByteArray captureCmd;
    captureCmd.append(0x43); // 'C'
    captureCmd.append(static_cast<char>(continuous ? 0x01 : 0x00));
    captureCmd.append(static_cast<char>(0x00));
    sendCommand(captureCmd);
}

void SerialHandler::stopCapture()
{
    if (!m_connected) return;

    QByteArray stopCmd;
    stopCmd.append(0x41); // 'A'
    stopCmd.append(static_cast<char>(0x00));
    stopCmd.append(static_cast<char>(0x00));
    sendCommand(stopCmd);
}

void SerialHandler::abortOperation()
{
    stopCapture();
    stopDDS();
    stopSweep();
}

void SerialHandler::setDDSWaveform(int type)
{
    WaveformType waveType = static_cast<WaveformType>(type);

    switch (waveType) {
    case SineWave:
        m_waveformTable = m_sineTable;
        break;
    case SquareWave:
        m_waveformTable = m_squareTable;
        break;
    case TriangleWave:
        m_waveformTable = m_triangleTable;
        break;
    case RampUpWave:
        m_waveformTable = m_rampUpTable;
        break;
    case RampDownWave:
        m_waveformTable = m_rampDownTable;
        break;
    case ArbitraryWave:
        // Use already loaded waveform
        break;
    default:
        m_waveformTable = m_sineTable;
        break;
    }

    m_statusMessage = tr("Waveform set to type %1").arg(type);
    emit statusChanged(m_statusMessage);
}

void SerialHandler::setDDSFrequency(double frequency)
{
    if (frequency <= 0) return;

    if (!m_connected) {
        m_statusMessage = tr("Frequency set to %1 Hz (not connected)").arg(frequency);
        emit statusChanged(m_statusMessage);
        return;
    }

    // Calculate timer period and phase step
    const quint32 systemClock = 32000000; // 32 MHz
    quint16 divider = 1;
    quint32 effectiveClock = systemClock / divider;
    quint16 phaseStep = calculatePhaseStep(frequency, effectiveClock);

    // Find optimal divider
    while (phaseStep < 256 && divider < 1024) {
        divider *= 2;
        effectiveClock = systemClock / divider;
        phaseStep = calculatePhaseStep(frequency, effectiveClock);
    }

    // Calculate actual frequency
    double actualFreq = (phaseStep * effectiveClock) / 65536.0;

    // Send timer period command
    QByteArray periodCmd;
    periodCmd.append(0x70); // 'p'
    periodCmd.append(static_cast<char>((divider >> 8) & 0xFF));
    periodCmd.append(static_cast<char>(divider & 0xFF));
    sendCommand(periodCmd);

    // Send phase step command
    QByteArray phaseCmd;
    phaseCmd.append(0x4E); // 'N'
    phaseCmd.append(static_cast<char>((phaseStep >> 8) & 0xFF));
    phaseCmd.append(static_cast<char>(phaseStep & 0xFF));
    sendCommand(phaseCmd);

    m_statusMessage = tr("Set frequency to %1 Hz").arg(actualFreq);
    emit statusChanged(m_statusMessage);
}

quint16 SerialHandler::calculatePhaseStep(double frequency, quint32 clockFrequency)
{
    if (clockFrequency == 0) return 0;
    return static_cast<quint16>((frequency * 65536) / clockFrequency);
}

void SerialHandler::runDDS()
{
    if (!m_connected) {
        m_statusMessage = "DDS started (not connected)";
        emit statusChanged(m_statusMessage);
        return;
    }

    // First send the waveform data
    QByteArray waveformCmd;
    waveformCmd.append(0x72); // 'r'
    waveformCmd.append(static_cast<char>(m_waveformTable.size()));
    waveformCmd.append(static_cast<char>(0x00));
    for (const quint8 &value : m_waveformTable) {
        waveformCmd.append(static_cast<char>(value));
    }
    sendCommand(waveformCmd);

    // Then start DDS
    QByteArray runCmd;
    runCmd.append(0x66); // 'f'
    runCmd.append(static_cast<char>(0x00));
    runCmd.append(static_cast<char>(0x00));
    sendCommand(runCmd);

    m_statusMessage = "DDS started";
    emit statusChanged(m_statusMessage);
}

void SerialHandler::stopDDS()
{
    if (!m_connected) return;

    QByteArray stopCmd;
    stopCmd.append(0x41); // 'A' for abort
    stopCmd.append(static_cast<char>(0x00));
    stopCmd.append(static_cast<char>(0x00));
    sendCommand(stopCmd);

    m_statusMessage = "DDS stopped";
    emit statusChanged(m_statusMessage);
}

void SerialHandler::loadArbitraryWaveform(const QVector<quint8> &data)
{
    if (data.size() <= 256) {
        m_waveformTable = data;
        m_statusMessage = tr("Arbitrary waveform loaded (%1 points)").arg(data.size());
        emit statusChanged(m_statusMessage);
    }
}

void SerialHandler::setDigitalOutputs(quint8 outputs)
{
    if (!m_connected) return;

    QByteArray digOutCmd;
    digOutCmd.append(0x68); // 'h'
    digOutCmd.append(static_cast<char>(outputs));
    digOutCmd.append(static_cast<char>(0x00));
    sendCommand(digOutCmd);
}

quint8 SerialHandler::readDigitalInputs()
{
    if (!m_connected) {
        // Return some test data
        quint8 testInputs = 0x05; // Simulate inputs 0 and 2 being high
        emit digitalInputsChanged(testInputs);
        return testInputs;
    }

    QByteArray digInCmd;
    digInCmd.append(0x69); // 'i'
    digInCmd.append(static_cast<char>(0x00));
    digInCmd.append(static_cast<char>(0x00));
    sendCommand(digInCmd);

    return 0; // Actual value comes from serial response
}

void SerialHandler::startSweep(double startFreq, double endFreq, int steps, int delayMs)
{
    if (steps <= 0) return;

    double step = (endFreq - startFreq) / steps;

    for (int i = 0; i <= steps; ++i) {
        double freq = startFreq + (i * step);
        QTimer::singleShot(i * delayMs, this, [this, freq]() {
            setDDSFrequency(freq);
            runDDS();
        });
    }

    m_statusMessage = tr("Sweep started from %1 to %2 Hz").arg(startFreq).arg(endFreq);
    emit statusChanged(m_statusMessage);
}

void SerialHandler::stopSweep()
{
    stopDDS();
    m_statusMessage = "Sweep stopped";
    emit statusChanged(m_statusMessage);
}

void SerialHandler::generateTestData()
{
    // Generate some test oscilloscope data for demonstration
    QVector<QPointF> ch1Data;
    QVector<QPointF> ch2Data;

    for (int i = 0; i < 200; i++) {
        double x = i;
        double y1 = 5.0 * qSin(2 * M_PI * i / 50.0); // 5V amplitude sine wave
        double y2 = 3.0 * qSin(2 * M_PI * i / 25.0 + M_PI/4); // 3V amplitude, phase shifted

        ch1Data.append(QPointF(x, y1));
        ch2Data.append(QPointF(x, y2));
    }

    emit dataReceived(pointsToVariantList(ch1Data), pointsToVariantList(ch2Data));
}

void SerialHandler::handleReadyRead()
{
    QByteArray data = m_serial->readAll();
    processIncomingData(data);
}

void SerialHandler::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::NoError) return;

    m_statusMessage = tr("Serial Error: %1").arg(m_serial->errorString());
    emit statusChanged(m_statusMessage);

    if (error == QSerialPort::ResourceError) {
        disconnectPort();
    }
}

void SerialHandler::processIncomingData(const QByteArray &data)
{
    if (data.isEmpty()) return;

    // Parse incoming data based on expected format
    if (data.size() >= 400) { // Assuming scope data
        QVector<QPointF> ch1Data;
        QVector<QPointF> ch2Data;

        // Parse data into points
        for (int i = 0; i < 200 && i < (data.size() / 2); i++) {
            // CH1 data (first 200 bytes)
            double x = i;
            double y = static_cast<quint8>(data[i]) * 20.0 / 255.0 - 10.0;
            ch1Data.append(QPointF(x, y));

            // CH2 data (next 200 bytes)
            if (i + 200 < data.size()) {
                y = static_cast<quint8>(data[i+200]) * 20.0 / 255.0 - 10.0;
                ch2Data.append(QPointF(x, y));
            }
        }

        emit dataReceived(pointsToVariantList(ch1Data), pointsToVariantList(ch2Data));
    } else if (data.size() == 1) { // Digital inputs response
        quint8 inputs = static_cast<quint8>(data[0]);
        emit digitalInputsChanged(inputs);
    }
}

void SerialHandler::calculateDFT(const QVector<QPointF> &timeData)
{
    if (timeData.isEmpty()) return;

    const int N = timeData.size();
    QVector<QPointF> dftData;

    // Only calculate first half of DFT (Nyquist frequency)
    for (int k = 0; k < N/2; k++) {
        double real = 0.0;
        double imag = 0.0;

        for (int n = 0; n < N; n++) {
            double angle = 2 * M_PI * k * n / N;
            real += timeData[n].y() * qCos(angle);
            imag -= timeData[n].y() * qSin(angle);
        }

        double magnitude = qSqrt(real*real + imag*imag) * 2.0 / N;
        double frequency = k * 1000.0 / N; // Assuming 1kHz sample rate
        dftData.append(QPointF(frequency, magnitude));
    }

    emit dftCalculated(pointsToVariantList(dftData));
}

void SerialHandler::sendCommand(const QByteArray &command)
{
    if (m_connected && m_serial->isOpen()) {
        qint64 bytesWritten = m_serial->write(command);
        if (bytesWritten == -1) {
            m_statusMessage = tr("Failed to write command: %1").arg(m_serial->errorString());
            emit statusChanged(m_statusMessage);
        } else {
            m_serial->waitForBytesWritten(1000);
        }
    }
}

QVariantList SerialHandler::pointsToVariantList(const QVector<QPointF> &points)
{
    QVariantList list;
    for (const QPointF &point : points) {
        QVariantMap pointMap;
        pointMap["x"] = point.x();
        pointMap["y"] = point.y();
        list.append(pointMap);
    }
    return list;
}

QVector<QPointF> SerialHandler::variantListToPoints(const QVariantList &list)
{
    QVector<QPointF> points;
    for (const QVariant &variant : list) {
        QVariantMap pointMap = variant.toMap();
        if (pointMap.contains("x") && pointMap.contains("y")) {
            points.append(QPointF(pointMap["x"].toDouble(), pointMap["y"].toDouble()));
        }
    }
    return points;
}
