#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QTimer>
#include <qmlapplicationviewer.h>

#ifdef Q_OS_SYMBIAN
#include <FgrObserver.h>
#include <CenRepObserver.h>
#include <apgwgnam.h>
#include "statusbarinfo.h"
#include "playercontroller.h"
#include <notifyprovider.h>
#include <aknkeylock.h>
#endif
#include <localizer.h>
#include <QSettings>
#include <QThread>
#include <e32base.h>
#include <QOrientationSensor>
#include <clientimagecommander.h>
#include <clientdll.h>
#include <animdll.h>
#include <callsMonitor.h>
#include <etel3rdparty.h>
#include <windowmover.h>
#include <QProcess>
enum {
        EStartCapture=1,
        EStopCapture
};

const TUid KPSUidCoreApplicationUIs = { 0x101F8767 };
const TUint32 KCoreAppUIsAutolockStatus  = 0x00000501;
enum TPSAutolockStatus
    {
    EAutolockStatusUninitialized = 0,
    EAutolockOff,
#ifndef RD_REMOTELOCK
    EAutolockOn
#else
    ETimerLocked, // Autolock period is user defined and the lock was set on due to user inactivity timeout.
    EManualLocked, // User set the lock on manually from the power key menu.
    ERemoteLocked //The lock was set on by a remote lock message.
#endif // RD_REMOTELOCK
};
QTM_USE_NAMESPACE
#ifdef Q_OS_SYMBIAN
class Application : public QThread, public MFgrCallBack,public MCRCallBack, public MCallCallBack, public MWindowMover, public MPropertyCallBack
#else
class Application : public QThread
#endif
{
    Q_OBJECT
public:
    TBool inCall;
    QSettings* settings;
    CPeriodic* iFixAutolockTimer;
    static TInt iFixAutolockCB(TAny* aObj);
    void CallStatusChangedL(CTelephony::TCallStatus& aStatus, TInt aError);
    void ValChanged(TUid aUid,TUint32 aKey, TInt aValue);
    void ValTxtChanged(TUid aUid,TUint32 aKey,TDesC aValue);
    CPropertyObserver* ILockCodeObserver;
    TBool lockedWithCode;
    CPeriodic* iLockCodeCancelTimer;
    static TInt TickLockCodeCancelTimer(TAny* aObj);
#ifdef Q_OS_SYMBIAN
    CCallMonitor* iCallMon;
    CFgrObserver* iObserver;
    CCenRepObserver* iCR;
    RWsSession* iSession;
    CCenRepObserver* iWallpaperObserver;
    void run();
    void GroupListChanged();
    void ScreenChanged();
    void ValueChanged(TUid uid,TUint32 key, TInt aValue,TInt aErr);
    void TextValueChanged(TUid uid,TUint32 key,TPtrC aValue,TInt aErr);
    QString wallpaper;
    bool wallpaperUpdated;
    void KeyCaptured(TWsEvent aEvent);
    int iLocked;
    void Show();
    QList<int> iHandles;
    TUid iFg;
    int thrID;
    AnimDll* iDll;
    bool iAfterLockCancelSuspend;
    QTimer* iAfterLockTimer;
    StatusBarInfo* status;
    QTimer* iTimer;
    QTimer* startObservingTimer;
    QTime iLockTime;
    QTimer* iUnlockTimer;
    bool iWasKeyEvent;
    TRequestStatus iStatus;
    TThreadId iId;
    int nOfLocks;
    QOrientationSensor* orient;
    int iW;
    int iH;
    bool rotated;
#endif
    QList<int> iKeys;
public:
    QmlApplicationViewer& viewer;
    Localizer* loc;
    bool ready;
    explicit Application(QmlApplicationViewer& v,QObject *parent = 0);
    Q_INVOKABLE void Hide();
    PlayerController* iPlayer;
    NotifyProvider* iNotifications;
    QStringList apps;
    bool isFP2;
signals:
    void update(QString screen,int index);
    void setToZero();
    void Suspend(int aShow);
    void unSuspend();
    void setQMLFile(Application* app);
    void updateStatusBar(int battery,int charging,int network_signal,QString opsos,int mode,int profile,int bt);
    void changeSize(int w, int h);
    void stopTimer();
    void updateWallpaper();
    void setNotSleep();
public slots:
    void onExit();
    void Tick();
    void DllKeyCaptured(int key,int duration);
    void setThrID(int id);
    void unSleep();
    void AfterLock();
    void startObserving();
    void UnlockKB();
    void Unlock();
    void restartTimer();
    void MovingChanged(bool state);
    QString GetDate();
    QString getTime();
    void Launch(QString aUid);
    void moveWindow(int dx,int dy);
};

#endif // APPLICATION_H
