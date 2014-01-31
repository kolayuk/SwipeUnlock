#include "suspender.h"
#include <QDebug>
#include <QCoreApplication>
#include <QThread>
#include <eikenv.h>
#include <const.h>
#include <QDeclarativeContext>
#include <eikenv.h>
#include <QTimer>
#include <aknappui.h>
#include <const.h>
#include <QDeclarativeEngine>

Suspender::Suspender(Proxy* pr,QObject *parent) :
    QObject(parent)
{
proxy=pr;
CEikonEnv::Static()->RootWin().SetOrdinalPosition(-1, ECoeWinPriorityNeverAtFront);
CEikonEnv::Static()->iWgName->SetSystem(ETrue);
CEikonEnv::Static()->iWgName->SetHidden(ETrue);
((CAknAppUi*)CEikonEnv::Static()->AppUi())->HideApplicationFromFSW(ETrue);
iTimer=new QTimer();
iTimer->setInterval(2000);
iTimer->setSingleShot(true);
connect(iTimer,SIGNAL(timeout()),this,SLOT(Tick()));
iSuspended=false; // debug
}

void Suspender::Suspend(int aShow)
{
qDebug()<<"Suspender::Suspend"<<iSuspended<<aShow;
if (aShow) CEikonEnv::Static()->RootWin().SetOrdinalPosition(0, ECoeWinPriorityAlwaysAtFront+KAddPriority);
else CEikonEnv::Static()->RootWin().SetOrdinalPosition(-1, ECoeWinPriorityNeverAtFront);
emit sendId(RThread().Id().Id());
if (!iSuspended) {iTimer->start();}
//iSuspended=true; // DEBUG!!!
if (fp2) iMover->hide();
}

void Suspender::unSuspend()
{
//application->viewer.rootContext()->setContextProperty("wallpaper",application->wallpaper);
CEikonEnv::Static()->RootWin().SetOrdinalPosition(0, ECoeWinPriorityAlwaysAtFront+KAddPriority);
iSuspended=false;
if (fp2) iMover->show();
qDebug()<<"Suspender::unSuspend";

}

void Suspender::setupQML(Application *app)
{
    fp2=app->isFP2;
    application=app;
    iMover=CWindowMover::NewL(app,&app->viewer,&CEikonEnv::Static()->WsSession());
    if (fp2)
    {
        connect(iMover,SIGNAL(MovingChanged(bool)),app,SLOT(MovingChanged(bool)),Qt::QueuedConnection);
        connect(app,SIGNAL(changeSize(int,int)),iMover,SLOT(changeSize(int,int)),Qt::QueuedConnection);
        connect(app,SIGNAL(setToZero()),iMover,SLOT(toZero()));
    }
    qDebug()<<"SetupQML";
    int set=app->settings->value("settings/orient",KOrient).toInt();
    app->viewer.rootContext()->setContextProperty("application",app);
    app->viewer.rootContext()->setContextProperty("wallpaper",app->wallpaper);
    app->viewer.rootContext()->setContextProperty("strings",app->loc->GetStringsAsList());
    app->viewer.rootContext()->setContextProperty("player",app->iPlayer);
    app->viewer.rootContext()->setContextProperty("notify",app->iNotifications);
    app->viewer.rootContext()->setContextProperty("apps",app->apps);
    app->viewer.rootContext()->setContextProperty("FP2",app->isFP2);
    if (fp2) app->viewer.rootContext()->setContextProperty("mover",iMover);
    app->viewer.engine()->addImageProvider(QLatin1String("album"), app->iPlayer->iQMLProvider);
    //app->viewer.setOrientation(set==0?QmlApplicationViewer::ScreenOrientationAuto:set==1?QmlApplicationViewer::ScreenOrientationLockPortrait:QmlApplicationViewer::ScreenOrientationLockLandscape);
    app->viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    app->viewer.setMainQmlFile(QLatin1String("qml/SwipeUnlockSrv/main.qml"));

    connect(proxy,SIGNAL(sigSeekToPercent(int)),app->iPlayer,SLOT(SeekToPos(int)),Qt::QueuedConnection);
    connect(proxy,SIGNAL(sigPlay()),app->iPlayer,SLOT(Play()),Qt::QueuedConnection);
    connect(proxy,SIGNAL(sigPause()),app->iPlayer,SLOT(Pause()),Qt::QueuedConnection);
    connect(proxy,SIGNAL(sigNext()),app->iPlayer,SLOT(Next()),Qt::QueuedConnection);
    connect(proxy,SIGNAL(sigPrevious()),app->iPlayer,SLOT(Previous()),Qt::QueuedConnection);
    connect(proxy,SIGNAL(sigSeekBack()),app->iPlayer,SLOT(SeekBack()),Qt::QueuedConnection);
    connect(proxy,SIGNAL(sigSeekForward()),app->iPlayer,SLOT(SeekForward()),Qt::QueuedConnection);
    connect(proxy,SIGNAL(sigStopSeeking()),app->iPlayer,SLOT(StopSeeking()),Qt::QueuedConnection);
    connect(proxy,SIGNAL(sigGetState()),app->iPlayer,SLOT(GetState()),Qt::QueuedConnection);
    app->iPlayer->moveToThread(app);
    app->iDll->moveToThread(app);
    app->viewer.showExpanded();
    qDebug()<<"showed";
    //iSuspended=false; // DEBUG!

    CCoeControl *control =(app->viewer.winId());
    qDebug()<<" native control is "<<control;
    RWindow rWindow= (control->Window());

    TRegionFix<1> reg=TRegionFix<1>(TRect(TPoint(0,0),TSize(100,100)));
    qDebug()<<reg.Count();
    rWindow.SetTransparencyAlphaChannel();
    qDebug()<<"Set Transparency region"<<rWindow.SetTransparentRegion(reg);
    control->DrawNow();
}

void Suspender::Tick()
{
TInt id=CEikonEnv::Static()->WsSession().GetFocusWindowGroup();
CApaWindowGroupName* gn = CApaWindowGroupName::NewL(CEikonEnv::Static()->WsSession(), id);
qDebug()<<"sleep"<<QString::number((TUint32)gn->AppUid().iUid,16);
if (gn->AppUid()!=TUid::Uid(KMyUid))
{
    iSuspended=true;
    TThreadId id=RThread().Id();
    RThread t;
    t.Open(id,EOwnerThread);
    t.Suspend();
    t.Close();
}
//else iTimer->start();
delete gn;
}

void Suspender::setNotSleep()
{
    iSuspended=false;
    qDebug()<<"set not sleep";
}
