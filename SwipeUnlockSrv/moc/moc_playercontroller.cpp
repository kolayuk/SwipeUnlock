/****************************************************************************
** Meta object code from reading C++ file 'playercontroller.h'
**
** Created: Tue 25. Dec 20:38:04 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../playercontroller.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'playercontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PlayerController[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x05,
      28,   17,   17,   17, 0x05,
      38,   17,   17,   17, 0x05,
      50,   47,   17,   17, 0x05,
      70,   17,   17,   17, 0x05,
      97,   85,   17,   17, 0x05,
     138,  130,   17,   17, 0x05,
     157,   17,   17,   17, 0x05,
     188,  183,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
     208,   17,   17,   17, 0x0a,
     227,   17,   17,   17, 0x0a,
     234,   17,   17,   17, 0x0a,
     241,   17,   17,   17, 0x0a,
     249,   17,   17,   17, 0x0a,
     256,   17,   17,   17, 0x0a,
     267,   17,   17,   17, 0x0a,
     281,   17,   17,   17, 0x0a,
     292,   17,   17,   17, 0x0a,
     306,   17,   17,   17, 0x0a,
     333,   17,   17,   17, 0x0a,
     350,   17,   17,   17, 0x0a,
     372,  364,   17,   17, 0x0a,
     387,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_PlayerController[] = {
    "PlayerController\0\0playing()\0stopped()\0"
    "paused()\0pl\0playerStarted(bool)\0"
    "playerClosed()\0artist,song\0"
    "changeTrackInfo(QString,QString)\0"
    "val,len\0changePos(int,int)\0"
    "passAlbumArt(CFbsBitmap*)\0show\0"
    "updateAlbumArt(int)\0CheckPlayerState()\0"
    "Tick()\0Play()\0Pause()\0Next()\0Previous()\0"
    "SeekForward()\0SeekBack()\0StopSeeking()\0"
    "AlbumArtSaved(CFbsBitmap*)\0GoToNowPlaying()\0"
    "ClosePlayer()\0percent\0SeekToPos(int)\0"
    "GetState()\0"
};

const QMetaObject PlayerController::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PlayerController,
      qt_meta_data_PlayerController, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PlayerController::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PlayerController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PlayerController::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PlayerController))
        return static_cast<void*>(const_cast< PlayerController*>(this));
    if (!strcmp(_clname, "MAiPlayerPluginEngineObserver"))
        return static_cast< MAiPlayerPluginEngineObserver*>(const_cast< PlayerController*>(this));
    if (!strcmp(_clname, "MPropertyCallBack"))
        return static_cast< MPropertyCallBack*>(const_cast< PlayerController*>(this));
    return QObject::qt_metacast(_clname);
}

int PlayerController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: playing(); break;
        case 1: stopped(); break;
        case 2: paused(); break;
        case 3: playerStarted((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: playerClosed(); break;
        case 5: changeTrackInfo((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: changePos((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: passAlbumArt((*reinterpret_cast< CFbsBitmap*(*)>(_a[1]))); break;
        case 8: updateAlbumArt((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: CheckPlayerState(); break;
        case 10: Tick(); break;
        case 11: Play(); break;
        case 12: Pause(); break;
        case 13: Next(); break;
        case 14: Previous(); break;
        case 15: SeekForward(); break;
        case 16: SeekBack(); break;
        case 17: StopSeeking(); break;
        case 18: AlbumArtSaved((*reinterpret_cast< CFbsBitmap*(*)>(_a[1]))); break;
        case 19: GoToNowPlaying(); break;
        case 20: ClosePlayer(); break;
        case 21: SeekToPos((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 22: GetState(); break;
        default: ;
        }
        _id -= 23;
    }
    return _id;
}

// SIGNAL 0
void PlayerController::playing()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void PlayerController::stopped()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void PlayerController::paused()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void PlayerController::playerStarted(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void PlayerController::playerClosed()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void PlayerController::changeTrackInfo(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void PlayerController::changePos(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void PlayerController::passAlbumArt(CFbsBitmap * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void PlayerController::updateAlbumArt(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_END_MOC_NAMESPACE
