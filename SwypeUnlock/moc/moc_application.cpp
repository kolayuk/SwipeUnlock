/****************************************************************************
** Meta object code from reading C++ file 'application.h'
**
** Created: Thu 29. Nov 19:41:29 2012
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
      32,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      20,       // signalCount

 // signals: signature, parameters, type, tag, flags
      22,   13,   12,   12, 0x05,
      42,   13,   12,   12, 0x05,
      71,   64,   12,   12, 0x05,
      95,   13,   12,   12, 0x05,
     114,   13,   12,   12, 0x05,
     131,   13,   12,   12, 0x05,
     151,   13,   12,   12, 0x05,
     174,  168,   12,   12, 0x05,
     197,  168,   12,   12, 0x05,
     220,   13,   12,   12, 0x05,
     240,   13,   12,   12, 0x05,
     265,   13,   12,   12, 0x05,
     289,  285,   12,   12, 0x05,
     310,  285,   12,   12, 0x05,
     331,  285,   12,   12, 0x05,
     352,  285,   12,   12, 0x05,
     373,  285,   12,   12, 0x05,
     394,   13,   12,   12, 0x05,
     420,   13,   12,   12, 0x05,
     444,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
     478,  471,   12,   12, 0x0a,
     496,   12,   12,   12, 0x0a,
     526,  521,   12,   12, 0x0a,
     554,   12,  550,   12, 0x0a,
     578,  521,  550,   12, 0x0a,
     608,   12,   12,   12, 0x0a,

 // methods: signature, parameters, type, tag, flags
     630,  621,   12,   12, 0x02,
     662,   12,   12,   12, 0x02,
     672,   12,   12,   12, 0x02,
     685,  679,  550,   12, 0x02,
     703,   12,  550,   12, 0x02,
     725,  713,   12,   12, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_Application[] = {
    "Application\0\0newstate\0appWorkChanged(int)\0"
    "autostartChanged(int)\0newpic\0"
    "pictureChanged(QString)\0buttonChanged(int)\0"
    "zoomChanged(int)\0gestureChanged(int)\0"
    "timeChanged(int)\0sense\0horSenseChanged(float)\0"
    "verSenseChanged(float)\0hideSMSChanged(int)\0"
    "useWallpaperChanged(int)\0fp2DrawChanged(int)\0"
    "app\0app1Changed(QString)\0app2Changed(QString)\0"
    "app3Changed(QString)\0app4Changed(QString)\0"
    "app5Changed(QString)\0notificationsChanged(int)\0"
    "playerAlbumChanged(int)\0"
    "showAppPanelNotification()\0filter\0"
    "SortApps(QString)\0KillAnotherLockScreens()\0"
    "name\0KillLockScreen(QString)\0int\0"
    "GetAnotherLockscreens()\0"
    "isLockScreenLaunched(QString)\0"
    "HideSplash()\0id,value\0"
    "ChangeSetting(QString,QVariant)\0"
    "EditPic()\0Exit()\0index\0isKeyChecked(int)\0"
    "keysLen()\0key,checked\0checkKey(int,bool)\0"
};

const QMetaObject Application::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Application,
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
    return QObject::qt_metacast(_clname);
}

int Application::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: appWorkChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: autostartChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: pictureChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: buttonChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: zoomChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: gestureChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: timeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: horSenseChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 8: verSenseChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 9: hideSMSChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: useWallpaperChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: fp2DrawChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: app1Changed((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: app2Changed((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: app3Changed((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 15: app4Changed((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 16: app5Changed((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 17: notificationsChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: playerAlbumChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: showAppPanelNotification(); break;
        case 20: SortApps((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 21: KillAnotherLockScreens(); break;
        case 22: KillLockScreen((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 23: { int _r = GetAnotherLockscreens();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 24: { int _r = isLockScreenLaunched((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 25: HideSplash(); break;
        case 26: ChangeSetting((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2]))); break;
        case 27: EditPic(); break;
        case 28: Exit(); break;
        case 29: { int _r = isKeyChecked((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 30: { int _r = keysLen();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 31: checkKey((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 32;
    }
    return _id;
}

// SIGNAL 0
void Application::appWorkChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Application::autostartChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Application::pictureChanged(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Application::buttonChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Application::zoomChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Application::gestureChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Application::timeChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Application::horSenseChanged(float _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void Application::verSenseChanged(float _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void Application::hideSMSChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void Application::useWallpaperChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void Application::fp2DrawChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void Application::app1Changed(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void Application::app2Changed(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void Application::app3Changed(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void Application::app4Changed(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void Application::app5Changed(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void Application::notificationsChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void Application::playerAlbumChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void Application::showAppPanelNotification()
{
    QMetaObject::activate(this, &staticMetaObject, 19, 0);
}
QT_END_MOC_NAMESPACE
