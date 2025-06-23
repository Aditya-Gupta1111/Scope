#ifndef SERIALHANDLER_H
#define SERIALHANDLER_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QVector>
#include <QPointF>
#include <QStringList>
#include <QQmlEngine>

class SerialHandler : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    Q_PROPERTY(QStringList availablePorts READ availablePorts NOTIFY portsChanged)
    Q_PROPERTY(bool connected READ connected NOTIFY connectionChanged)
    Q_PROPERTY(QString statusMessage READ statusMessage NOTIFY statusChanged)

public:
    explicit SerialHandler(QObject *parent = nullptr);
    ~SerialHandler();

    QStringList availablePorts() const;
    bool connected() const;
    QString statusMessage() const;

    enum WaveformType {
        SineWave = 0,
        SquareWave = 1,
        TriangleWave = 2,
        RampUpWave = 3,
        RampDownWave = 4,
        ArbitraryWave = 5
    };
    Q_ENUM(WaveformType)

public slots:
    void refreshPorts();
    bool connectToPort(const QString &portName);
    void disconnectPort();
    void setupScope(int triggerMode, int triggerPolarity, int displayMode,
                    double ch1Gain, double ch2Gain, int ch1Offset, int ch2Offset,
                    int triggerLevel, int sampleRate);
    void runCapture(bool continuous);
    void stopCapture();
    void abortOperation();
    void setDDSWaveform(int type);
    void setDDSFrequency(double frequency);
    void runDDS();
    void stopDDS();
    void loadArbitraryWaveform(const QVector<quint8> &data);
    void setDigitalOutputs(quint8 outputs);
    quint8 readDigitalInputs();
    void startSweep(double startFreq, double endFreq, int steps, int delayMs);
    void stopSweep();

signals:
    void portsChanged();
    void connectionChanged();
    void statusChanged(const QString &message);
    void dataReceived(const QVariantList &ch1Data, const QVariantList &ch2Data);
    void dftCalculated(const QVariantList &dftData);
    void digitalInputsChanged(quint8 inputs);

private slots:
    void handleReadyRead();
    void handleError(QSerialPort::SerialPortError error);

private:
    QSerialPort *m_serial;
    QString m_statusMessage;
    bool m_connected;

    QVector<quint8> m_waveformTable;
    QVector<quint8> m_sineTable;
    QVector<quint8> m_squareTable;
    QVector<quint8> m_triangleTable;
    QVector<quint8> m_rampUpTable;
    QVector<quint8> m_rampDownTable;

    void processIncomingData(const QByteArray &data);
    void calculateDFT(const QVector<QPointF> &timeData);
    quint16 calculatePhaseStep(double frequency, quint32 clockFrequency);
    void sendCommand(const QByteArray &command);
    void initializeWaveformTables();
    void generateTestData();

    // Helper functions to convert between QVector<QPointF> and QVariantList
    QVariantList pointsToVariantList(const QVector<QPointF> &points);
    QVector<QPointF> variantListToPoints(const QVariantList &list);
};

#endif // SERIALHANDLER_H
