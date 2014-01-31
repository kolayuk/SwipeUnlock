# Add more folders to ship with the application, here
folder_01.source = qml/SwipeUnlockSrv
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

QT += network
CONFIG += MOBILITY
MOBILITY+=systeminfo
MOBILITY+=messaging
MOBILITY+=contacts
MOBILITY+=sensors
symbian:RSS_RULES += "hidden = KAppIsHidden;"
symbian {

    # Define rss file for autoboot
    autoStartBlock = \
    "SOURCEPATH      ." \
    "START RESOURCE startup.rss" \
    "END"

    MMP_RULES += autoStartBlock
    MMP_RULES+="DEBUGGABLE"

    # Deploy rsc file to package.
    deployRscFile = "\"$${EPOCROOT}epoc32/data/startup.rsc\" - \"C:/private/101f875a/import/[2004423C].rsc\" \
    \"D:/Symbian/9.4/S60_5th_Edition_SDK_v1.0/epoc32/release/armv5/urel/SwipeUnlockAnim.dll\" - \"!:\sys\bin\SwipeUnlockAnim.dll\""
    deployFiles.pkg_postrules += deployRscFile
    DEPLOYMENT += deployFiles
}

packageheader = "$${LITERAL_HASH}{\"SwypeUnlockSrv\"}, (0x2004423B), 1, 0, 0, TYPE=SA"
info.pkg_prerules=packageheader
symbian:DEPLOYMENT+=info
symbian:TARGET.EPOCHEAPSIZE = 0x19000 0x4000000
symbian:TARGET.EPOCSTACKSIZE = 0x10000
symbian:TARGET.UID3 = 0x2004423C
symbian:TARGET.CAPABILITY +=SwEvent ReadUserData Location WriteDeviceData ReadDeviceData NetworkServices PowerMgmt ProtServ
symbian:SOURCES+=CenRepObserver.cpp FgrObserver.cpp aiplayerpluginengine.cpp clientimagecommander.cpp clientdll.cpp
symbian:HEADERS+=CenRepObserver.h FgrObserver.h aiplayerpluginengine.h akncapserverclient.h clientimagecommander.h clientdll.h fmradiointernalpskeys.h
symbian:INCLUDEPATH+=D:/Symbian/QtSDK112/Symbian/SDKs/Symbian3Qt473/epoc32/include/mw
symbian:INCLUDEPATH+=D:\Symbian\QtSDK112\Symbian\SDKs\Symbian3Qt473\epoc32\include
symbian:LIBS+=-lapgrfx
symbian:LIBS+=-leikcore
symbian:LIBS+=-lavkon
symbian:LIBS+=-leiksrv
symbian:LIBS+=-lcone
symbian:LIBS+=-lapparc
symbian:LIBS+=-lws32
symbian:LIBS+=-lcentralrepository
symbian:LIBS+=-lmpxcollectionutility
symbian:LIBS+=-lmpxcommon
symbian:LIBS+=-lmpxplaybackutility
symbian:LIBS+=-lefsrv
symbian:LIBS+=-llogcli
symbian:LIBS+=-ltzclient
symbian:LIBS+=-lakncapserverclient
symbian:LIBS+=-lgdi
symbian:LIBS+=-lbitgdi
symbian:LIBS+=-laknskins
symbian:LIBS+=-lfbscli
symbian:LIBS+=-legul
symbian:LIBS+=-laknicon
symbian:LIBS+=-letel3rdparty
symbian:LIBS+=-lmsgs
symbian:LIBS+=-lsmcm
symbian:LIBS+=-lgsmu
symbian:LIBS+=-lmtur
symbian:LIBS+=-letext
symbian:LIBS+=-laknnotify
symbian:LIBS+=-leiksrv
symbian:LIBS+=-lestor
symbian:LIBS+=-lhwrmpowerclient
symbian:LIBS+=-lhal
symbian:LIBS+=-lthumbnailmanager
symbian:LIBS+=-lIclExtJpegApi
symbian:LIBS+=-lbitmaptransforms
symbian:LIBS+=-limageconversion
symbian:LIBS+=-lMetaDataUtility

SOURCES += main.cpp \
    application.cpp \
    statusbarinfo.cpp \
    playercontroller.cpp \
    notifyprovider.cpp \
    logmonitor.cpp \
    localizer.cpp \
    suspender.cpp \
    proxy.cpp \
    propertyobserver.cpp \
    animdll.cpp \
    iconprovider.cpp \
    CallsMonitor.cpp \
    SMSReciever.cpp \
    mpximageutil.cpp \
    mpxalbumartutil.cpp \
    albumartprovider.cpp \
    windowmover.cpp \
    myanimation.cpp \
    operatorobserver.cpp \
    skinbgprovider.cpp

# Please do not modify the following two lines. Required for deployment.
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

HEADERS += \
    application.h \
    statusbarinfo.h \
    playercontroller.h \
    const.h \
    notifyprovider.h \
    logmonitor.h \
    localizer.h \
    suspender.h \
    proxy.h \
    propertyobserver.h \
    animdll.h \
    iconprovider.h \
    callsMonitor.h \
    SMSReciever.h \
    thumbnailobjectsource.h \
    thumbnailmanagerobserver.h \
    thumbnailmanager.h \
    thumbnaildata.h \
    mpxplaybackutility.h \
    mpxplaybackmessagedefs.h \
    mpximageutil.h \
    mpxalbumartutil.h \
    imageframeformats.hrh \
    imageframeconst.hrh \
    imageframeconst.h \
    imageframe.h \
    IclExtJpegApi.h \
    iclexifimageframe.h \
    iclexif.h \
    albumartprovider.h \
    windowmover.h \
    myanimation.h \
    operatorobserver.h \
    skinbgprovider.h

OTHER_FILES += \
    main.qml













