#ifndef WINDOWMOVER_H
#define WINDOWMOVER_H

#include <e32std.h>
#include <e32base.h>
#include <coecntrl.h>
#include <w32std.h>
#include <QDeclarativeView>
#include <QObject>
#include <qmlapplicationviewer.h>
#include <QSettings>
#include "MyAnimation.h"
#include <QTimer>
class MWindowMover
{
public:
    virtual void Hide()=0;
    virtual void MovingChanged(bool state)=0;

};

class CWindowMover : public QObject, public CCoeControl
    {
    Q_OBJECT
public:
    enum TAnimationAxis{
       EXAxis,
       EYAxis
    };
    ~CWindowMover();
    static CWindowMover* NewL(MWindowMover* m,QmlApplicationViewer* v,RWsSession* aWg);
    static CWindowMover* NewLC(MWindowMover* m,QmlApplicationViewer* v,RWsSession* aWg);
private:
    QSettings* settings;
    MyAnimation* xAnim;
    MyAnimation* yAnim;
    int prevY,prevYD;
    void startAnim(TAnimationAxis axis,int to);
    QmlApplicationViewer* viewer;
    int axisX,axisY;
    bool axisSet;
    CWindowMover(QObject* parent);
    void ConstructL(MWindowMover* m,QmlApplicationViewer* v,RWsSession* aWs);
    void HandlePointerEventL(const TPointerEvent& aPointerEvent);
    RWindowGroup* iWinGroup;
    TPoint iPointerPoint1;
    TPoint iPointerPoint2;
    MWindowMover* iCallBack;
    TBool iDragged;
    void Draw(const TRect&) const;
    void SimulatePointer(TPointerEvent aPointer);
    QTimer* iTimer;
private slots:
    void xAnimChanged(const QVariant & value );
    void yAnimChanged(const QVariant & value );
    void finished();
    void checkLaunchArea();
public slots:
    void show();
    void toZero();
    void hide();
    void changeSize(int w,int h);
signals:
    void MovingChanged(bool);
    void showLaunchArea();
    };
#endif // WINDOWMOVER_H
