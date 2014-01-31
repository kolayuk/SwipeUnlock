#include "playercontroller.h"
#include "aiplayerpluginengine.h"
#include <apgtask.h>
#include <eikenv.h>
#include <QDebug>
#include <w32std.h>
#include <e32base.h>
#include <fmradiointernalpskeys.h>
#include <mpxparameter.h>
#include <mpxconstants.h>               // KAppUidMusicPlayerX
#include <mpxmusicplayerviewplugin.hrh>

PlayerController::PlayerController(QObject *parent) :
    QObject(parent),MAiPlayerPluginEngineObserver()
{
iPlayer=CAiPlayerPluginEngine::NewL(*this);
iQMLProvider=new AlbumArtProvider();
connect(this,SIGNAL(passAlbumArt(CFbsBitmap*)),iQMLProvider,SLOT(setAlbumArt(CFbsBitmap*)));
connect(iQMLProvider,SIGNAL(AlbumArtSaved(CFbsBitmap*)),this,SLOT(AlbumArtSaved(CFbsBitmap*)));
playerLaunched=false;
radioLaunched=false;
checkTimer=new QTimer(this);
connect(checkTimer,SIGNAL(timeout()),this,SLOT(Tick()));
connect(this,SIGNAL(playerStarted(bool)),checkTimer,SLOT(start()));
checkTimer->setSingleShot(false);
checkTimer->setInterval(3000);
//checkTimer->start();
iStation.freq=0;
iStation.name="";
iStation.rds="";

iFreqObserver=CPropertyObserver::NewL(KFMRadioPSUid, KFMRadioPSDataFrequency,this);
iNameObserver=CPropertyObserver::NewL(KFMRadioPSUid, KFMRadioPSDataChannelName,this);
iRdsObserver=CPropertyObserver::NewL(KFMRadioPSUid, KFMRadioPSDataRDSRadioText,this);
iRadioStateObserver=CPropertyObserver::NewL(KFMRadioPSUid, KFMRadioPSDataRadioPowerState,this);
iSwitchTrack=false;
}

void PlayerController::PlayerStateChanged(TMPXPlaybackState aState)
{
    qDebug()<<"player state changed"<<aState;
    if (aState==EPbStateStopped){emit stopped();}
    else if (aState==EPbStatePlaying){emit playing();iSwitchTrack=true;}
    else if (aState==EPbStatePaused){emit paused();iSwitchTrack=true;}
    else if (aState==EPbStateNotInitialised&&(!iSwitchTrack))
    {
        if (!radioLaunched) emit playerClosed();
        playerLaunched=false;
        qDebug()<<"Player closed";
        checkTimer->stop();
    }
    if (!checkTimer->isActive()) checkTimer->start();
}

void PlayerController::TrackInfoChanged(const TDesC &aTitle, const TDesC &aArtist)
{
QString name=QString::fromRawData(reinterpret_cast<const QChar*>(aTitle.Ptr()),aTitle.Length());
QString artist=QString::fromRawData(reinterpret_cast<const QChar*>(aArtist.Ptr()),aArtist.Length());
qDebug()<<"TrackInfoChanged"<<name<<artist;
if (name.length()>15){name=name.left(12)+"...";}
if (artist.length()>40){artist=artist.left(37)+"...";}
//if (artist.length()==0){artist=QString::fromUtf8("Unknown aritst");}
emit changeTrackInfo(artist,name);
}

void PlayerController::PlaybackPositionChanged(TInt aPosition)
{
TInt len=iPlayer->Duration();
qDebug()<<aPosition<<len;
emit changePos(aPosition,len);
if (!checkTimer->isActive()) checkTimer->start();
}

void PlayerController::AlbumArtChanged(CFbsBitmap *aBitmap)
{
qDebug()<<"album art"<<aBitmap;
if (aBitmap) emit passAlbumArt(aBitmap);
else updateAlbumArt(0);
}
void PlayerController::Opening(){}
void PlayerController::PlaylisIsEmpty(){}

void PlayerController::Play()
{
qDebug()<<"Play, thread"<<RThread().Id().Id();
if (playerLaunched) iPlayer->iPlaybackUtility->CommandL(EPbCmdPlay);
else if (radioLaunched) Close(KRadioUid);
}

void PlayerController::Pause()
{
qDebug()<<"Pause, thread"<<RThread().Id().Id();
if (playerLaunched) iPlayer->iPlaybackUtility->CommandL(EPbCmdPause);
else if (radioLaunched) Close(KRadioUid);
}

void PlayerController::Next()
{
if (playerLaunched) iPlayer->iPlaybackUtility->CommandL(EPbCmdNext);
else if (radioLaunched) RProperty::Set( KFMRadioPSUid, KFMRadioPSControlStepToChannel, EFMRadioPSStepToChannelUp );
}

void PlayerController::Previous()
{
if (playerLaunched) iPlayer->iPlaybackUtility->CommandL(EPbCmdPrevious);
else if (radioLaunched) RProperty::Set( KFMRadioPSUid, KFMRadioPSControlStepToChannel, EFMRadioPSStepToChannelDown );
}

void PlayerController::SeekForward()
{
if (playerLaunched) iPlayer->iPlaybackUtility->CommandL(EPbCmdStartSeekForward);
}

void PlayerController::SeekBack()
{
if (playerLaunched) iPlayer->iPlaybackUtility->CommandL(EPbCmdStartSeekBackward);
}

void PlayerController::StopSeeking()
{
if (playerLaunched) iPlayer->iPlaybackUtility->CommandL(EPbCmdStopSeeking);
}

void PlayerController::Tick()
{
    RWsSession* iSession=new RWsSession();
    iSession->Connect();
       TApaTaskList lst(*iSession);
       TApaTask tsk=lst.FindApp(KMusicPlayerAppUid);
       TApaTask tsk2=lst.FindApp(KRadioUid);
       if (tsk.Exists())
       {
           if (!playerLaunched)
           {
               emit playerStarted(true);
               playerLaunched=true;
               qDebug()<<"Player launched";
               Close(KRadioUid);
               iPlayer->RequestMediaL();
           }
       }
       else
       {
           if (playerLaunched)
           {
               if (!radioLaunched) emit playerClosed();
               playerLaunched=false;
               qDebug()<<"Player closed";
               checkTimer->stop();
           }
       }

       if (!tsk2.Exists())
       {
           if (radioLaunched)
           {
               if (!playerLaunched) emit playerClosed();
               radioLaunched=false;
               qDebug()<<"radio closed";
               checkTimer->stop();
           }
       }
       iSession->Close();
}

void PlayerController::ValChanged(TUid aUid, TUint32 aKey, TInt aValue)
{
if (aKey==KFMRadioPSDataRadioPowerState)
{
    if (aValue==EFMRadioPSRadioPowerOn&&(!radioLaunched))
    {
        radioLaunched=true;
        Close(KMusicPlayerAppUid);
        qDebug()<<"radio launched";
        emit playerStarted(false);
     }
     else if (aValue==EFMRadioPSRadioPowerOff&&radioLaunched)
     {
        radioLaunched=false;
        qDebug()<<"radio closed";
        emit playerClosed();
     }
}
else if (aKey==KFMRadioPSDataFrequency)
{
    float freq=aValue/1e6;
    iStation.freq=freq;
    qDebug()<<aValue<<radioLaunched;
    if (freq>50&&freq<200)
    {
        radioLaunched=true;
        Close(KMusicPlayerAppUid);
        qDebug()<<"radio launched";
        emit playerStarted(false);
    }
    if ((freq>200||freq<50)&&radioLaunched)
    {
        radioLaunched=false;
        qDebug()<<"radio closed";
        emit playerClosed();
    }
    QString line;
    if (iStation.name.length()>0) line=QString::fromUtf8(iStation.name.toUtf8().data());
    else if (iStation.rds.length()>0) line=QString::fromUtf8(iStation.rds.toUtf8().data());
    else line=QString::fromUtf8("FM Radio");
    if (radioLaunched)changeTrackInfo(line,QString::number(iStation.freq,'f',2)+" MHz");
}
}

void PlayerController::Close(TUid aUid)
{
    RWsSession* iSession=new RWsSession();
    iSession->Connect();
    if (aUid==KRadioUid)
    {
    radioLaunched=false;
    qDebug()<<"radio closed";
    if (!playerLaunched){emit playerClosed();}
    }
    TApaTaskList lst(*iSession);
    TApaTask tsk=lst.FindApp(aUid);
    if(tsk.Exists()){tsk.EndTask();}
    iSession->Close();
}

void PlayerController::ValTxtChanged(TUid aUid, TUint32 aKey,TDesC aValue)
{
TBuf<255> name,rds,type;
RProperty::Get(KFMRadioPSUid, KFMRadioPSDataChannelName,name);
RProperty::Get(KFMRadioPSUid, KFMRadioPSDataRDSRadioText,rds);
iStation.name=QString::fromRawData(reinterpret_cast<const QChar*>(name.Ptr()),name.Length());
iStation.rds=QString::fromRawData(reinterpret_cast<const QChar*>(rds.Ptr()),rds.Length());

qDebug()<<"aValueTxtChanged"<<aKey<<iStation.name<<iStation.rds;

QString line;
if (iStation.name.length()>0) line=QString::fromUtf8(iStation.name.toUtf8().data());
else if (iStation.rds.length()>0) line=QString::fromUtf8(iStation.rds.toUtf8().data());
else line=QString::fromUtf8("FM Radio");
changeTrackInfo(line,QString::number(iStation.freq,'f',2)+" MHz");
}

void PlayerController::AlbumArtSaved(CFbsBitmap *bmp)
{
    if (bmp){
        emit updateAlbumArt(1);
    }
    else emit updateAlbumArt(0);
}

void PlayerController::CheckPlayerState()
{
RWsSession* iSession=new RWsSession();
iSession->Connect();
TApaTaskList lst(*iSession);
TApaTask tsk=lst.FindApp(KMusicPlayerAppUid);
TApaTask tsk2=lst.FindApp(KRadioUid);

if (tsk.Exists()){emit playerStarted(true);qDebug()<<"player started";}
if (tsk2.Exists())
{
    radioLaunched=true;
    emit playerStarted(false);
    qDebug()<<"radio started";
    int aValue;
    RProperty::Get(KFMRadioPSUid, KFMRadioPSDataFrequency,aValue);
    float freq=aValue/1e6;
    iStation.freq=freq;
    TBuf<255> name,rds,type;
    RProperty::Get(KFMRadioPSUid, KFMRadioPSDataChannelName,name);
    RProperty::Get(KFMRadioPSUid, KFMRadioPSDataRDSRadioText,rds);
    iStation.name=QString::fromRawData(reinterpret_cast<const QChar*>(name.Ptr()),name.Length());
    iStation.rds=QString::fromRawData(reinterpret_cast<const QChar*>(rds.Ptr()),rds.Length());
    QString line;
    if (iStation.name.length()>0) line=QString::fromUtf8(iStation.name.toUtf8().data());
    else if (iStation.rds.length()>0) line=QString::fromUtf8(iStation.rds.toUtf8().data());
    else line=QString::fromUtf8("FM Radio");
    changeTrackInfo(line,QString::number(iStation.freq,'f',2)+" MHz");
}
iSession->Close();
}

void PlayerController::GoToNowPlaying()
{
    if (playerLaunched)
    {
 //Launch player
        RWsSession wsSession;
        User::LeaveIfError( wsSession.Connect() );
        TApaTaskList list(wsSession);
        TApaTask task = list.FindApp(KMusicPlayerAppUid);
        CMPXParameter* param = new ( ELeave ) CMPXParameter();
        CleanupStack::PushL( param );
        param->iType.iUid = KMPXPluginTypePlaybackUid;
        param->iCmdForward = EMPXCmdFwdNone;
        CBufBase* buffer =
                CBufFlat::NewL(3 );
        CleanupStack::PushL( buffer );
        RBufWriteStream writeStream( *buffer );
        CleanupClosePushL( writeStream );
        param->ExternalizeL( writeStream );
        writeStream.CommitL();
        buffer->Compress();
        CleanupStack::PopAndDestroy( &writeStream );
        if ( task.Exists() )
            {
            wsSession.SendMessageToWindowGroup( task.WgId(), KAppUidMusicPlayerX,
                        buffer->Ptr( 0 ) );


            }
        else
            {
            RApaLsSession ls;
            CleanupClosePushL( ls );
            User::LeaveIfError( ls.Connect() );
            TApaAppInfo appInfo;
            User::LeaveIfError( ls.GetAppInfo( appInfo, KAppUidMusicPlayerX ) );
            CApaCommandLine* apaCommandLine = CApaCommandLine::NewLC();
            apaCommandLine->SetExecutableNameL( appInfo.iFullName );
            apaCommandLine->SetTailEndL( buffer->Ptr( 0 ) );
            User::LeaveIfError( ls.StartApp( *apaCommandLine ) );
            CleanupStack::PopAndDestroy(); // apaCommandLine
            CleanupStack::PopAndDestroy(); // ls
            }
        CleanupStack::PopAndDestroy( buffer );
        CleanupStack::PopAndDestroy( param );
        wsSession.Close();
    }
    else if (radioLaunched)
    {
        RApaLsSession ls;
        CleanupClosePushL( ls );
        User::LeaveIfError( ls.Connect() );
        TApaAppInfo appInfo;
        User::LeaveIfError( ls.GetAppInfo( appInfo, KRadioUid ) );
        CApaCommandLine* apaCommandLine = CApaCommandLine::NewLC();
        apaCommandLine->SetExecutableNameL( appInfo.iFullName );
        User::LeaveIfError( ls.StartApp( *apaCommandLine ) );
        CleanupStack::PopAndDestroy(); // apaCommandLine
        CleanupStack::PopAndDestroy(); // ls
    }
}

void PlayerController::ClosePlayer()
{
    Close(KMusicPlayerAppUid);
}

void PlayerController::SeekToPos(int percent)
{
    int secs=round(iPlayer->Duration()*(percent/100.0));
    qDebug()<<"seek to pos"<<secs;
    if (playerLaunched)iPlayer->iPlaybackUtility->SetL(EPbPropertyPosition,secs*1000);
}

void PlayerController::GetState()
{
    if (playerLaunched){
        TMPXPlaybackState state=iPlayer->iPlaybackUtility->StateL();
        PlayerStateChanged(state);
    }
}

