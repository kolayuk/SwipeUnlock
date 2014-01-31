#include "proxy.h"
#include <QDebug>
#include <e32base.h>
#include <eikenv.h>
#include <w32std.h>
Proxy::Proxy(Application* app,QObject *parent) :
    QObject(parent)
{
App=app;
}

void Proxy::Hide()
{
    qDebug()<<"Proxy::Hide"<<RThread().Id().Id();
/*
    RThread t;
    TThreadId id(App->thrID);
    qDebug()<<"err:"<<t.Open(id,EOwnerProcess);
    qDebug()<<"resume in proxy:"<<t.Id().Id();
    t.Resume();
    t.Close();
*/
    emit sigHide();
//QMetaObject::invokeMethod(App, "Hide", Qt::QueuedConnection);
}

void Proxy::restartTimer()
{
qDebug()<<"Proxy::restartTimer";
emit sigRestartTimer();
}

void Proxy::MovingChanged(bool state)
{
    emit sigMovingChanged(state);
}

void Proxy::Play()
{
emit sigPlay();
}

void Proxy::Pause()
{
emit sigPause();
}

void Proxy::Next()
{
emit sigNext();
}

void Proxy::Previous()
{
emit sigPrevious();
}

void Proxy::SeekForward()
{
emit sigSeekForward();
}

void Proxy::SeekBack()
{
emit sigSeekBack();
}

void Proxy::StopSeeking()
{
    emit sigStopSeeking();
}

void Proxy::openViewer(int type)
{
}

void Proxy::screenChanged()
{
/*
qDebug()<<"Proxy::screenChanged, thread "<<RThread().Id().Id();
int w=CEikonEnv::Static()->ScreenDevice()->SizeInPixels().iWidth;
int h=CEikonEnv::Static()->ScreenDevice()->SizeInPixels().iHeight;
qDebug()<<"Size:"<<w<<h;
emit setSize(w,h);
*/
}

void Proxy::SeekToPos(int percent)
{
    emit sigSeekToPercent(percent);
}

void Proxy::GetState()
{
    emit sigGetState();
}
