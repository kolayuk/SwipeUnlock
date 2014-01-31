/****************************************************************************
** Meta object code from reading C++ file 'application.h'
**
** Created: Tue 25. Dec 20:38:04 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../application.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'application.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Application[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      26,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: signature, parameters, type, tag, flags
      26,   13,   12,   12, 0x05,
      46,   12,   12,   12, 0x05,
      64,   58,   12,   12, 0x05,
      77,   12,   12,   12, 0x05,
      93,   89,   12,   12, 0x05,
     172,  118,   12,   12, 0x05,
     225,  221,   12,   12, 0x05,
     245,   12,   12,   12, 0x05,
     257,   12,   12,   12, 0x05,
     275,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
     289,   12,   12,   12, 0x0a,
     298,   12,   12,   12, 0x0a,
     318,  305,   12,   12, 0x0a,
     345,  342,   12,   12, 0x0a,
     359,   12,   12,   12, 0x0a,
     369,   12,   12,   12, 0x0a,
     381,   12,   12,   12, 0x0a,
     398,   12,   12,   12, 0x0a,
     409,   12,   12,   12, 0x0a,
     418,   12,   12,   12, 0x0a,
     439,  433,   12,   12, 0x0a,
     467,   12,  459,   12, 0x0a,
     477,   12,  459,   12, 0x0a,
     492,  487,   12,   12, 0x0a,
     514,  508,   12,   12, 0x0a,

 // methods: signature, parameters, type, tag, flags
     534,   12,   12,   12, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_Application[] = {
    "Application\0\0screen,index\0update(QString,int)\0"
    "setToZero()\0aShow\0Suspend(int)\0"
    "unSuspend()\0app\0setQMLFile(Application*)\0"
    "battery,charging,network_signal,opsos,mode,profile,bt\0"
    "updateStatusBar(int,int,int,QString,int,int,int)\0"
    "w,h\0changeSize(int,int)\0stopTimer()\0"
    "updateWallpaper()\0setNotSleep()\0"
    "onExit()\0Tick()\0key,duration\0"
    "DllKeyCaptured(int,int)\0id\0setThrID(int)\0"
    "unSleep()\0AfterLock()\0startObserving()\0"
    "UnlockKB()\0Unlock()\0restartTimer()\0"
    "state\0MovingChanged(bool)\0QString\0"
    "GetDate()\0getTime()\0aUid\0Launch(QString)\0"
    "dx,dy\0moveWindow(int,int)\0Hide()\0"
};

const QMetaObject Application::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_Application,
      qt_meta_data_Application, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Application::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Application::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Application::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Application))
        return static_cast<void*>(const_cast< Application*>(this));
    if (!strcmp(_clname, "MFgrCallBack"))
        return static_cast< MFgrCallBack*>(const_cast< Application*>(this));
    if (!strcmp(_clname, "MCRCallBack"))
        return static_cast< MCRCallBack*>(const_cast< Application*>(this));
    if (!strcmp(_clname, "MCallCallBack"))
        return static_cast< MCallCallBack*>(const_cast< Application*>(this));
    if (!strcmp(_clname, "MWindowMover"))
        return static_cast< MWindowMover*>(const_cast< Application*>(this));
    if (!strcmp(_clname, "MPropertyCallBack"))
        return static_cast< MPropertyCallBack*>(const_cast< Application*>(this));
    return QThread::qt_metacast(_clname);
}

int Application::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: update((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: setToZero(); break;
        case 2: Suspend((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: unSuspend(); break;
        case 4: setQMLFile((*reinterpret_cast< Application*(*)>(_a[1]))); break;
        case 5: updateStatusBar((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< int(*)>(_a[7]))); break;
        case 6: changeSize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: stopTimer(); break;
        case 8: updateWallpaper(); break;
        case 9: setNotSleep(); break;
        case 10: onExit(); break;
        case 11: Tick(); break;
        case 12: DllKeyCaptured((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 13: setThrID((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: unSleep(); break;
        case 15: AfterLock(); break;
        case 16: startObserving(); break;
        case 17: UnlockKB(); break;
        case 18: Unlock(); break;
        case 19: restartTimer(); break;
        case 20: MovingChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 21: { QString _r = GetDate();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 22: { QString _r = getTime();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 23: Launch((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 24: moveWindow((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 25: Hide(); break;
        default: ;
        }
        _id -= 26;
    }
    return _id;
}

// SIGNAL 0
void Application::update(QString _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Application::setToZero()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void Application::Suspend(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Application::unSuspend()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void Application::setQMLFile(Application * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Application::updateStatusBar(int _t1, int _t2, int _t3, QString _t4, int _t5, int _t6, int _t7)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)), const_cast<void*>(reinterpret_cast<const void*>(&_t7)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Application::changeSize(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Application::stopTimer()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}

// SIGNAL 8
void Application::updateWallpaper()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}

// SIGNAL 9
void Application::setNotSleep()
{
    QMetaObject::activate(this, &staticMetaObject, 9, 0);
}
QT_END_MOC_NAMESPACE
