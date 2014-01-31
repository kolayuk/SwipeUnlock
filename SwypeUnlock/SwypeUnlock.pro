# Add more folders to ship with the application, here
folder_01.source = qml/SwypeUnlock
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

qt_components.pkg_prerules += "(0x200346DE), 1, 0, 0, {\"Qt Components\"}"
symbian:DEPLOYMENT += qt_components
mob.pkg_prerules += "(0x2002AC89), 1, 1, 3, {\"QtMobility\"}"
symbian:DEPLOYMENT += mob
TARGET="SwipeUnlock"
symbian:DEPLOYMENT.display_name="SwipeUnlock"
symbian:TARGET.UID3 = 0x2004423B
symbian:TARGET.CAPABILITY += WriteDeviceData ReadDeviceData ReadUserData PowerMgmt
CONFIG += qt-components

symbian:INCLUDEPATH+=D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/include/mw
symbian:INCLUDEPATH+=D:\Symbian\QtSDK112\Symbian\SDKs\Symbian3Qt473\epoc32\include
#MMP_RULES+="DEBUGGABLE"
locs.source=D:\Symbian\QtSDK\workspace\SwypeUnlock\lang
locs.target = C:\system\apps\SwypeUnlock
symbian:DEPLOYMENTFOLDERS+=locs

wp1 =  "\"D:\\Symbian\\QtSDK\\workspace\\SwipeUnlockSrv\\meego.png\"		  -\"C:\\Data\\Images\\MeeGo.png\" \
\"D:\\Symbian\\QtSDK\\workspace\\SwipeUnlockSrv\\splash_v.jpg\"		  -\"C:\\System\\Apps\\SwypeUnlock\\splash_v.jpg\" \
\"D:\\Symbian\\QtSDK\\workspace\\SwipeUnlockSrv\\splash_h.jpg\"		  -\"C:\\System\\Apps\\SwypeUnlock\\splash_h.jpg\" "
wp.pkg_postrules = wp1
symbian:DEPLOYMENT += wp
symbian:ICON="SwypeUnlock.svg"
#qml.source=D:\Symbian\QtSDK\workspace\SwipeUnlockSrv\qml
#qml.target = !:\\private\e48dd893\qml
#symbian:DEPLOYMENTFOLDERS+=qml

vendorinfo =  "%{\"Alexander Fokin\"}" \
    ":\"Alexander Fokin\""
vendor.pkg_prerules = vendorinfo
symbian:DEPLOYMENT += vendor

packageheader = "$${LITERAL_HASH}{\"SwipeUnlock\"}, (0x2004423C), 1, 8, 0, TYPE=SA"
info.pkg_prerules=packageheader
symbian:DEPLOYMENT+=info

symbian:LIBS+=-lmgfetch -lbafl -lefsrv
symbian:LIBS+=-leikcore
symbian:LIBS+=-lavkon
symbian:LIBS+=-leiksrv
symbian:LIBS+=-lcone
symbian:LIBS+=-lapparc
symbian:LIBS+=-lapgrfx
symbian:LIBS+=-lbitgdi -lapmime -limageconversion -lws32 -lfbscli -lgdi


SOURCES += main.cpp localizer.cpp \
    application.cpp
HEADERS += localizer.h \
    application.h \
    const.h
symbian:HEADERS+=SplashControl.h
symbian:SOURCES+=SplashControl.cpp


# Please do not modify the following two lines. Required for deployment.
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

srv =  "\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/release/$(PLATFORM)/$(TARGET)/SwipeUnlockSrv.exe\" - \"!:\sys\bin\SwipeUnlockSrv.exe\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/resource/apps/SwipeUnlockSrv.rsc\" - \"!:\resource\apps\SwipeUnlockSrv.rsc\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/resource/apps/SwipeUnlockSrv.mif\" - \"!:\resource\apps\SwipeUnlockSrv.mif\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/10003a3f/import/apps/SwipeUnlockSrv_reg.rsc\" - \"!:\private\10003a3f\import\apps\SwipeUnlockSrv_reg.rsc\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/abc-settings.txt\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\abc-settings.txt\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/Button.qml\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\Button.qml\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/DigitalClock.qml\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\DigitalClock.qml\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/main.qml\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\main.qml\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/Notifer.qml\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\Notifer.qml\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/notify/background.png\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\notify\background.png\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/notify/call.png\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\notify\call.png\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/notify/email.png\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\notify\email.png\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/notify/sms.png\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\notify\sms.png\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/player/next-pressed.png\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\player\next-pressed.png\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/player/next.png\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\player\next.png\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/player/pause-pressed.png\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\player\pause-pressed.png\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/player/pause.png\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\player\pause.png\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/player/play-pressed.png\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\player\play-pressed.png\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/player/play.png\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\player\play.png\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/player/prev.png\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\player\prev.png\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/player/prev-pressed.png\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\player\prev-pressed.png\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/player/stop.png\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\player\stop.png\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/player/stop-pressed.png\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\player\stop-pressed.png\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/Player.qml\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\Player.qml\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/LaunchArea.qml\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\LaunchArea.qml\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/status-icons/icon-s-status-3g-active.png\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\status-icons\icon-s-status-3g-active.png\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/status-icons/icon-s-status-battery-low.png\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\status-icons\icon-s-status-battery-low.png\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/status-icons/icon-s-status-battery-verylow.png\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\status-icons\icon-s-status-battery-verylow.png\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/status-icons/icon-s-status-battery1.png\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\status-icons\icon-s-status-battery1.png\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/status-icons/icon-s-status-battery2.png\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\status-icons\icon-s-status-battery2.png\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/status-icons/icon-s-status-battery3.png\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\status-icons\icon-s-status-battery3.png\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/status-icons/icon-s-status-battery4.png\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\status-icons\icon-s-status-battery4.png\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/status-icons/icon-s-status-battery5.png\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\status-icons\icon-s-status-battery5.png\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/status-icons/icon-s-status-battery6.png\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\status-icons\icon-s-status-battery6.png\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/status-icons/icon-s-status-battery7.png\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\status-icons\icon-s-status-battery7.png\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/status-icons/icon-s-status-battery8.png\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\status-icons\icon-s-status-battery8.png\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/status-icons/icon-s-status-bluetooth.png\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\status-icons\icon-s-status-bluetooth.png\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/status-icons/icon-s-status-charger.png\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\status-icons\icon-s-status-charger.png\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/status-icons/icon-s-status-flight-mode.png\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\status-icons\icon-s-status-flight-mode.png\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/status-icons/icon-s-status-gsm-active.png\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\status-icons\icon-s-status-gsm-active.png\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/status-icons/icon-s-status-network0.png\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\status-icons\icon-s-status-network0.png\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/status-icons/icon-s-status-network1.png\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\status-icons\icon-s-status-network1.png\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/status-icons/icon-s-status-network2.png\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\status-icons\icon-s-status-network2.png\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/status-icons/icon-s-status-network3.png\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\status-icons\icon-s-status-network3.png\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/status-icons/icon-s-status-network4.png\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\status-icons\icon-s-status-network4.png\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/status-icons/icon-s-status-network5.png\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\status-icons\icon-s-status-network5.png\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/status-icons/icon-s-status-no-gsm-connection.png\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\status-icons\icon-s-status-no-gsm-connection.png\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/status-icons/icon-s-status-offline.png\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\status-icons\icon-s-status-offline.png\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/status-icons/icon-s-status-silent.png\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\status-icons\icon-s-status-silent.png\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/status-icons/icon-s-status-wlan-active.png\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\status-icons\icon-s-status-wlan-active.png\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/status-icons/icon-s-status-wlan.png\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\status-icons\icon-s-status-wlan.png\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/StatusBar.qml\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\StatusBar.qml\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/z/private/2004423c/qml/SwipeUnlockSrv/NotiferDelegate.qml\" - \"!:\private\2004423c\qml\SwipeUnlockSrv\NotiferDelegate.qml\" \
\"D:/Symbian/QtSDK/workspace/SwypeUnlock/qml/SwypeUnlock/logo_small.png\" - \"C:\System\Apps\SwypeUnlock\firststart\" \
\"D:/Symbian/9.4/S60_5th_Edition_SDK_v1.0/epoc32/release/armv5/urel/SwipeUnlockAnim.dll\" - \"!:\sys\bin\SwipeUnlockAnim.dll\" \
\"D:/Symbian/9.4/S60_5th_Edition_SDK_v1.0/epoc32/release/armv5/urel/SwipeUnlockStarter.exe\" - \"C:\sys\bin\SwipeUnlockStarter.exe\" \
\"D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/data/startup.rsc\" - \"C:/private/101f875a/import/[2004423C].rsc\""
srv1.pkg_postrules = srv
symbian:DEPLOYMENT += srv1

symbian:DEPLOYMENT.installer_header = "$${LITERAL_HASH}{\"SwipeUnlock\"},(0x2002CCCF),1,8,0"



