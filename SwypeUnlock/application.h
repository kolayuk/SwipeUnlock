#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <localizer.h>
#include <QSettings>
#include <QDeclarativeContext>
#include <qmlapplicationviewer.h>

#ifdef Q_OS_SYMBIAN
#include <e32base.h>
#include <SplashControl.h>
struct TApplicationInfo
{
        TFileName iCaption;
        TUid iUid;
        static TInt Compare(const TApplicationInfo& aInfo1, const TApplicationInfo& aInfo2)
        {
                return aInfo1.iCaption.CompareC(aInfo2.iCaption);
        }
};
#endif

class Application : public QObject
{
    Q_OBJECT
public:
    CSplashScreen* splash;
    explicit Application(QmlApplicationViewer& v,QObject *parent = 0);
    Localizer* loc;
    QSettings* settings;
    void ReadSettings();
    bool isFirstStart;
    QmlApplicationViewer& viewer;
    Q_INVOKABLE void ChangeSetting(QString id, QVariant value);
    int countScans;
    Q_INVOKABLE void EditPic();
    Q_INVOKABLE void Exit();
    Q_INVOKABLE int isKeyChecked(int index);
    Q_INVOKABLE int keysLen();
    Q_INVOKABLE void checkKey(int key, bool checked);
    QList<int> keys;
    QMap<int,int> keyMap;
    QStringList appModel;
#ifdef Q_OS_SYMBIAN
    RArray<TApplicationInfo> apps;
    RArray<TApplicationInfo> fullApps;
#endif
signals:
    void appWorkChanged(int newstate);
    void autostartChanged(int newstate);
    void pictureChanged(QString newpic);
    void buttonChanged(int newstate);
    void zoomChanged(int newstate);
    void gestureChanged(int newstate);
    void timeChanged(int newstate);
    void horSenseChanged(float sense);
    void verSenseChanged(float sense);
    void hideSMSChanged(int newstate);
    void useWallpaperChanged(int newstate);
    void fp2DrawChanged(int newstate);
    void app1Changed(QString app);
    void app2Changed(QString app);
    void app3Changed(QString app);
    void app4Changed(QString app);
    void app5Changed(QString app);
    void notificationsChanged(int newstate);
    void playerAlbumChanged(int newstate);
    void showAppPanelNotification();
public slots:
    void SortApps(QString filter);
    void KillAnotherLockScreens();
    void KillLockScreen(QString name);
    int GetAnotherLockscreens();
    int isLockScreenLaunched(QString name);
    void HideSplash();

};

#endif // APPLICATION_H
