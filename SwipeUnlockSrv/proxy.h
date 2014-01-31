#ifndef PROXY_H
#define PROXY_H

#include <QObject>
#include <application.h>
class Proxy : public QObject
{
    Q_OBJECT
public:
    explicit Proxy(Application* app, QObject *parent = 0);
    Application* App;
signals:
    void sigHide();
    void sigRestartTimer();
    void sigMovingChanged(bool state);
    void sigPlay();
    void sigPause();
    void sigNext();
    void sigPrevious();
    void sigSeekForward();
    void sigSeekBack();
    void sigStopSeeking();
    void setSize(int w,int h);
    void sigSeekToPercent(int pos);
    void sigGetState();
public slots:
    void Hide();
    void restartTimer();
    void MovingChanged(bool state);
    void Play();
    void Pause();
    void Next();
    void Previous();
    void SeekForward();
    void SeekBack();
    void StopSeeking();
    void openViewer(int type);
    void screenChanged();
    void SeekToPos(int percent);
    void GetState();

};

#endif // PROXY_H
