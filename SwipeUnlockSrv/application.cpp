#include "application.h"
#include <QDebug>
#include <QApplication>
#include <QDeclarativeContext>
#include <QImage>
#include <QPixmap>
#include <const.h>
#include <apgwgnam.h>
#include <eikenv.h>
#include <coedef.h>
#include <aknkeylock.h>
#include <ImageConversion.h>
#include <fbs.h>
#include <centralrepository.h>
#include <e32keys.h>
#include <AknAppUi.h>
#include <QThread>
#include <QCoreApplication>
#include <e32property.h>
#include <QEventLoop>
#include <QRect>
#include <QDesktopWidget>
#include <QOrientationSensor>
#include <apacmdln.h>
#include <apgcli.h>
#include <QDate>
#include <callsmonitor.h>
#include <QFile>
#include <hal.h>
#include <hal_data.h>
Application::Application(QmlApplicationViewer& v,QObject *parent) :
    QThread(),viewer(v)
{
ready=false;
inCall=EFalse;
setStackSize(0xf000);
start();
moveToThread(this);
}
void Application::run()
{
lockedWithCode=EFalse;
QFile fp2("Z:\\System\\Install\\Series60v5.5.sis");
QFile fp1("Z:\\System\\Install\\Series60v5.4.sis");
if (fp2.exists()||fp1.exists()) {qDebug()<<"FP2 OS"; isFP2=true;}
else {qDebug()<<"not FP2 OS"; isFP2=false;}
TInt device;
HAL::Get(HAL::EMachineUid,device);
if (device==0x20035566) // nokia 500
 {qDebug()<<"Nokia 500 - enable fp2 mode"; isFP2=true;}
rotated=false;
iAfterLockCancelSuspend=false;
settings=new QSettings(KConfigFile,QSettings::IniFormat);
if (!settings->value("settings/appwork",KWork).toBool()){qDebug()<<"app disabled";((CAknAppUi*)CEikonEnv::Static()->AppUi())->Exit();}
iSession=new RWsSession();
iSession->Connect();
qDebug()<<"thread id in start run"<<RThread().Id().Id();
thrID=RThread().Id().Id();
TApaTaskList list(*iSession);
TApaTask task=list.FindApp(TUid::Uid(KGUIUid));
if(!task.Exists())
{//autostart
    if (!settings->value("settings/autostart",KAutostart).toBool()){qDebug()<<"autostarted and its disabled";((CAknAppUi*)CEikonEnv::Static()->AppUi())->Exit();}
}
GroupListChanged();
settings->beginGroup("settings");
QVariantList slist;
QStringList keys=settings->allKeys();
keys.sort();
qDebug()<<keys;
for (int i=0;i<keys.count();i++)
{
    slist<<settings->value(keys[i]);
}
settings->endGroup();
viewer.rootContext()->setContextProperty("settings",slist);

iKeys.clear();
settings->beginGroup("keys");
QStringList sets=settings->allKeys();
for (int i=0;i<sets.length();i++)
{
    iKeys.append(settings->value(sets[i],-1).toInt());
}
settings->endGroup();
if (iKeys.count()==0) iKeys.append(180);
apps.clear();
settings->beginGroup("apps");
QStringList sets_apps=settings->allKeys();
for (int i=0;i<sets_apps.length();i++)
{
    apps.append(settings->value(sets_apps[i],"2004423C").toString());
}
settings->endGroup();

qDebug()<<iKeys<<sets.length();

qDebug()<<"check&start starter";
TInt err=-1;
bool found=false;
TRAP(err,
{
      TBuf<255> a;
      a.Append(KStarter);
      a.Append(_L("*"));
      TFindProcess processFinder(a); // by name, case-sensitive
      TFullName result;
      RProcess processHandle;
      while ( processFinder.Next(result) == KErrNone)
      {
          User::LeaveIfError(processHandle.Open ( processFinder, EOwnerThread));
          found=true;
      }
});
qDebug()<<"checked"<<err<<found;
if (err||(!found))
{
    RApaLsSession session;
    session.Connect();
    CApaCommandLine* cmdLine = CApaCommandLine::NewLC();
    cmdLine->SetExecutableNameL(KStarter);
    cmdLine->SetCommandL(EApaCommandRun);
    cmdLine->SetCommandL(EApaCommandBackground);
    TInt err2=session.StartApp(*cmdLine);
    CleanupStack::PopAndDestroy(cmdLine);
    session.Close();
    qDebug()<<"started"<<err2;
}

RAknKeyLock lock;
lock.Connect();
lock.DisableWithoutNote();
qDebug()<<"Unlocked";
lock.Close();

connect(this,SIGNAL(destroyed()),this,SLOT(onExit()));
int lang=16;
#ifdef Q_OS_SYMBIAN
lang=User::Language();
#endif
loc=new Localizer(lang);
#ifdef Q_OS_SYMBIAN
iId=-1;
//CEikonEnv::Static()->RootWin().SetOrdinalPosition(-1, ECoeWinPriorityNeverAtFront);
iObserver=CFgrObserver::NewL(*iSession,*this);
iCR=CCenRepObserver::NewL(TUid::Uid(0x101f8765),0x1,*this);
iCR->StartObservingL();
qDebug()<<"observer created";
status=new StatusBarInfo();
status->startListening();
iPlayer=new PlayerController();
//iPlayer->moveToThread(this);
qDebug()<<"player created";
iNotifications=new NotifyProvider();
connect(iNotifications,SIGNAL(Unlock()),this,SLOT(Unlock()));
connect(iNotifications,SIGNAL(SuspendApp(int)),this,SIGNAL(Suspend(int)));
connect(iNotifications,SIGNAL(unSuspendApp()),this,SLOT(unSleep()));
#endif

iTimer=new QTimer();
connect(iTimer,SIGNAL(timeout()),this,SLOT(Tick()),Qt::DirectConnection);
iTimer->setSingleShot(true);
iTimer->setInterval(KLockTimer);
connect(this,SIGNAL(stopTimer()),iTimer,SLOT(stop()),Qt::QueuedConnection);
startObservingTimer=new QTimer();
connect(startObservingTimer,SIGNAL(timeout()),this,SLOT(startObserving()),Qt::DirectConnection);
startObservingTimer->setSingleShot(true);
startObservingTimer->setInterval(500);

iAfterLockTimer=new QTimer();
connect(iAfterLockTimer,SIGNAL(timeout()),this,SLOT(AfterLock()),Qt::DirectConnection);
iAfterLockTimer->setSingleShot(true);
iAfterLockTimer->setInterval(KAfterLockTimer);

CRepository* cr=CRepository::NewL(TUid::Uid(0x101f8770));
TBuf<255> s;
cr->Get(0x1,s);
QString scr=QString::fromRawData(reinterpret_cast<const QChar*>(s.Ptr()),s.Length());
delete cr;
qDebug()<<"screensaver:"<<scr;
/*
iUnlockTimer=new QTimer();
connect(iUnlockTimer,SIGNAL(timeout()),this,SLOT(UnlockKB()),Qt::DirectConnection);
iUnlockTimer->setSingleShot(true);
int timeout=scr.length()==0?5:100;
iUnlockTimer->setInterval(timeout);
*/
iCallMon = CCallMonitor::NewL(*this);

wallpaper=settings->value("settings/picture",KPicture).toString();
int usewp=settings->value("settings/zusewallpaper",0).toInt();
if (usewp)
{
   TBuf<512> aValue;
   CRepository* wpcr=CRepository::NewL(TUid::Uid(0x101F876F));
   wpcr->Get(0x9,aValue);
   delete wpcr;
   wallpaper=QString::fromRawData(reinterpret_cast<const QChar*>(aValue.Ptr()),aValue.Length());
   wallpaper.replace("\\","\\\\");
   wallpaper="file:///"+wallpaper;
   if (wallpaper.length()<9){ wallpaper="image://skin/"+QString::number(rand()%10);}

}
wallpaperUpdated=true;
viewer.rootContext()->setContextProperty("wallpaper",wallpaper);
iWallpaperObserver=CCenRepObserver::NewL(TUid::Uid(0x101F876F),0x9,*this);
iWallpaperObserver->StartObservingL();
    CRepository* cr1=CRepository::NewL(TUid::Uid(0x101f877a));
    TInt val=60;
    cr1->Get(0x5,val);
    User::After(50000);
    cr1->Set(0x5,60);
    User::After(50000);
    cr1->Set(0x5,val);
    delete cr1;


    viewer.rootContext()->setContextProperty("application",this);
    viewer.rootContext()->setContextProperty("strings",loc->GetStringsAsList());
    viewer.rootContext()->setContextProperty("player",iPlayer);
    viewer.rootContext()->setContextProperty("notify",iNotifications);
    qDebug()<<"application -ok";
    emit setQMLFile(this);
    ready=true;
    qDebug()<<"thread id in end run "<<RThread().Id().Id();
    nOfLocks=0;
    iFixAutolockTimer=CPeriodic::NewL(CActive::EPriorityLow);
    iFixAutolockTimer->Start(11*1000*1000,11*1000*1000,TCallBack(iFixAutolockCB,this));
    iDll=new AnimDll(iSession,QString(KDllName));
    connect(iDll,SIGNAL(KeyCaptured(int,int)),this,SLOT(DllKeyCaptured(int,int)));
    ILockCodeObserver=CPropertyObserver::NewL(KPSUidCoreApplicationUIs,KCoreAppUIsAutolockStatus,this);
    exec();
    qDebug()<<"exec()";
}

#ifdef Q_OS_SYMBIAN


void Application::ScreenChanged()
{
qDebug()<<"ScreenChanged";
CWsScreenDevice* iScreenDevice=new (ELeave) CWsScreenDevice(*iSession);
iScreenDevice->Construct();
int w=iScreenDevice->SizeInPixels().iWidth;
int h=iScreenDevice->SizeInPixels().iHeight;
qDebug()<<"Size:"<<w<<h;
delete iScreenDevice;
TInt id=iSession->GetFocusWindowGroup();
CApaWindowGroupName* gn = CApaWindowGroupName::NewL(*iSession, id);
if (gn->AppUid().iUid!=0x10207218){iW=w; iH=h;}
emit changeSize(w,h);
}

void Application::GroupListChanged()
{

    TInt id=iSession->GetFocusWindowGroup();
    CApaWindowGroupName* gn = CApaWindowGroupName::NewL(*iSession, id);
    qDebug()<<"focus changed"<<QString::number((TUint32)gn->AppUid().iUid,16);
    if (gn->AppUid()==TUid::Uid(0x10005a32)){((CAknAppUi*)CEikonEnv::Static()->AppUi())->Exit();} // themes
    if (gn->AppUid()==TUid::Uid(0x2000fdc3)) {emit Suspend(1);} // screen saver
    if (gn->AppUid()==TUid::Uid(0x100058b3)){Hide();} // phone
    delete gn;
}

void Application::ValueChanged(TUid aUid,TUint32 key,TInt aValue,TInt aErr)
{
    if (aUid==TUid::Uid(0x101f8765)) // keyboard
    {
        if (inCall) return;
        iLocked=aValue;
        iAfterLockCancelSuspend=false;
        CApaWindowGroupName* gn = CApaWindowGroupName::NewL(*iSession, iSession->GetFocusWindowGroup());
        qDebug()<<"keylock "<<aValue<<QString::number((TUint32)gn->AppUid().iUid,16);
        TUid uid=gn->AppUid();
        if (aValue)
        {
            if (iFixAutolockTimer->IsActive()){iFixAutolockTimer->Cancel();}
            unSleep();
            qDebug()<<"capture";
            iDll->iClientCommander.ImageCommand(EStartCapture);
            emit setToZero();
            emit Suspend(1);
            /*
            for (int i=1;i<=255;i++)
            {
                iHandles<<iObserver->CaptureKey(i);
            }
            */
            iAfterLockTimer->start();
        }
        if (!aValue)
        {
            if (iFixAutolockTimer->IsActive())iFixAutolockTimer->Cancel();
            iFixAutolockTimer->Start(11*1000*1000,11*1000*1000,TCallBack(iFixAutolockCB,this));
            Hide(); // it's in dllkeycaptured
            iDll->iClientCommander.ImageCommand(EStopCapture);
        }
        delete gn;
    }
}

void Application::TextValueChanged(TUid uid, TUint32 key, TPtrC aValue, TInt aErr)
{
    if (uid==TUid::Uid(0x101F876F)&&key==0x9) // wallpaper
    {
        int usewp=settings->value("settings/zusewallpaper",0).toInt();
        if (usewp)
        {
        wallpaper=QString::fromRawData(reinterpret_cast<const QChar*>(aValue.Ptr()),aValue.Length());
        wallpaper.replace("\\","\\\\");
        wallpaper="file:///"+wallpaper;
        if (wallpaper.length()<9){ wallpaper="image://skin/"+QString::number(rand()%10);}
        qDebug()<<"wallpaper changed"<<wallpaper;
        wallpaperUpdated=true;
        viewer.rootContext()->setContextProperty("wallpaper",wallpaper);
        emit updateWallpaper();
        }
    }
}

void Application::KeyCaptured(TWsEvent event)
{

}

#endif


void Application::onExit()
{
#ifdef Q_OS_SYMBIAN
    qDebug()<<"exititng";
    if (iSession){iSession->Close(); delete iSession;}
    if (iObserver){delete iObserver;}
    if (iCR){delete iCR;}
#endif
}

void Application::Tick()
{
    //TBuf<255> a;
    //a.Num(User::InactivityTime().Int());
    qDebug()<<"thread id in tick"<<RThread().Id().Id();
    CApaWindowGroupName* gn = CApaWindowGroupName::NewL(*iSession, iSession->GetFocusWindowGroup());
    qDebug()<<"timer "<<QString::number((TUint32)gn->AppUid().iUid,16);
    TUid uid=gn->AppUid();
    if (uid==TUid::Uid(KMyUid))
    {
            RAknKeyLock lock;
            lock.Connect();
            if (!lock.IsKeyLockEnabled()){lock.EnableWithoutNote();}
            lock.Close();
            iTimer->stop();
            //emit Suspend();
            //Sleep();
            /*
            for (int i=0;i<iHandles.count();i++)
            {
                iObserver->CancelCapture(iHandles[i]);
            }
            iHandles.clear();
            for (int i=1;i<=255;i++)
            {
                iHandles<<iObserver->CaptureKey(i);
            }
           //*/
    }
    delete gn;

}

void Application::Hide()
{
qDebug()<<"hide";
unSleep();
emit Suspend(0);
qDebug()<<"uncapture";
RProperty::Set(TUid::Uid(KPropertyUid),0x200,EStopCapture);
if (lockedWithCode&&(!inCall))
{
    iDll->iClientCommander.ImageCommand(EStopCapture);
    User::After(50000);
    TRawEvent ev;
    ev.Set(TRawEvent::EKeyDown,179);
    UserSvr::AddEvent(ev);
    User::After(abs(50000));
    ev.Set(TRawEvent::EKeyUp,179);
    UserSvr::AddEvent(ev);
    User::After(50000);
    //iDll->iClientCommander.ImageCommand(EStartCapture);
    RProperty::Set(TUid::Uid(KPropertyUid),0x200,EStartCapture);
        qDebug()<<"Timer";
        iLockCodeCancelTimer=CPeriodic::NewL(CActive::EPriorityStandard);
        iLockCodeCancelTimer->Start(1500*1000,1500*1000,TCallBack(TickLockCodeCancelTimer,this));
    return;
}
    qDebug()<<"thread id in hide"<<RThread().Id().Id();
//iDll->iClientCommander.ImageCommand(EStopCapture);
qDebug()<<"stoptimer";
emit stopTimer();
qDebug()<<"ok";
}

void Application::AfterLock()
{

#ifdef Q_OS_SYMBIAN
/*
    if (nOfLocks%2==0)
        {qDebug()<<"after lock";setToZero();iAfterLockTimer->start();}
    else {qDebug()<<"after lock suspend";emit Suspend(1);}
    nOfLocks++;
    */
    //qDebug()<<"after lock";
    //emit setToZero();
    //if (!iAfterLockCancelSuspend){qDebug()<<"after lock suspend"; emit Suspend(1);}
    //iAfterLockCancelSuspend=false;

#endif
}

void Application::restartTimer()
{
qDebug()<<"restartTimer";
iTimer->stop();
iTimer->start();
}

void Application::startObserving()
{
    qDebug()<<"start observing, thread"<<RThread().Id().Id();
    iCR->StartObservingL();
}

void Application::Show()
{
    qDebug()<<"show"<<RThread().Id().Id() ;
    if (iFixAutolockTimer->IsActive())iFixAutolockTimer->Cancel();
    iFixAutolockTimer->Start(11*1000*1000,11*1000*1000,TCallBack(iFixAutolockCB,this));
    unSleep();
    emit updateStatusBar(status->bars,status->charging,status->signal,status->opsos,status->network_mode,status->profile,status->bluetooth);
    //if (wallpaperUpdated)emit updateWallpaper(wallpaper);
    //viewer.rootContext()->setContextProperty("wallpaper",wallpaper);
    wallpaperUpdated=false;
    iTimer->start();
    iAfterLockCancelSuspend=true;
        //iUnlockTimer->start();
        UnlockKB();
        emit unSuspend();
    qDebug()<<"show ok";


    CCoeControl *control =(viewer.winId());
    qDebug()<<" native control is "<<control;
    RDrawableWindow* rWindow= control->DrawableWindow();
    qDebug()<<" native window is "<<rWindow;
    qDebug()<<" native effective control is "<<viewer.effectiveWinId ();
    qDebug()<<"native internal control"<<viewer.internalWinId();
}

void Application::UnlockKB()
{
    qDebug()<<"UnlockKB";
    RAknKeyLock lock;
    lock.Connect();
    iCR->StopObserving();
    //CEikonEnv::Static()->RootWin().SetOrdinalPosition(0, ECoeWinPriorityAlwaysAtFront+KAddPriority);
    if (lock.IsKeyLockEnabled()){lock.DisableWithoutNote();}
    startObservingTimer->start();
    lock.Close();
}

void Application::Unlock()
{
    Hide();
}

void Application::setThrID(int id)
{
qDebug()<<"set id:"<<id;
iId=TThreadId(id);
}
/*
void Application::Sleep()
{
qDebug()<<"sleep";
//iStatus=KRequestPending;
//User::WaitForRequest(iStatus);
//viewer.setViewportUpdateMode(QGraphicsView::NoViewportUpdate);
}
*/
void Application::unSleep()
{
qDebug()<<"unsleep";
RThread t;
if (iId.Id()!=-1)
{
    qDebug()<<"err:"<<t.Open(iId,EOwnerProcess);
    qDebug()<<t.Id().Id();
    t.Resume();
    t.Close();
    emit setNotSleep();
}
}

void Application::MovingChanged(bool aMoving)
{
qDebug()<<"Moving changed:"<<aMoving;
if (aMoving){iTimer->stop();}
else {
iTimer->start();
}
}

void Application::DllKeyCaptured(int key,int duration)
{
    RAknKeyLock lock;
    lock.Connect();
    TInt id=iSession->GetFocusWindowGroup();
    CApaWindowGroupName* gn = CApaWindowGroupName::NewL(*iSession, id);
    TUid uid=gn->AppUid();
    if ((!lock.IsKeyLockEnabled())&&(!lockedWithCode)&&gn->AppUid()!=TUid::Uid(KMyUid)){iDll->iClientCommander.ImageCommand(EStopCapture); return;}

    delete gn;
    lock.Close();
    qDebug()<<"key"<<key<<duration<<iKeys.contains(key);
    if (uid!=TUid::Uid(KMyUid))
    {
        if (iKeys.contains(key)){Show(); return;}
        else
        {
            if (key==179){Hide();}
            qDebug()<<"emulate";
            iDll->iClientCommander.ImageCommand(EStopCapture);
            User::After(50000);
            TRawEvent ev;
            ev.Set(TRawEvent::EKeyDown,key);
            UserSvr::AddEvent(ev);
            User::After(abs(duration));
            ev.Set(TRawEvent::EKeyUp,key);
            UserSvr::AddEvent(ev);
            User::After(50000);
            iDll->iClientCommander.ImageCommand(EStartCapture);
        }
    }
    else
    {
        if (iKeys.contains(key)||key==179)
        {
        qDebug()<<"lock again";
        lock.Connect();
        lock.EnableWithoutNote();
        lock.Close();
        }
    }


/*

        iDll->iClientCommander.ImageCommand(EStopCapture);
        TRawEvent ev;
        ev.Set(TRawEvent::EKeyDown,180);
        UserSvr::AddEvent(ev);
        User::After(50000);
        ev.Set(TRawEvent::EKeyUp,180);
        UserSvr::AddEvent(ev);
        iDll->iClientCommander.ImageCommand(EStartCapture);
        */
        /*
        lock.Connect();
        if (lock.IsKeyLockEnabled()) Hide();
        if (lock.IsKeyLockEnabled()) lock.DisableWithoutNote();
        else lock.EnableWithoutNote();
        lock.Close();
        return;
        */
}

QString Application::GetDate()
{
QDateTime d=QDateTime::currentDateTime();
QString result=d.toString("dddd, d MMMM yyyy");//d.longDayName(d.dayOfWeek())+", "+QString::number(d.day())+" "+d.longMonthName(d.month(),QDate::StandaloneFormat)+" "+QString::number(d.year());
return result;
}

QString Application::getTime()
{
qDebug()<<"getTime";
TLocale l;
QString format;
if (l.TimeFormat()!=ETime24) format="hh:mm AP";
else format="hh:mm";
QDateTime t=QDateTime::currentDateTime();
return t.toString(format);
}

TInt Application::iFixAutolockCB(TAny *aObj)
{
/*
    int inact=User::InactivityTime().Int();
    CRepository* cr1=CRepository::NewL(TUid::Uid(0x101f877a));
    TInt val=60;
    cr1->Get(0x5,val);
    delete cr1;

    CRepository* cr2=CRepository::NewL(TUid::Uid(0x101f877a));
    cr2->Set(0x5,60);
    delete cr2;

    CRepository* cr3=CRepository::NewL(TUid::Uid(0x101f877a));
    cr3->Set(0x5,val);
    delete cr3;

    qDebug()<<"iFixAutolockCB1"<<User::InactivityTime().Int()<<val;
    if (inact>val)
    {
        RAknKeyLock lock;
        lock.Connect();
        qDebug()<<"lock by inactivity";
        if (!lock.IsKeyLockEnabled()) lock.EnableWithoutNote();
        lock.Close();
    }
    return 1;
    */
    return 0;
}
void Application::Launch(QString id)
{
    qDebug()<<"Launch"<<id;
    bool ok;
    TUid aUid=TUid::Uid((TUint32)id.toULong(&ok,16));
    RApaLsSession apaLsSession;
    User::LeaveIfError(apaLsSession.Connect());
    CleanupClosePushL(apaLsSession);
    TApaAppInfo appInfo;
    TInt retVal = apaLsSession.GetAppInfo(appInfo, aUid);
    if(retVal == KErrNone)
        {
/*
        CApaCommandLine* cmdLine = CApaCommandLine::NewLC();
        cmdLine->SetExecutableNameL(appInfo.iFullName);
        cmdLine->SetCommandL(EApaCommandRun);
        cmdLine->SetCommandL(EApaCommandViewActivate);
        User::LeaveIfError( apaLsSession.StartApp(*cmdLine) );
        CleanupStack::PopAndDestroy(cmdLine);
*/
        TParse p;
        CEikonEnv::Static()->FsSession().Parse(appInfo.iFullName,p);
        QString name=QString::fromRawData(reinterpret_cast<const QChar*>(p.NameAndExt().Ptr()),p.NameAndExt().Length());
        TApaTaskList list (CEikonEnv::Static()->WsSession());
        TApaTask tsk=list.FindApp(aUid);
        if (tsk.Exists()) tsk.BringToForeground();
        else
        {
            QProcess starter;
            starter.startDetached(name);
        }
        }
    else
        {
        // The application not found!
        }
    CleanupStack::PopAndDestroy(&apaLsSession);
}

void Application::moveWindow(int dx, int dy)
{

    if (isFP2)
    {
        qDebug()<<"moveWindow"<<dx<<dy;
        CCoeControl* control =(viewer.winId());
        RDrawableWindow* rWindow=(control->DrawableWindow());
        control->SetPosition(TPoint(dx,dy));
    }

}

void Application::CallStatusChangedL(CTelephony::TCallStatus &aStatus, TInt aError)
{
    inCall=(aStatus!=CTelephony::EStatusIdle);
    qDebug()<<"call status"<<(int)aStatus<<"err"<<aError;
    if (aError==KErrNone)
    {
        if (aStatus!=CTelephony::EStatusIdle){Hide();}
        else
        {

            RAknKeyLock lock;
            lock.Connect();
            if (lock.IsKeyLockEnabled())
            {
                if (iFixAutolockTimer->IsActive()){iFixAutolockTimer->Cancel();}
                unSleep();
                qDebug()<<"capture";
                iDll->iClientCommander.ImageCommand(EStartCapture);
                emit setToZero();
                emit Suspend(1);
                iAfterLockTimer->start();
            }
            lock.Close();
        }
    }
}

void Application::ValChanged(TUid aUid, TUint32 aKey, TInt aValue)
{
    if (aUid==KPSUidCoreApplicationUIs&&aKey==KCoreAppUIsAutolockStatus)
    {
        qDebug()<<"lock with code changed"<<aValue
                  ;
        if (aValue>EAutolockOff)
        {
            lockedWithCode=ETrue;
            ValueChanged(TUid::Uid(0x101f8765),0x1,1,0);
        }
        else {lockedWithCode=EFalse;ValueChanged(TUid::Uid(0x101f8765),0x1,0,0);}
    }
}

void Application::ValTxtChanged(TUid aUid, TUint32 aKey, TDesC aValue)
{
}

TInt Application::TickLockCodeCancelTimer(TAny *aObj)
{
    qDebug()<<"Application::TickLockCodeCancelTimer";
    qDebug()<<aObj;
    Application* obj=static_cast<Application*>(aObj);
    qDebug()<<obj->iLockCodeCancelTimer;
    obj->emit setToZero();
    //obj->emit Suspend(1);
    if (obj->iLockCodeCancelTimer)
    {
    if (obj->iLockCodeCancelTimer->IsActive()) obj->iLockCodeCancelTimer->Cancel();
    delete obj->iLockCodeCancelTimer;
    }
    return 0;
}



