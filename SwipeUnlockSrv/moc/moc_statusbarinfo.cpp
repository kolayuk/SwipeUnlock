/****************************************************************************
** Meta object code from reading C++ file 'statusbarinfo.h'
**
** Created: Sat 22. Dec 15:01:50 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../statusbarinfo.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'statusbarinfo.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_StatusBarInfo[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x0a,
      72,   58,   14,   14, 0x0a,
     136,  131,   14,   14, 0x0a,
     166,  160,   14,   14, 0x0a,
     218,  213,   14,   14, 0x0a,
     280,  270,   14,   14, 0x0a,
     344,  340,   14,   14, 0x0a,
     379,  367,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_StatusBarInfo[] = {
    "StatusBarInfo\0\0"
    "profileChanged(QSystemDeviceInfo::Profile)\0"
    "mode,strength\0"
    "signalStrengthChanged(QSystemNetworkInfo::NetworkMode,int)\0"
    "bars\0batteryBarsChanged(int)\0state\0"
    "chargingChanged(QSystemDeviceInfo::PowerState)\0"
    "mode\0networkModeChanged(QSystemNetworkInfo::NetworkMode)\0"
    "mode,name\0"
    "networkNameChanged(QSystemNetworkInfo::NetworkMode,QString)\0"
    "val\0bluetoothChanged(bool)\0mode,status\0"
    "stateChanged(QSystemNetworkInfo::NetworkMode,QSystemNetworkInfo::Netwo"
    "rkStatus)\0"
};

const QMetaObject StatusBarInfo::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_StatusBarInfo,
      qt_meta_data_StatusBarInfo, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &StatusBarInfo::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *StatusBarInfo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *StatusBarInfo::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_StatusBarInfo))
        return static_cast<void*>(const_cast< StatusBarInfo*>(this));
    if (!strcmp(_clname, "MOperatorObserver"))
        return static_cast< MOperatorObserver*>(const_cast< StatusBarInfo*>(this));
    return QObject::qt_metacast(_clname);
}

int StatusBarInfo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: profileChanged((*reinterpret_cast< QSystemDeviceInfo::Profile(*)>(_a[1]))); break;
        case 1: signalStrengthChanged((*reinterpret_cast< QSystemNetworkInfo::NetworkMode(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: batteryBarsChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: chargingChanged((*reinterpret_cast< QSystemDeviceInfo::PowerState(*)>(_a[1]))); break;
        case 4: networkModeChanged((*reinterpret_cast< QSystemNetworkInfo::NetworkMode(*)>(_a[1]))); break;
        case 5: networkNameChanged((*reinterpret_cast< QSystemNetworkInfo::NetworkMode(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 6: bluetoothChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: stateChanged((*reinterpret_cast< QSystemNetworkInfo::NetworkMode(*)>(_a[1])),(*reinterpret_cast< QSystemNetworkInfo::NetworkStatus(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
