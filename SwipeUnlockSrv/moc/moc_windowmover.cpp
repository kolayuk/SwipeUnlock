/****************************************************************************
** Meta object code from reading C++ file 'windowmover.h'
**
** Created: Sat 22. Dec 15:01:52 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../windowmover.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'windowmover.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CWindowMover[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,
      34,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      57,   51,   13,   13, 0x08,
      80,   51,   13,   13, 0x08,
     103,   13,   13,   13, 0x08,
     114,   13,   13,   13, 0x08,
     132,   13,   13,   13, 0x0a,
     139,   13,   13,   13, 0x0a,
     148,   13,   13,   13, 0x0a,
     159,  155,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CWindowMover[] = {
    "CWindowMover\0\0MovingChanged(bool)\0"
    "showLaunchArea()\0value\0xAnimChanged(QVariant)\0"
    "yAnimChanged(QVariant)\0finished()\0"
    "checkLaunchArea()\0show()\0toZero()\0"
    "hide()\0w,h\0changeSize(int,int)\0"
};

const QMetaObject CWindowMover::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CWindowMover,
      qt_meta_data_CWindowMover, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CWindowMover::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CWindowMover::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CWindowMover::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CWindowMover))
        return static_cast<void*>(const_cast< CWindowMover*>(this));
    if (!strcmp(_clname, "CCoeControl"))
        return static_cast< CCoeControl*>(const_cast< CWindowMover*>(this));
    return QObject::qt_metacast(_clname);
}

int CWindowMover::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: MovingChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: showLaunchArea(); break;
        case 2: xAnimChanged((*reinterpret_cast< const QVariant(*)>(_a[1]))); break;
        case 3: yAnimChanged((*reinterpret_cast< const QVariant(*)>(_a[1]))); break;
        case 4: finished(); break;
        case 5: checkLaunchArea(); break;
        case 6: show(); break;
        case 7: toZero(); break;
        case 8: hide(); break;
        case 9: changeSize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void CWindowMover::MovingChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CWindowMover::showLaunchArea()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
