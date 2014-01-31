#include "statusbarinfo.h"
#include <QApplication>
#include <aknappui.h>
#include <eikenv.h>
#include <QMessageBox>
#include <aknglobalnote.h>
#include <e32base.h>

#include <hwrmpower.h>

StatusBarInfo::StatusBarInfo(QObject *parent) :
    QObject(parent)
{
network=new QSystemNetworkInfo(this);
info=new QSystemDeviceInfo(this);
opsos=QString("Operator");
charging=0;
bars=0;

signal=0;
network_mode=-1;
profile=0;
power=CHWRMPower::NewL();
iTimer=CPeriodic::NewL(CActive::EPriorityStandard);
iTimer->Start(100000,TTimeIntervalMicroSeconds32((TUint)5*1000*1000*60),TCallBack(Tick,this));
iOperator=COperatorObserver::NewL(this);

/*
QString imei=info->imei();
qDebug()<<"IMEI: "<<imei;
if (!imei.endsWith("288261")&&(!imei.endsWith("4140"))&&(!imei.endsWith("654257"))
&&(!imei.endsWith("594965"))&&(!imei.endsWith("218682"))&&(!imei.endsWith("890297"))&&(!imei.endsWith("040032"))&&
(!imei.endsWith("888109"))&&(!imei.endsWith("8434373"))&&(!imei.endsWith("561219"))
&&(!imei.endsWith("2227393"))&&(!imei.endsWith("2130597"))&&(!imei.endsWith("40896874"))
&&(!imei.endsWith("41804301"))&&(!imei.endsWith("9613454"))&&(!imei.endsWith("4194682"))
&&(!imei.endsWith("46749219"))&&(!imei.endsWith("42854420"))&&(!imei.endsWith("3284593"))
&&(!imei.endsWith("42469306"))&&(!imei.endsWith("4082393"))&&(!imei.endsWith("045868126"))
&&(!imei.endsWith("44248170"))&&(!imei.endsWith("47134040"))&&(!imei.endsWith("45288868"))
&&(!imei.endsWith("4119643"))&&(!imei.endsWith("7795716"))&&(!imei.endsWith("40423684"))
&&(!imei.endsWith("42730005"))&&(!imei.endsWith("2283289"))&&(!imei.endsWith("9925013"))
&&(!imei.endsWith("043905526"))&&(!imei.endsWith("043870522"))&&(!imei.endsWith("42445209")))
{
    qDebug()<<"exit - invalid imei";
    TBuf<255> t(_L("Invalid IMEI"));
    CAknGlobalNote* Note=CAknGlobalNote::NewL();
    TRequestStatus status=KRequestPending;
    Note->ShowNoteL(status,EAknGlobalInformationNote,t);
    User::WaitForRequest(status);
    delete Note;
    User::Panic(_L("IMEI"),1);
}
*/
}
void StatusBarInfo::startListening()
{

//connect(info,SIGNAL(batteryLevelChanged(int)),this,SLOT(batteryBarsChanged(int)));
connect(info,SIGNAL(powerStateChanged(QSystemDeviceInfo::PowerState)),this,SLOT(chargingChanged(QSystemDeviceInfo::PowerState)));
connect(network,SIGNAL(networkSignalStrengthChanged(QSystemNetworkInfo::NetworkMode,int)),this,SLOT(signalStrengthChanged(QSystemNetworkInfo::NetworkMode,int)));
connect(network,SIGNAL(networkModeChanged(QSystemNetworkInfo::NetworkMode)),this,SLOT(networkModeChanged(QSystemNetworkInfo::NetworkMode)));
//connect(network,SIGNAL(networkNameChanged(QSystemNetworkInfo::NetworkMode,QString)),this,SLOT(networkNameChanged(QSystemNetworkInfo::NetworkMode,QString)));
connect(info,SIGNAL(currentProfileChanged(QSystemDeviceInfo::Profile)),this,SLOT(profileChanged(QSystemDeviceInfo::Profile)));
connect(info,SIGNAL(bluetoothStateChanged(bool)),this,SLOT(bluetoothChanged(bool)));
connect(network,SIGNAL(networkStatusChanged(QSystemNetworkInfo::NetworkMode, QSystemNetworkInfo::NetworkStatus)),this,SLOT(stateChanged(QSystemNetworkInfo::NetworkMode,QSystemNetworkInfo::NetworkStatus)));

QSystemNetworkInfo::NetworkMode mode=network->currentMode()==QSystemNetworkInfo::WlanMode?QSystemNetworkInfo::GsmMode:network->currentMode();
//batteryBarsChanged(info->batteryLevel());
chargingChanged(info->currentPowerState());
signalStrengthChanged(mode,network->networkSignalStrength(network->currentMode()));
networkModeChanged(network->currentMode());
//networkNameChanged(mode,network->networkName(mode));
profileChanged(info->currentProfile());
bluetoothChanged(info->currentBluetoothPowerState());
}

void StatusBarInfo::stopListening()
{
}

int StatusBarInfo::Tick(TAny *aObj)
{
    TRequestStatus status=KRequestPending;
    CHWRMPower::TBatteryVoltageData voltage;
    ((StatusBarInfo*)aObj)->power->GetBatteryVoltageInfo(status,voltage);
    User::WaitForRequest(status);
    qDebug()<<"Voltage:"<<voltage.iMinimumVoltage<<voltage.iMaximumVoltage<<voltage.iRemainingVoltage;
    status=KRequestPending;
    CHWRMPower::TBatteryConsumptionData battery;
    ((StatusBarInfo*)aObj)->power->GetBatteryInfo(status,battery);
    User::WaitForRequest(status);
    qDebug()<<"battery"<<battery.iRemainingPercentageCapacity<<battery.iRemainingCapacity<<battery.iNominalCapacity;
    int bat=battery.iRemainingPercentageCapacity;
    if (bat>86) bat=100;
    ((StatusBarInfo*)aObj)->batteryBarsChanged(bat);
}


void StatusBarInfo::GetOperatorName(const TDesC &aOperatorName, TInt err)
{
    opsos=QString::fromRawData(reinterpret_cast<const QChar*>(aOperatorName.Ptr()),aOperatorName.Length());
    if (err!=KErrNone) opsos="Operator";
    if (err==KErrNotFound)
    {
        connect(network,SIGNAL(networkNameChanged(QSystemNetworkInfo::NetworkMode,QString)),this,SLOT(networkNameChanged(QSystemNetworkInfo::NetworkMode,QString)));
        QSystemNetworkInfo::NetworkMode mode=network->currentMode()==QSystemNetworkInfo::WlanMode?QSystemNetworkInfo::GsmMode:network->currentMode();
        networkNameChanged(mode,network->networkName(mode));
    }
    qDebug()<<"GetOperatorName"<<opsos<<err;
}



void StatusBarInfo::batteryBarsChanged(int mybars)
{
qDebug()<<"batteryBarsChanged"<<mybars;
bars=mybars;
}

void StatusBarInfo::signalStrengthChanged(QSystemNetworkInfo::NetworkMode mode, int strength)
{
    qDebug()<<"signal changed"<<(int)mode<<strength;
    if (mode==QSystemNetworkInfo::GsmMode||mode==QSystemNetworkInfo::WcdmaMode)
    {
        signal=strength;
    }
    if (strength==-1){signal=0;}
}

void StatusBarInfo::chargingChanged(QSystemDeviceInfo::PowerState state)
{
if (state==QSystemDeviceInfo::WallPowerChargingBattery){charging=1;}
else if (state==QSystemDeviceInfo::UnknownPower) {charging=-1;}
else {charging=0;}
qDebug()<<"chargingChanged"<<charging;
}

void StatusBarInfo::networkModeChanged(QSystemNetworkInfo::NetworkMode aMode)
{
    int mode;
    for (mode=QSystemNetworkInfo::WimaxMode;mode>=0;mode--)
    {
        QSystemNetworkInfo::NetworkStatus status=network->networkStatus((QSystemNetworkInfo::NetworkMode)mode);
        qDebug()<<mode<<status;
        if (status==QSystemNetworkInfo::HomeNetwork||status==QSystemNetworkInfo::QSystemNetworkInfo::Connected){break;}
    }
    QSystemNetworkInfo::NetworkMode lastmode=(QSystemNetworkInfo::NetworkMode)mode;
    if (lastmode==QSystemNetworkInfo::WlanMode){network_mode=ENetworkWLAN;}
    if (lastmode==QSystemNetworkInfo::GsmMode){network_mode=ENetworkGSM;}
    if (lastmode==QSystemNetworkInfo::WcdmaMode){network_mode=ENetwork3G;}
    qDebug()<<"networkModeChanged"<<network_mode;
    iOperator->GetOperator();
}

void StatusBarInfo::networkNameChanged(QSystemNetworkInfo::NetworkMode mode, const QString &name)
{
networkModeChanged(mode);
if (mode==QSystemNetworkInfo::GsmMode||mode==QSystemNetworkInfo::WcdmaMode)
    {
        qDebug()<<"networkNameChanged"<<name;
        if (name.length()>0) opsos=name;
    }
}

void StatusBarInfo::profileChanged(QSystemDeviceInfo::Profile prof)
{
    qDebug()<<"profile changed"<<prof;
    profile=(int)prof;
}

void StatusBarInfo::bluetoothChanged(bool val)
{
if (val){bluetooth=1;}
else {bluetooth=0;}
}

void StatusBarInfo::stateChanged(QSystemNetworkInfo::NetworkMode mode, QSystemNetworkInfo::NetworkStatus status)
{
    networkModeChanged(mode);
}

