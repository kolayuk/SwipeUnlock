#include "application.h"
#include <const.h>
#include <QDebug>
#ifdef Q_OS_SYMBIAN
 #include <MGFetch.h>
 #include <e32debug.h>
 #include <f32file.h>
 #include <eikenv.h>
 #include <apgcli.h>
#endif
#include <QFile>

Application::Application(QmlApplicationViewer& v,QObject *parent) :
    QObject(parent),viewer(v)
{
    TBuf<255> p1(_L("C:\\System\\Apps\\SwypeUnlock\\splash_h.jpg"));
    TBuf<255> p2(_L("C:\\System\\Apps\\SwypeUnlock\\splash_v.jpg"));
    splash=CSplashScreen::NewL(p2,p1);
int lang=1;
#ifdef Q_OS_SYMBIAN
lang=User::Language();
#endif
loc=new Localizer(lang,this);
QFile fs(KFirstStart);
isFirstStart=false;
if (fs.exists())
{
    fs.remove();
    QFile file(KConfigFile);
    if (file.exists()){file.remove();}
    isFirstStart=true;
}

settings=new QSettings(KConfigFile,QSettings::IniFormat);

keyMap.clear();
keyMap.insert(0,180); // menu
keyMap.insert(1,179); // lock
keyMap.insert(2,166); // power
keyMap.insert(3,196); // green
keyMap.insert(4,197); // red
keyMap.insert(5,171); // camera
keyMap.insert(6,226); // light camera


keys.clear();
settings->beginGroup("keys");
QStringList sets=settings->allKeys();
for (int i=0;i<sets.length();i++)
{
    keys.append(settings->value(sets[i],-1).toInt());
}
settings->endGroup();
if (keys.length()==0){keys.append(180);}

#ifdef Q_OS_SYMBIAN
RApaLsSession AppSession;
AppSession.Connect();
TApaAppInfo appInfo;
AppSession.GetAllApps();
TBuf<255> UidTxt;
while (AppSession.GetNextApp(appInfo)==KErrNone)
{
    HBufC* fn;
    if (AppSession.GetAppIcon(appInfo.iUid,fn)!=KErrNone){continue;}
    if (fn){delete fn;}
    if (appInfo.iCaption.Length()<2){continue;}
    TApplicationInfo info;
    info.iCaption=appInfo.iCaption;
    info.iUid=appInfo.iUid;
    apps.Append(info);
    fullApps.Append(info);
}
AppSession.Close();
TLinearOrder<TApplicationInfo> sortOrder(TApplicationInfo::Compare);
fullApps.Sort(sortOrder);
apps.Sort(sortOrder);
for (int i=0; i<fullApps.Count();i++)
{
appModel<<QString::fromRawData(reinterpret_cast<const QChar*>(apps[i].iCaption.Ptr()),apps[i].iCaption.Length());
}
#else
for (int i=0; i<20;i++)
{
appModel<<QString::number(i);
}
#endif
}
void Application::ReadSettings()
{
emit appWorkChanged(settings->value("settings/appwork",KWork).toBool());
emit autostartChanged(settings->value("settings/autostart",KAutostart).toBool());
#ifdef Q_OS_SYMBIAN
TParse parse;
QString file=settings->value("settings/picture",KPicture).toString();
file=file.replace("file:///","");
TPtrC file1 (reinterpret_cast<const TText*>(file.constData()),file.length());
CEikonEnv::Static()->FsSession().Parse(file1,parse);
TBuf<255> a=parse.NameAndExt();
file=QString::fromRawData(reinterpret_cast<const QChar*>(a.Ptr()),a.Length());
emit pictureChanged(file);

RApaLsSession ls;
ls.Connect();
TApaAppInfo info;
bool ok;
QString name;

ls.GetAppInfo(info, TUid::Uid((TUint32)settings->value("apps/app1",app1).toString().toULong(&ok,16)));
name=QString::fromRawData(reinterpret_cast<const QChar*>(info.iCaption.Ptr()),info.iCaption.Length());
app1Changed(name);

ls.GetAppInfo(info, TUid::Uid((TUint32)settings->value("apps/app2",app2).toString().toULong(&ok,16)));
name=QString::fromRawData(reinterpret_cast<const QChar*>(info.iCaption.Ptr()),info.iCaption.Length());
app2Changed(name);

ls.GetAppInfo(info, TUid::Uid((TUint32)settings->value("apps/app3",app3).toString().toULong(&ok,16)));
name=QString::fromRawData(reinterpret_cast<const QChar*>(info.iCaption.Ptr()),info.iCaption.Length());
app3Changed(name);

ls.GetAppInfo(info, TUid::Uid((TUint32)settings->value("apps/app4",app4).toString().toULong(&ok,16)));
name=QString::fromRawData(reinterpret_cast<const QChar*>(info.iCaption.Ptr()),info.iCaption.Length());
app4Changed(name);

ls.GetAppInfo(info, TUid::Uid((TUint32)settings->value("apps/app5",app5).toString().toULong(&ok,16)));
name=QString::fromRawData(reinterpret_cast<const QChar*>(info.iCaption.Ptr()),info.iCaption.Length());
app5Changed(name);
#endif

emit buttonChanged(settings->value("settings/button",KButton).toInt());
emit zoomChanged(settings->value("settings/zoom",KZoom).toInt());
emit gestureChanged(settings->value("settings/gesture",KGesture).toInt());
emit verSenseChanged(settings->value("settings/versense",KHorSensevity).toFloat());
emit horSenseChanged(settings->value("settings/horsense",KVerSensevity).toFloat());
emit hideSMSChanged(settings->value("settings/hidesms",KHideSMS).toInt());
emit notificationsChanged(settings->value("settings/notificattions",KShowNotifications).toInt());
emit playerAlbumChanged(settings->value("settings/zplayeralbum",KShowAlbumArt).toInt());
emit useWallpaperChanged(settings->value("settings/zusewallpaper",KUseWallpaper).toInt());
settings->beginGroup("keys");
QStringList sets=settings->allKeys();
for (int i=0;i<sets.length();i++) settings->remove(sets[i]);
for (int i=0;i<keys.length();i++) settings->setValue(QString::number(i),keys[i]);
settings->endGroup();

settings->beginGroup("settings");
qDebug()<<settings->allKeys();
settings->endGroup();
}

void Application::ChangeSetting(QString id, QVariant value)
{
#ifdef Q_OS_SYMBIAN
    TRAPD(err,
            {
            TBuf<255> a;
            a.Append(KMyServer);
            a.Append(_L("*"));
            TFindProcess processFinder(a); // by name, case-sensitive
            TFullName result;
            RProcess processHandle;
            while ( processFinder.Next(result) == KErrNone)
            {
               User::LeaveIfError(processHandle.Open ( processFinder, EOwnerThread));
               processHandle.Kill(KErrNone);
               processHandle.Close();
            }
            });
TRAPD(err2,
        {
        TBuf<255> a;
        a.Append(KMyServerStarter);
        a.Append(_L("*"));
        TFindProcess processFinder(a); // by name, case-sensitive
        TFullName result;
        RProcess processHandle;
        while ( processFinder.Next(result) == KErrNone)
        {
           User::LeaveIfError(processHandle.Open ( processFinder, EOwnerThread));
           processHandle.Kill(KErrNone);
           processHandle.Close();
        }
        });
#endif
if (id!="")
{

if (id.contains(QRegExp("app."))&&id!="appwork")
{
#ifdef Q_OS_SYMBIAN
    qDebug()<<"change app "<<value.toInt()<<QString::number((TUint32)apps[value.toInt()].iUid.iUid,16);
    settings->setValue("apps/"+id,QString::number((TUint32)apps[value.toInt()].iUid.iUid,16));
#endif
}
else settings->setValue("settings/"+id,value);
settings->sync();
settings->setValue("settings/appwork",settings->value("settings/appwork",KWork).toBool());
settings->setValue("settings/autostart",settings->value("settings/autostart",KAutostart).toBool());
settings->setValue("settings/picture",settings->value("settings/picture",KPicture).toString());
settings->setValue("settings/zoom",settings->value("settings/zoom",KZoom).toInt());
settings->setValue("settings/button",settings->value("settings/button",KButton).toInt());
settings->setValue("settings/hidesms",settings->value("settings/hidesms",KHideSMS).toInt());
settings->setValue("settings/notifications",settings->value("settings/notifications",KShowNotifications).toInt());
settings->setValue("settings/zplayeralbum",settings->value("settings/zplayeralbum",KShowAlbumArt).toInt());
settings->setValue("settings/zusewallpaper",settings->value("settings/zusewallpaper",KUseWallpaper).toInt());
settings->setValue("settings/gesture",settings->value("settings/gesture",KGesture).toInt());
settings->setValue("settings/horsense",settings->value("settings/horsense",KHorSensevity).toFloat());
settings->setValue("settings/versense",settings->value("settings/versense",KVerSensevity).toFloat());

settings->setValue("apps/app1",settings->value("apps/app1",app1).toString());
settings->setValue("apps/app2",settings->value("apps/app2",app2).toString());
settings->setValue("apps/app3",settings->value("apps/app3",app3).toString());
settings->setValue("apps/app4",settings->value("apps/app4",app4).toString());
settings->setValue("apps/app5",settings->value("apps/app5",app5).toString());

settings->sync();
}
#ifdef Q_OS_SYMBIAN
if (settings->value("settings/appwork",KWork).toBool())
{
    RApaLsSession session;
    session.Connect();
    CApaCommandLine* cmdLine = CApaCommandLine::NewLC();
    cmdLine->SetExecutableNameL(KMyServer);
    cmdLine->SetCommandL(EApaCommandRun);
    cmdLine->SetCommandL(EApaCommandBackground);
    User::LeaveIfError( session.StartApp(*cmdLine) );
    CleanupStack::PopAndDestroy(cmdLine);
    session.Close();
}
#endif

}


void Application::EditPic()
{
#ifdef Q_OS_SYMBIAN
CDesCArray* arr=new CDesCArrayFlat(3);
MGFetch::RunL(*arr,EImageFile,EFalse);
if (arr->Count()>0)
{
    QString file=QString::fromRawData(reinterpret_cast<const QChar*>(arr->MdcaPoint(0).Ptr()),arr->MdcaPoint(0).Length());
    file="file:///"+file;
    ChangeSetting("picture",file);
    file=file.replace("file:///","");
    TParse parse;
    TPtrC file1 (reinterpret_cast<const TText*>(file.constData()),file.length());
    CEikonEnv::Static()->FsSession().Parse(file1,parse);
    TBuf<255> a=parse.NameAndExt();
    file=QString::fromRawData(reinterpret_cast<const QChar*>(a.Ptr()),a.Length());
    emit pictureChanged(file);
}
#endif
}

void Application::Exit()
{

}

int Application::isKeyChecked(int index)
{
int key=keyMap.value(index,-1);
qDebug()<<"checking key "<<key<<keys.contains(key);
if (keys.contains(key)&&key!=-1) return 1;
else return 0;
}

void Application::checkKey(int index, bool checked)
{
int key=keyMap.value(index,-1);
if (checked)
{
if (!keys.contains(key)) keys.append(key);
}
else keys.removeOne(key);
settings->beginGroup("keys");
QStringList sets=settings->allKeys();
for (int i=0;i<sets.length();i++) settings->remove(sets[i]);
for (int i=0;i<keys.length();i++) settings->setValue(QString::number(i),keys[i]);
settings->endGroup();
settings->sync();
}

int Application::keysLen()
{
    return keys.length();
}

void Application::SortApps(QString filter)
{
#ifdef Q_OS_SYMBIAN
    apps.Reset();
    appModel.clear();
    QString name;
    for (int i=0;i<fullApps.Count();i++)
    {
        name=QString::fromRawData(reinterpret_cast<const QChar*>(fullApps[i].iCaption.Ptr()),fullApps[i].iCaption.Length());
       if (name.toLower().startsWith(filter.toLower()))
       {
       apps.Append(fullApps[i]);
       appModel.append(name);
       }
    }
    viewer.rootContext()->setContextProperty("appModel",appModel);
#endif
}

void Application::KillAnotherLockScreens()
{
    QStringList list;
    list<<"JellyUnlock";
    list<<"7Unlock";
    for (int i=0;i<list.length();i++)
        KillLockScreen(list[i]);
}

void Application::KillLockScreen(QString name)
{
    TPtrC n (static_cast<const TUint16*>(name.utf16()), name.length());
    TRAPD(err,
            {
            TBuf<255> a;
            a.Append(n);
            a.Append(_L("Srv.exe"));
            a.Append(_L("*"));
            TFindProcess processFinder(a); // by name, case-sensitive
            TFullName result;
            RProcess processHandle;
            while ( processFinder.Next(result) == KErrNone)
            {
               User::LeaveIfError(processHandle.Open ( processFinder, EOwnerThread));
               processHandle.Kill(KErrNone);
               processHandle.Close();
            }
            });
    TRAPD(err2,
        {
        TBuf<255> a;
        a.Append(n);
        a.Append(_L("Starter.exe"));
        a.Append(_L("*"));
        TFindProcess processFinder(a); // by name, case-sensitive
        TFullName result;
        RProcess processHandle;
        while ( processFinder.Next(result) == KErrNone)
        {
           User::LeaveIfError(processHandle.Open ( processFinder, EOwnerThread));
           processHandle.Kill(KErrNone);
           processHandle.Close();
        }
        });
    QString configPath;
    if (name=="SwipeUnlock") name="SwypeUnlock";
    configPath="C:\\System\\Apps\\"+name+"\\config.ini";
    QSettings* lockSettings=new QSettings(configPath,QSettings::IniFormat);
    lockSettings->setValue("settings/autostart",false);
    lockSettings->setValue("settings/appwork",false);
    lockSettings->sync();
    delete lockSettings;
    }

int Application::GetAnotherLockscreens()
    {
    int results=0;
    QStringList list;
    list<<"JellyUnlock";
    list<<"7Unlock";
    for (int i=0;i<list.length();i++)
        if (isLockScreenLaunched(list[i])) results++;
    return results;
    }

int Application::isLockScreenLaunched(QString name)
    {
     TPtrC n (static_cast<const TUint16*>(name.utf16()), name.length());
     int err1=-1;
        TRAP(err1,
            {
            TBuf<255> a;
            a.Append(n);
            a.Append(_L("Srv.exe"));
            a.Append(_L("*"));
            TFindProcess processFinder(a); // by name, case-sensitive
            TFullName result;
            RProcess processHandle;
            User::LeaveIfError(processFinder.Next(result));
            User::LeaveIfError(processHandle.Open ( processFinder, EOwnerThread));
            processHandle.Close();
            });
    qDebug()<<name<<err1;
    if (err1==KErrNotFound) return 0;
    else return 1;
    }

void Application::HideSplash()
    {
    qDebug()<<"Hide splash";
    splash->Hide();
    }
