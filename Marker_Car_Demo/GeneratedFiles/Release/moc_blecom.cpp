/****************************************************************************
** Meta object code from reading C++ file 'blecom.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../blecom.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'blecom.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BLECom_t {
    QByteArrayData data[35];
    char stringdata0[521];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BLECom_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BLECom_t qt_meta_stringdata_BLECom = {
    {
QT_MOC_LITERAL(0, 0, 6), // "BLECom"
QT_MOC_LITERAL(1, 7, 13), // "devDiscovered"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 4), // "info"
QT_MOC_LITERAL(4, 27, 15), // "devScanFinished"
QT_MOC_LITERAL(5, 43, 15), // "devDisconnected"
QT_MOC_LITERAL(6, 59, 12), // "devConnected"
QT_MOC_LITERAL(7, 72, 5), // "error"
QT_MOC_LITERAL(8, 78, 9), // "dataReady"
QT_MOC_LITERAL(9, 88, 4), // "data"
QT_MOC_LITERAL(10, 93, 7), // "devScan"
QT_MOC_LITERAL(11, 101, 10), // "devConnect"
QT_MOC_LITERAL(12, 112, 3), // "dev"
QT_MOC_LITERAL(13, 116, 7), // "srvUuid"
QT_MOC_LITERAL(14, 124, 8), // "charUuid"
QT_MOC_LITERAL(15, 133, 13), // "devDisconnect"
QT_MOC_LITERAL(16, 147, 9), // "writeData"
QT_MOC_LITERAL(17, 157, 17), // "devScanAgentError"
QT_MOC_LITERAL(18, 175, 37), // "QBluetoothDeviceDiscoveryAgen..."
QT_MOC_LITERAL(19, 213, 8), // "newError"
QT_MOC_LITERAL(20, 222, 17), // "devScanDiscovered"
QT_MOC_LITERAL(21, 240, 20), // "QBluetoothDeviceInfo"
QT_MOC_LITERAL(22, 261, 20), // "devLeControllerError"
QT_MOC_LITERAL(23, 282, 27), // "QLowEnergyController::Error"
QT_MOC_LITERAL(24, 310, 24), // "devLeControllerConnected"
QT_MOC_LITERAL(25, 335, 21), // "devLeServerDiscovered"
QT_MOC_LITERAL(26, 357, 16), // "devLeServerError"
QT_MOC_LITERAL(27, 374, 31), // "QLowEnergyService::ServiceError"
QT_MOC_LITERAL(28, 406, 14), // "devLeCharReady"
QT_MOC_LITERAL(29, 421, 31), // "QLowEnergyService::ServiceState"
QT_MOC_LITERAL(30, 453, 8), // "newState"
QT_MOC_LITERAL(31, 462, 12), // "devDataReady"
QT_MOC_LITERAL(32, 475, 24), // "QLowEnergyCharacteristic"
QT_MOC_LITERAL(33, 500, 14), // "characteristic"
QT_MOC_LITERAL(34, 515, 5) // "value"

    },
    "BLECom\0devDiscovered\0\0info\0devScanFinished\0"
    "devDisconnected\0devConnected\0error\0"
    "dataReady\0data\0devScan\0devConnect\0dev\0"
    "srvUuid\0charUuid\0devDisconnect\0writeData\0"
    "devScanAgentError\0"
    "QBluetoothDeviceDiscoveryAgent::Error\0"
    "newError\0devScanDiscovered\0"
    "QBluetoothDeviceInfo\0devLeControllerError\0"
    "QLowEnergyController::Error\0"
    "devLeControllerConnected\0devLeServerDiscovered\0"
    "devLeServerError\0QLowEnergyService::ServiceError\0"
    "devLeCharReady\0QLowEnergyService::ServiceState\0"
    "newState\0devDataReady\0QLowEnergyCharacteristic\0"
    "characteristic\0value"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BLECom[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  104,    2, 0x06 /* Public */,
       4,    0,  107,    2, 0x06 /* Public */,
       5,    0,  108,    2, 0x06 /* Public */,
       6,    0,  109,    2, 0x06 /* Public */,
       7,    1,  110,    2, 0x06 /* Public */,
       8,    1,  113,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,  116,    2, 0x0a /* Public */,
      11,    3,  117,    2, 0x0a /* Public */,
      15,    0,  124,    2, 0x0a /* Public */,
      16,    1,  125,    2, 0x0a /* Public */,
      17,    1,  128,    2, 0x08 /* Private */,
      20,    1,  131,    2, 0x08 /* Private */,
      22,    1,  134,    2, 0x08 /* Private */,
      24,    0,  137,    2, 0x08 /* Private */,
      25,    0,  138,    2, 0x08 /* Private */,
      26,    1,  139,    2, 0x08 /* Private */,
      28,    1,  142,    2, 0x08 /* Private */,
      31,    2,  145,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QByteArray,    9,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   12,   13,   14,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    9,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void, 0x80000000 | 21,   12,
    QMetaType::Void, 0x80000000 | 23,   19,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 27,   19,
    QMetaType::Void, 0x80000000 | 29,   30,
    QMetaType::Void, 0x80000000 | 32, QMetaType::QByteArray,   33,   34,

       0        // eod
};

void BLECom::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BLECom *_t = static_cast<BLECom *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->devDiscovered((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->devScanFinished(); break;
        case 2: _t->devDisconnected(); break;
        case 3: _t->devConnected(); break;
        case 4: _t->error((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->dataReady((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 6: _t->devScan(); break;
        case 7: _t->devConnect((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 8: _t->devDisconnect(); break;
        case 9: _t->writeData((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 10: _t->devScanAgentError((*reinterpret_cast< QBluetoothDeviceDiscoveryAgent::Error(*)>(_a[1]))); break;
        case 11: _t->devScanDiscovered((*reinterpret_cast< const QBluetoothDeviceInfo(*)>(_a[1]))); break;
        case 12: _t->devLeControllerError((*reinterpret_cast< QLowEnergyController::Error(*)>(_a[1]))); break;
        case 13: _t->devLeControllerConnected(); break;
        case 14: _t->devLeServerDiscovered(); break;
        case 15: _t->devLeServerError((*reinterpret_cast< QLowEnergyService::ServiceError(*)>(_a[1]))); break;
        case 16: _t->devLeCharReady((*reinterpret_cast< QLowEnergyService::ServiceState(*)>(_a[1]))); break;
        case 17: _t->devDataReady((*reinterpret_cast< const QLowEnergyCharacteristic(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QBluetoothDeviceInfo >(); break;
            }
            break;
        case 12:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QLowEnergyController::Error >(); break;
            }
            break;
        case 15:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QLowEnergyService::ServiceError >(); break;
            }
            break;
        case 16:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QLowEnergyService::ServiceState >(); break;
            }
            break;
        case 17:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QLowEnergyCharacteristic >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (BLECom::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BLECom::devDiscovered)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (BLECom::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BLECom::devScanFinished)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (BLECom::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BLECom::devDisconnected)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (BLECom::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BLECom::devConnected)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (BLECom::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BLECom::error)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (BLECom::*)(const QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BLECom::dataReady)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject BLECom::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_BLECom.data,
    qt_meta_data_BLECom,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *BLECom::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BLECom::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BLECom.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int BLECom::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void BLECom::devDiscovered(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void BLECom::devScanFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void BLECom::devDisconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void BLECom::devConnected()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void BLECom::error(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void BLECom::dataReady(const QByteArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
