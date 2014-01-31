/****************************************************************************
** Meta object code from reading C++ file 'albumartprovider.h'
**
** Created: Sat 22. Dec 15:01:51 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../albumartprovider.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'albumartprovider.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AlbumArtProvider[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      50,   45,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_AlbumArtProvider[] = {
    "AlbumArtProvider\0\0AlbumArtSaved(CFbsBitmap*)\0"
    "aFbs\0setAlbumArt(CFbsBitmap*)\0"
};

const QMetaObject AlbumArtProvider::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_AlbumArtProvider,
      qt_meta_data_AlbumArtProvider, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AlbumArtProvider::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AlbumArtProvider::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AlbumArtProvider::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AlbumArtProvider))
        return static_cast<void*>(const_cast< AlbumArtProvider*>(this));
    if (!strcmp(_clname, "QDeclarativeImageProvider"))
        return static_cast< QDeclarativeImageProvider*>(const_cast< AlbumArtProvider*>(this));
    return QObject::qt_metacast(_clname);
}

int AlbumArtProvider::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: AlbumArtSaved((*reinterpret_cast< CFbsBitmap*(*)>(_a[1]))); break;
        case 1: setAlbumArt((*reinterpret_cast< CFbsBitmap*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void AlbumArtProvider::AlbumArtSaved(CFbsBitmap * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
