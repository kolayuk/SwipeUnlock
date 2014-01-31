#include "windowmover.h"

#include <eikenv.h>
#include <w32std.h>
#include <QDebug>
#include <apgwgnam.h>
#include <const.h>
#include <QApplication>

CWindowMover::CWindowMover(QObject* parent): QObject(parent)
    {
    // No implementation required
    }

CWindowMover::~CWindowMover()
    {
    }

CWindowMover* CWindowMover::NewLC(MWindowMover* m,QmlApplicationViewer* v,RWsSession* aWg)
    {
    CWindowMover* self = new (ELeave) CWindowMover(NULL);
    CleanupStack::PushL(self);
    self->ConstructL(m,v,aWg);
    return self;
}

void CWindowMover::startAnim(CWindowMover::TAnimationAxis axis, int to)
{
    CCoeControl* control =(viewer->winId());
    if (axis==EXAxis)
    {
    xAnim->setStartValue(QVariant(control->Position().iX));
    xAnim->setEndValue(QVariant(to));
    xAnim->start();
    qDebug()<<"start x anim"<<to;

    }
    else
    {
        yAnim->setStartValue(QVariant(control->Position().iY));
        yAnim->setEndValue(QVariant(to));
        yAnim->start();
        qDebug()<<"start y anim"<<to;
    }
}


CWindowMover* CWindowMover::NewL(MWindowMover* m,QmlApplicationViewer* v,RWsSession* aWg)
    {
    CWindowMover* self = CWindowMover::NewLC(m,v,aWg);
    CleanupStack::Pop(); // self;
    return self;
    }

void CWindowMover::ConstructL(MWindowMover* m,QmlApplicationViewer* v,RWsSession* aWs)
    {

    iWinGroup=new (ELeave) RWindowGroup(*aWs);
    iWinGroup->Construct((TUint32)&iWinGroup, EFalse);
    iWinGroup->EnableReceiptOfFocus(EFalse); // Don't capture any key events.
    iWinGroup->SetOrdinalPosition(0, ECoeWinPriorityAlwaysAtFront+KAddPriority+1);

    CApaWindowGroupName* wn=CApaWindowGroupName::NewL(*aWs);
    wn->SetHidden(ETrue);
    wn->SetSystem(ETrue);
    wn->SetWindowGroupName(*iWinGroup);
    delete wn;

    iCallBack=m;
    viewer=v;
    iDragged=EFalse;
    CreateWindowL(iWinGroup);
    SetPointerCapture(ETrue);
    EnableDragEvents();
    // for transparency
    TRgb backgroundColour = KRgbWhite; // for example
//#ifndef _DEBUG
    if(KErrNone == Window().SetTransparencyAlphaChannel())
        {backgroundColour.SetAlpha(0);}
//#endif
    Window().SetBackgroundColor(backgroundColour);
    //SetSize(TSize(1,1));
    MakeVisible(EFalse);
    SetExtentToWholeScreen();

    settings=new QSettings(KConfigFile,QSettings::IniFormat);

    xAnim=new MyAnimation();
    yAnim=new MyAnimation();
    //QEasingCurve curve=new QEasingCurve(QEasingCurve::OutQuad);
    xAnim->setEasingCurve(QEasingCurve::OutQuad);
    yAnim->setEasingCurve(QEasingCurve::OutQuad);
    xAnim->setDuration(200);
    yAnim->setDuration(200);
    connect(xAnim,SIGNAL(valueChanged(QVariant)),this,SLOT(xAnimChanged(QVariant)));
    connect(yAnim,SIGNAL(valueChanged(QVariant)),this,SLOT(yAnimChanged(QVariant)));
    connect(yAnim,SIGNAL(finished()),this,SLOT(finished()));
    connect(xAnim,SIGNAL(finished()),this,SLOT(finished()));
    iTimer=new QTimer();
    iTimer->setInterval(400);
    iTimer->setSingleShot(false);
    connect(iTimer,SIGNAL(timeout()),this,SLOT(checkLaunchArea()));
    ActivateL();
    int gest=settings->value("settings/gesture").toInt();
    if (gest==0) axisSet=false;
    else if (gest==1) {axisX=1;axisY=0; axisSet=true;}
    else if (gest==2) {axisX=0;axisY=1; axisSet=true;}
    }

void CWindowMover::HandlePointerEventL(const TPointerEvent& aPointerEvent)
    {
    CCoeControl* control =(viewer->winId());
    if (aPointerEvent.iType == TPointerEvent::EButton1Down)
        {
        iPointerPoint1=aPointerEvent.iPosition;
        iPointerPoint2=aPointerEvent.iPosition;
        MovingChanged(true);

        QGraphicsSceneMouseEvent pressEvent(QEvent::GraphicsSceneMousePress);
        pressEvent.setScenePos(QPointF(iPointerPoint1.iX-control->Position().iX, iPointerPoint1.iY-control->Position().iY));
        qDebug()<<pressEvent.scenePos().x()<<pressEvent.scenePos().y();
        pressEvent.setButton(Qt::LeftButton);
        pressEvent.setButtons(Qt::LeftButton);
        QApplication::sendEvent(viewer->scene(), &pressEvent);
        }
    else if (aPointerEvent.iType == TPointerEvent::EDrag)
        {
        iDragged=ETrue;
        TInt dx=aPointerEvent.iPosition.iX-iPointerPoint1.iX;
        TInt dy=aPointerEvent.iPosition.iY-iPointerPoint1.iY;
        if (!axisSet)
        {
            if (abs(dy)>abs(dx)) {axisX=0; axisY=1;}
            else {axisX=1;axisY=0;}
            axisSet=true;
        }
        RWindow rWindow=(control->Window());
        control->SetPosition(TPoint(dx*axisX,dy*axisY));
        control->DrawBackground(TRect(control->Position(),control->Size()));
        }
    else if (aPointerEvent.iType==TPointerEvent::EButton1Up)
        {
        iPointerPoint2=aPointerEvent.iPosition;
        //MakeVisible(EFalse);
        int gest=settings->value("settings/gesture").toInt();
        if (gest==0) axisSet=false;

        float horSense=settings->value("settings/horsense",0.5).toFloat();
        float verSense=settings->value("settings/versense",0.5).toFloat();
        int width=control->Size().iWidth;
        int height=control->Size().iHeight;
        int x=control->Position().iX;
        int y=control->Position().iY;
        qDebug()<<"("<<x<<","<<y<<")"<<horSense<<verSense;
        if (x>(horSense)*width)
           {startAnim(EXAxis,width);}
        else if (x<(-horSense)*width)
           {startAnim(EXAxis,-width);}
        else if (x!=0)
           {startAnim(EXAxis,0);}
        if (y>(verSense)*height)
           {startAnim(EYAxis,height);}
        else if (y<(-verSense)*height)
           {startAnim(EYAxis,-height);}
        else if (y!=0)
           {startAnim(EYAxis,0);}
        if (abs(iPointerPoint1.iX-iPointerPoint2.iX)<20&&abs(iPointerPoint1.iY-iPointerPoint2.iY)<20)
        {
            QGraphicsSceneMouseEvent releaseEvent(QEvent::GraphicsSceneMouseRelease);
            releaseEvent.setScenePos(QPointF(iPointerPoint1.iX-control->Position().iX, iPointerPoint1.iY-control->Position().iY));
            releaseEvent.setButton(Qt::LeftButton);
            releaseEvent.setButtons(Qt::LeftButton);
            QApplication::sendEvent(viewer->scene(), &releaseEvent);
        }
        else
        {
            QGraphicsSceneMouseEvent moveEvent(QEvent::GraphicsSceneMouseMove);
            moveEvent.setScenePos(QPointF(iPointerPoint1.iX-control->Position().iX-10,iPointerPoint1.iY-control->Position().iY-10));
            moveEvent.setButton(Qt::LeftButton);
            moveEvent.setButtons(Qt::LeftButton);
            QApplication::sendEvent(viewer->scene(), &moveEvent);
            QGraphicsSceneMouseEvent releaseEvent(QEvent::GraphicsSceneMouseRelease);
            releaseEvent.setScenePos(QPointF(0,0));
            releaseEvent.setButton(Qt::LeftButton);
            releaseEvent.setButtons(Qt::LeftButton);
            QApplication::sendEvent(viewer->scene(), &releaseEvent);

        }
        MovingChanged(false);
        }
    CCoeControl::HandlePointerEventL(aPointerEvent);
    }

void CWindowMover::SimulatePointer(TPointerEvent aPointerEvent)
{

}

void CWindowMover::xAnimChanged(const QVariant &value)
{
    bool ok;
    int val=value.toInt(&ok);
    CCoeControl* control =(viewer->winId());
    control->SetPosition(TPoint(val,0));
    int loop=xAnim->currentLoop();
    TSize s=TSize(abs(xAnim->keyValueAt(loop).toInt()-val),control->Size().iHeight);
    control->DrawBackground(TRect(TPoint(val,0),s));
    //if (abs(val)==control->Size().iWidth&&iCallBack) iCallBack->Hide();
    //qDebug()<<"x anim"<<val;
}

void CWindowMover::yAnimChanged(const QVariant &value)
{
    bool ok;
    int val=value.toInt(&ok);
     CCoeControl* control =(viewer->winId());
     control->SetPosition(TPoint(0,val));
     int loop=yAnim->currentLoop();
     TSize s=TSize(control->Size().iWidth,abs(yAnim->keyValueAt(loop).toInt()-val));
     control->DrawBackground(TRect(TPoint(0,val),s));
     //if ((abs(val)==control->Size().iHeight)&&iCallBack) iCallBack->Hide();
     //qDebug()<<"y anim"<<val;
}

void CWindowMover::finished()
{
    qDebug()<<"finished anim";
    CCoeControl* control =(viewer->winId());
    TPoint p=control->Position();
    int val=0;
    if (p.iX==0) val=p.iY;
    else if (p.iY==0) val=p.iX;
    if ((abs(val)==control->Size().iHeight||abs(val)==control->Size().iWidth)&&iCallBack) iCallBack->Hide();
}

void CWindowMover::checkLaunchArea()
{
    CCoeControl* control =(viewer->winId());
    int y=control->Position().iY;
    int x=control->Position().iX;
    float verSense=settings->value("settings/versense",0.5).toFloat();
    int height=control->Size().iHeight;
    if (x==0&&abs(y-prevY)<40&&y>(-height*verSense)&&y<-40)
    {
        qDebug()<<"will show launch area";
        emit showLaunchArea();
        startAnim(EYAxis,0);
    }
    prevY=y;
}

void CWindowMover::show()
{
    qDebug()<<"SHOW CAPTURER WINDOW";
    MakeVisible(ETrue);
    //iWinGroup->SetOrdinalPosition(0, ECoeWinPriorityAlwaysAtFront+KAddPriority+1);
    iTimer->start();
}

void CWindowMover::toZero()
{
    CCoeControl* control =(viewer->winId());
    RDrawableWindow* rWindow=(control->DrawableWindow());
    control->SetPosition(TPoint(0,0));
    prevY=0;
}

void CWindowMover::hide()
{
    MakeVisible(EFalse);
    qDebug()<<"HIDE CAPTURER WINDOW";
    iTimer->stop();
}

void CWindowMover::changeSize(int w, int h)
{
    SetSize(TSize(w,h));
    DrawNow();
}



void CWindowMover::Draw(const TRect& /*aRect*/) const
    {
    CWindowGc& gc = SystemGc();
    TRect drawRect(Rect());
    gc.Clear(drawRect);
    }

