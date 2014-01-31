#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <QObject>
#include <aiplayerpluginengine.h>
#include <QTimer>
#include <propertyobserver.h>
#include <albumartprovider.h>

struct TStation{
    QString name;
    QString rds;
    float freq;
};

class PlayerController : public QObject, public MAiPlayerPluginEngineObserver, public MPropertyCallBack
{
    Q_OBJECT
public:
    bool iSwitchTrack;
    AlbumArtProvider* iQMLProvider;
    explicit PlayerController(QObject *parent = 0);
    CAiPlayerPluginEngine* iPlayer;
    void ValChanged(TUid aUid, TUint32 aKey, TInt aValue);
    void ValTxtChanged(TUid aUid, TUint32 aKey, TDesC aValue);
    void PlayerStateChanged( TMPXPlaybackState aState );
    void Close(TUid aUid);
    void TrackInfoChanged( const TDesC& aTitle, const TDesC& aArtist );
    void PlaybackPositionChanged( TInt aPosition );
    void AlbumArtChanged( CFbsBitmap* aBitmap );
    void Opening();
    TStation iStation;
    void PlaylisIsEmpty();
    QTimer* checkTimer;
    bool playerLaunched;
    bool radioLaunched;
    CPropertyObserver* iFreqObserver;
    CPropertyObserver* iRadioStateObserver;
    CPropertyObserver* iRdsObserver;
    CPropertyObserver* iNameObserver;
signals:
    void playing();
    void stopped();
    void paused();
    void playerStarted(bool pl);
    void playerClosed();
    void changeTrackInfo(QString artist,QString song);
    void changePos(int val,int len);
    void passAlbumArt(CFbsBitmap*);
    void updateAlbumArt(int show);
public slots:
    void CheckPlayerState();
    void Tick();
    void Play();
    void Pause();
    void Next();
    void Previous();
    void SeekForward();
    void SeekBack();
    void StopSeeking();
    void AlbumArtSaved(CFbsBitmap*);
    void GoToNowPlaying();
    void ClosePlayer();
    void SeekToPos(int percent);
    void GetState();
};

#endif // PLAYERCONTROLLER_H
