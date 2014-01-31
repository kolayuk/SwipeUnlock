/****************************************************************************
** Meta object code from reading C++ file 'notifyprovider.h'
**
** Created: Sat 22. Dec 15:01:50 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../notifyprovider.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'notifyprovider.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_NotifyProvider[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: signature, parameters, type, tag, flags
      41,   16,   15,   15, 0x05,
     121,   90,   15,   15, 0x05,
     183,  177,   15,   15, 0x05,
     203,   15,   15,   15, 0x05,
     218,  212,   15,   15, 0x05,
     239,  212,   15,   15, 0x05,
     264,  259,   15,   15, 0x05,
     280,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
     295,  177,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_NotifyProvider[] = {
    "NotifyProvider\0\0from,text,time,icon,type\0"
    "addNotifier(QString,QString,QString,QString,int)\0"
    "index,from,text,time,icon,type\0"
    "updateNotifier(int,QString,QString,QString,QString,int)\0"
    "index\0removeNotifier(int)\0Unlock()\0"
    "count\0updateCallCount(int)\0"
    "updateSMSCount(int)\0show\0SuspendApp(int)\0"
    "unSuspendApp()\0openViewer(int)\0"
};

const QMetaObject NotifyProvider::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_NotifyProvider,
      qt_meta_data_NotifyProvider, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &NotifyProvider::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *NotifyProvider::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *NotifyProvider::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NotifyProvider))
        return static_cast<void*>(const_cast< NotifyProvider*>(this));
    if (!strcmp(_clname, "MLogMonitor"))
        return static_cast< MLogMonitor*>(const_cast< NotifyProvider*>(this));
    if (!strcmp(_clname, "MSMSRecCallBack"))
        return static_cast< MSMSRecCallBack*>(const_cast< NotifyProvider*>(this));
    if (!strcmp(_clname, "MCRCallBack"))
        return static_cast< MCRCallBack*>(const_cast< NotifyProvider*>(this));
    return QObject::qt_metacast(_clname);
}

int NotifyProvider::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: addNotifier((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 1: updateNotifier((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6]))); break;
        case 2: removeNotifier((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: Unlock(); break;
        case 4: updateCallCount((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: updateSMSCount((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: SuspendApp((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: unSuspendApp(); break;
        case 8: openViewer((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void NotifyProvider::addNotifier(QString _t1, QString _t2, QString _t3, QString _t4, int _t5)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void NotifyProvider::updateNotifier(int _t1, QString _t2, QString _t3, QString _t4, QString _t5, int _t6)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void NotifyProvider::removeNotifier(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void NotifyProvider::Unlock()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void NotifyProvider::updateCallCount(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void NotifyProvider::updateSMSCount(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void NotifyProvider::SuspendApp(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void NotifyProvider::unSuspendApp()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}
QT_END_MOC_NAMESPACE
