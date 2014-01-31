#ifndef STATUSBARINFO_H
#define STATUSBARINFO_H
#include <QObject>

#include <QSystemDeviceInfo>
#include <QSystemNetworkInfo>

#include <hwrmpower.h>
#include <hwrmpowerstatesdkpskeys.h>
#include "operatorobserver.h"

QTM_USE_NAMESPACE

enum{
ENetworkGSM=0,
ENetwork3G=1,
ENetworkWLAN=2
};

class StatusBarInfo : public QObject, public MOperatorObserver

{
    Q_OBJECT
public:
    int signal;
    int bars;
    int charging;
    int network_mode;
    int profile;
    int bluetooth;
    QString opsos;
    explicit StatusBarInfo(QObject *parent = 0);
    QSystemNetworkInfo* network;
    QSystemDeviceInfo* info;
    void startListening();
    void stopListening();
    CHWRMPower* power;
    static int Tick(TAny* aObj);
    CPeriodic* iTimer;
    COperatorObserver* iOperator;
    void GetOperatorName(const TDesC &aOperatorName, TInt err);
signals:

public slots:
    void profileChanged(QSystemDeviceInfo::Profile);
    void signalStrengthChanged(QSystemNetworkInfo::NetworkMode mode, int strength);
    void batteryBarsChanged(int bars);
    void chargingChanged(QSystemDeviceInfo::PowerState state);
    void networkModeChanged(QSystemNetworkInfo::NetworkMode mode);
    void networkNameChanged( QSystemNetworkInfo::NetworkMode mode, const QString & name );
    void bluetoothChanged(bool val);
    void stateChanged( QSystemNetworkInfo::NetworkMode mode, QSystemNetworkInfo::NetworkStatus status );
};

#endif // STATUSBARINFO_H
