#ifndef SUSPENDER_H
#define SUSPENDER_H

#include <QObject>
#include <e32base.h>
#include <application.h>
#include <proxy.h>
#include <windowmover.h>

class Suspender : public QObject
{
    Q_OBJECT
     QTimer* iTimer;
public:
    explicit Suspender(Proxy* pr,QObject *parent = 0);
     Proxy* proxy;
     bool iSuspended;
     CWindowMover* iMover;
     bool fp2;
     Application* application;
signals:
    void sendId(int id);
    void maySleep();
public slots:
    void Suspend(int aShow);
    void unSuspend();
    void setupQML(Application* app);
    void Tick();
    void setNotSleep();
};

#endif // SUSPENDER_H
