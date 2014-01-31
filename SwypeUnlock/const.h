#ifndef CONST_H
#define CONST_H
#ifdef Q_OS_SYMBIAN
   #define KLangSettingFile "C:\\system\\apps\\SwypeUnlock\\lang\\lang.setting"
   #define KLangFile "C:\\system\\apps\\SwypeUnlock\\lang\\strings.l"
   #define KConfigFile "C:\\System\\Apps\\SwypeUnlock\\config.ini"
   #define KFirstStart "C:\\System\\Apps\\SwypeUnlock\\firststart"
#else
   #define KLangSettingFile "D:\\Symbian\\QtSDK\\workspace\\SwypeUnlock\\lang\\lang.setting"
   #define KLangFile "D:\\Symbian\\QtSDK\\workspace\\SwypeUnlock\\lang\\strings.l"
   #define KConfigFile "config.ini"
   #define KFirstStart "firststart"
#endif
#ifdef Q_OS_SYMBIAN
_LIT(KMyServer,"SwipeUnlockSrv.exe");
_LIT(KMyServerStarter,"SwipeUnlockStarter.exe");
#endif


const bool KAutostart=true;
const bool KWork=true;
#define KPicture "file:///C:\\Data\\Images\\MeeGo.png"
const int KButton=0;
const int KZoom=1;
const int KTime=0;
const int KGesture=0;
const int KHideSMS=0;
const int KShowNotifications=1;
const int KShowAlbumArt=1;
const float KHorSensevity=0.5;
const float KVerSensevity=0.5;
const int KUseWallpaper=0;
const QString app1="101F4CCE";
const QString app2="101F4CD5";
const QString app3="101F857A";
const QString app4="102072C3";
const QString app5="10008D39";
#endif // CONST_H
