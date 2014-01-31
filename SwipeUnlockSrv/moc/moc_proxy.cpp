/****************************************************************************
** Meta object code from reading C++ file 'proxy.h'
**
** Created: Tue 25. Dec 20:38:04 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../proxy.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'proxy.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Proxy[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      27,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      13,       // signalCount

 // signals: signature, parameters, type, tag, flags
       7,    6,    6,    6, 0x05,
      17,    6,    6,    6, 0x05,
      41,   35,    6,    6, 0x05,
      64,    6,    6,    6, 0x05,
      74,    6,    6,    6, 0x05,
      85,    6,    6,    6, 0x05,
      95,    6,    6,    6, 0x05,
     109,    6,    6,    6, 0x05,
     126,    6,    6,    6, 0x05,
     140,    6,    6,    6, 0x05,
     161,  157,    6,    6, 0x05,
     182,  178,    6,    6, 0x05,
     204,    6,    6,    6, 0x05,

 // slots: signature, parameters, type, tag, flags
     218,    6,    6,    6, 0x0a,
     225,    6,    6,    6, 0x0a,
     240,   35,    6,    6, 0x0a,
     260,    6,    6,    6, 0x0a,
     267,    6,    6,    6, 0x0a,
     275,    6,    6,    6, 0x0a,
     282,    6,    6,    6, 0x0a,
     293,    6,    6,    6, 0x0a,
     307,    6,    6,    6, 0x0a,
     318,    6,    6,    6, 0x0a,
     337,  332,    6,    6, 0x0a,
     353,    6,    6,    6, 0x0a,
     377,  369,    6,    6, 0x0a,
     392,    6,    6,    6, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Proxy[] = {
    "Proxy\0\0sigHide()\0sigRestartTimer()\0"
    "state\0sigMovingChanged(bool)\0sigPlay()\0"
    "sigPause()\0sigNext()\0sigPrevious()\0"
    "sigSeekForward()\0sigSeekBack()\0"
    "sigStopSeeking()\0w,h\0setSize(int,int)\0"
    "pos\0sigSeekToPercent(int)\0sigGetState()\0"
    "Hide()\0restartTimer()\0MovingChanged(bool)\0"
    "Play()\0Pause()\0Next()\0Previous()\0"
    "SeekForward()\0SeekBack()\0StopSeeking()\0"
    "type\0openViewer(int)\0screenChanged()\0"
    "percent\0SeekToPos(int)\0GetState()\0"
};

const QMetaObject Proxy::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Proxy,
      qt_meta_data_Proxy, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Proxy::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Proxy::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Proxy::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Proxy))
        return static_cast<void*>(const_cast< Proxy*>(this));
    return QObject::qt_metacast(_clname);
}

int Proxy::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sigHide(); break;
        case 1: sigRestartTimer(); break;
        case 2: sigMovingChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: sigPlay(); break;
        case 4: sigPause(); break;
        case 5: sigNext(); break;
        case 6: sigPrevious(); break;
        case 7: sigSeekForward(); break;
        case 8: sigSeekBack(); break;
        case 9: sigStopSeeking(); break;
        case 10: setSize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 11: sigSeekToPercent((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: sigGetState(); break;
        case 13: Hide(); break;
        case 14: restartTimer(); break;
        case 15: MovingChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 16: Play(); break;
        case 17: Pause(); break;
        case 18: Next(); break;
        case 19: Previous(); break;
        case 20: SeekForward(); break;
        case 21: SeekBack(); break;
        case 22: StopSeeking(); break;
        case 23: openViewer((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 24: screenChanged(); break;
        case 25: SeekToPos((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 26: GetState(); break;
        default: ;
        }
        _id -= 27;
    }
    return _id;
}

// SIGNAL 0
void Proxy::sigHide()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Proxy::sigRestartTimer()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void Proxy::sigMovingChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Proxy::sigPlay()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void Proxy::sigPause()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void Proxy::sigNext()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void Proxy::sigPrevious()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void Proxy::sigSeekForward()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}

// SIGNAL 8
void Proxy::sigSeekBack()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}

// SIGNAL 9
void Proxy::sigStopSeeking()
{
    QMetaObject::activate(this, &staticMetaObject, 9, 0);
}

// SIGNAL 10
void Proxy::setSize(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void Proxy::sigSeekToPercent(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void Proxy::sigGetState()
{
    QMetaObject::activate(this, &staticMetaObject, 12, 0);
}
QT_END_MOC_NAMESPACE
