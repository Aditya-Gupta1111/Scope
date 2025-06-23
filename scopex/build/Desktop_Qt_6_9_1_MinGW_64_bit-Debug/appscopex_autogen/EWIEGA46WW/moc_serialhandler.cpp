/****************************************************************************
** Meta object code from reading C++ file 'serialhandler.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../serialhandler.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serialhandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN13SerialHandlerE_t {};
} // unnamed namespace

template <> constexpr inline auto SerialHandler::qt_create_metaobjectdata<qt_meta_tag_ZN13SerialHandlerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "SerialHandler",
        "QML.Element",
        "auto",
        "QML.Singleton",
        "true",
        "portsChanged",
        "",
        "connectionChanged",
        "statusChanged",
        "message",
        "dataReceived",
        "QVariantList",
        "ch1Data",
        "ch2Data",
        "dftCalculated",
        "dftData",
        "digitalInputsChanged",
        "inputs",
        "refreshPorts",
        "connectToPort",
        "portName",
        "disconnectPort",
        "setupScope",
        "triggerMode",
        "triggerPolarity",
        "displayMode",
        "ch1Gain",
        "ch2Gain",
        "ch1Offset",
        "ch2Offset",
        "triggerLevel",
        "sampleRate",
        "runCapture",
        "continuous",
        "stopCapture",
        "abortOperation",
        "setDDSWaveform",
        "type",
        "setDDSFrequency",
        "frequency",
        "runDDS",
        "stopDDS",
        "loadArbitraryWaveform",
        "QList<quint8>",
        "data",
        "setDigitalOutputs",
        "outputs",
        "readDigitalInputs",
        "startSweep",
        "startFreq",
        "endFreq",
        "steps",
        "delayMs",
        "stopSweep",
        "handleReadyRead",
        "handleError",
        "QSerialPort::SerialPortError",
        "error",
        "availablePorts",
        "connected",
        "statusMessage",
        "WaveformType",
        "SineWave",
        "SquareWave",
        "TriangleWave",
        "RampUpWave",
        "RampDownWave",
        "ArbitraryWave"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'portsChanged'
        QtMocHelpers::SignalData<void()>(5, 6, QMC::AccessPublic, QMetaType::Void),
        // Signal 'connectionChanged'
        QtMocHelpers::SignalData<void()>(7, 6, QMC::AccessPublic, QMetaType::Void),
        // Signal 'statusChanged'
        QtMocHelpers::SignalData<void(const QString &)>(8, 6, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 9 },
        }}),
        // Signal 'dataReceived'
        QtMocHelpers::SignalData<void(const QVariantList &, const QVariantList &)>(10, 6, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 11, 12 }, { 0x80000000 | 11, 13 },
        }}),
        // Signal 'dftCalculated'
        QtMocHelpers::SignalData<void(const QVariantList &)>(14, 6, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 11, 15 },
        }}),
        // Signal 'digitalInputsChanged'
        QtMocHelpers::SignalData<void(quint8)>(16, 6, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UChar, 17 },
        }}),
        // Slot 'refreshPorts'
        QtMocHelpers::SlotData<void()>(18, 6, QMC::AccessPublic, QMetaType::Void),
        // Slot 'connectToPort'
        QtMocHelpers::SlotData<bool(const QString &)>(19, 6, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 20 },
        }}),
        // Slot 'disconnectPort'
        QtMocHelpers::SlotData<void()>(21, 6, QMC::AccessPublic, QMetaType::Void),
        // Slot 'setupScope'
        QtMocHelpers::SlotData<void(int, int, int, double, double, int, int, int, int)>(22, 6, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 23 }, { QMetaType::Int, 24 }, { QMetaType::Int, 25 }, { QMetaType::Double, 26 },
            { QMetaType::Double, 27 }, { QMetaType::Int, 28 }, { QMetaType::Int, 29 }, { QMetaType::Int, 30 },
            { QMetaType::Int, 31 },
        }}),
        // Slot 'runCapture'
        QtMocHelpers::SlotData<void(bool)>(32, 6, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 33 },
        }}),
        // Slot 'stopCapture'
        QtMocHelpers::SlotData<void()>(34, 6, QMC::AccessPublic, QMetaType::Void),
        // Slot 'abortOperation'
        QtMocHelpers::SlotData<void()>(35, 6, QMC::AccessPublic, QMetaType::Void),
        // Slot 'setDDSWaveform'
        QtMocHelpers::SlotData<void(int)>(36, 6, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 37 },
        }}),
        // Slot 'setDDSFrequency'
        QtMocHelpers::SlotData<void(double)>(38, 6, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 39 },
        }}),
        // Slot 'runDDS'
        QtMocHelpers::SlotData<void()>(40, 6, QMC::AccessPublic, QMetaType::Void),
        // Slot 'stopDDS'
        QtMocHelpers::SlotData<void()>(41, 6, QMC::AccessPublic, QMetaType::Void),
        // Slot 'loadArbitraryWaveform'
        QtMocHelpers::SlotData<void(const QVector<quint8> &)>(42, 6, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 43, 44 },
        }}),
        // Slot 'setDigitalOutputs'
        QtMocHelpers::SlotData<void(quint8)>(45, 6, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UChar, 46 },
        }}),
        // Slot 'readDigitalInputs'
        QtMocHelpers::SlotData<quint8()>(47, 6, QMC::AccessPublic, QMetaType::UChar),
        // Slot 'startSweep'
        QtMocHelpers::SlotData<void(double, double, int, int)>(48, 6, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 49 }, { QMetaType::Double, 50 }, { QMetaType::Int, 51 }, { QMetaType::Int, 52 },
        }}),
        // Slot 'stopSweep'
        QtMocHelpers::SlotData<void()>(53, 6, QMC::AccessPublic, QMetaType::Void),
        // Slot 'handleReadyRead'
        QtMocHelpers::SlotData<void()>(54, 6, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'handleError'
        QtMocHelpers::SlotData<void(QSerialPort::SerialPortError)>(55, 6, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 56, 57 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'availablePorts'
        QtMocHelpers::PropertyData<QStringList>(58, QMetaType::QStringList, QMC::DefaultPropertyFlags, 0),
        // property 'connected'
        QtMocHelpers::PropertyData<bool>(59, QMetaType::Bool, QMC::DefaultPropertyFlags, 1),
        // property 'statusMessage'
        QtMocHelpers::PropertyData<QString>(60, QMetaType::QString, QMC::DefaultPropertyFlags, 2),
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'WaveformType'
        QtMocHelpers::EnumData<WaveformType>(61, 61, QMC::EnumFlags{}).add({
            {   62, WaveformType::SineWave },
            {   63, WaveformType::SquareWave },
            {   64, WaveformType::TriangleWave },
            {   65, WaveformType::RampUpWave },
            {   66, WaveformType::RampDownWave },
            {   67, WaveformType::ArbitraryWave },
        }),
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
            {    3,    4 },
    });
    return QtMocHelpers::metaObjectData<SerialHandler, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject SerialHandler::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13SerialHandlerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13SerialHandlerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13SerialHandlerE_t>.metaTypes,
    nullptr
} };

void SerialHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<SerialHandler *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->portsChanged(); break;
        case 1: _t->connectionChanged(); break;
        case 2: _t->statusChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->dataReceived((*reinterpret_cast< std::add_pointer_t<QVariantList>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QVariantList>>(_a[2]))); break;
        case 4: _t->dftCalculated((*reinterpret_cast< std::add_pointer_t<QVariantList>>(_a[1]))); break;
        case 5: _t->digitalInputsChanged((*reinterpret_cast< std::add_pointer_t<quint8>>(_a[1]))); break;
        case 6: _t->refreshPorts(); break;
        case 7: { bool _r = _t->connectToPort((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->disconnectPort(); break;
        case 9: _t->setupScope((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[6])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[7])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[8])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[9]))); break;
        case 10: _t->runCapture((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 11: _t->stopCapture(); break;
        case 12: _t->abortOperation(); break;
        case 13: _t->setDDSWaveform((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 14: _t->setDDSFrequency((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 15: _t->runDDS(); break;
        case 16: _t->stopDDS(); break;
        case 17: _t->loadArbitraryWaveform((*reinterpret_cast< std::add_pointer_t<QList<quint8>>>(_a[1]))); break;
        case 18: _t->setDigitalOutputs((*reinterpret_cast< std::add_pointer_t<quint8>>(_a[1]))); break;
        case 19: { quint8 _r = _t->readDigitalInputs();
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 20: _t->startSweep((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4]))); break;
        case 21: _t->stopSweep(); break;
        case 22: _t->handleReadyRead(); break;
        case 23: _t->handleError((*reinterpret_cast< std::add_pointer_t<QSerialPort::SerialPortError>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 17:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<quint8> >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (SerialHandler::*)()>(_a, &SerialHandler::portsChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (SerialHandler::*)()>(_a, &SerialHandler::connectionChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (SerialHandler::*)(const QString & )>(_a, &SerialHandler::statusChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (SerialHandler::*)(const QVariantList & , const QVariantList & )>(_a, &SerialHandler::dataReceived, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (SerialHandler::*)(const QVariantList & )>(_a, &SerialHandler::dftCalculated, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (SerialHandler::*)(quint8 )>(_a, &SerialHandler::digitalInputsChanged, 5))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QStringList*>(_v) = _t->availablePorts(); break;
        case 1: *reinterpret_cast<bool*>(_v) = _t->connected(); break;
        case 2: *reinterpret_cast<QString*>(_v) = _t->statusMessage(); break;
        default: break;
        }
    }
}

const QMetaObject *SerialHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SerialHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13SerialHandlerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SerialHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void SerialHandler::portsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SerialHandler::connectionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void SerialHandler::statusChanged(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void SerialHandler::dataReceived(const QVariantList & _t1, const QVariantList & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1, _t2);
}

// SIGNAL 4
void SerialHandler::dftCalculated(const QVariantList & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}

// SIGNAL 5
void SerialHandler::digitalInputsChanged(quint8 _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}
QT_WARNING_POP
