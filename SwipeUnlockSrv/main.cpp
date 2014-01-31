#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"
#include "Application.h"
#include <QDeclarativeContext>

#include <QtDebug>
#include <QFile>
#include <QTextStream>
#ifdef Q_OS_SYMBIAN
#include <e32debug.h>
#endif
#include <suspender.h>
#include <proxy.h>
#include <aknappui.h>
#include <eikenv.h>
#include <QTime>
#include <iconprovider.h>
#include <QDeclarativeEngine>
#include <skinbgprovider.h>

void myMessageHandler(QtMsgType type, const char *msg)
{
        QString txt;
        QTime t=QTime::currentTime();
        QString st=t.toString("hh:mm:ss");
        switch (type) {
        case QtDebugMsg:
                txt = QString(" %1").arg(msg);
                break;
        case QtWarningMsg:
                txt = QString(" Warning: %1").arg(msg);
        break;
        case QtCriticalMsg:
                txt = QString(" Critical: %1").arg(msg);
        break;
        case QtFatalMsg:
                txt = QString(" Fatal: %1").arg(msg);
                abort();
        }
        txt=st+txt;
        QFile outFile("C:\\System\\Apps\\SwypeUnlock\\swypeunlocksrv.txt");
        outFile.open(QIODevice::WriteOnly | QIODevice::Append);
        QTextStream ts(&outFile);
        ts << txt << endl;
#ifdef Q_OS_SYMBIAN
        TPtrC des (reinterpret_cast<const TText*>(txt.constData()),txt.length());
        RDebug::Print(des);
#endif
}

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));
    QScopedPointer<QmlApplicationViewer> viewer(QmlApplicationViewer::create());
    QFile file("C:\\System\\Apps\\SwypeUnlock\\swypeunlocksrv.txt");
    if (file.exists()){file.remove();}
    qInstallMsgHandler(myMessageHandler);

    Application* myapp=new Application(*viewer.data());
    qDebug()<<"app obj created";
    Proxy* proxy=new Proxy(myapp);
    proxy->moveToThread(myapp);

    Suspender* susp=new Suspender(proxy);
    qDebug()<<"Main thread:"<<RThread().Id().Id();
    QObject::connect(myapp,SIGNAL(setQMLFile(Application*)),susp,SLOT(setupQML(Application*)));
    QObject::connect(myapp,SIGNAL(Suspend(int)),susp,SLOT(Suspend(int)));
    QObject::connect(myapp,SIGNAL(unSuspend()),susp,SLOT(unSuspend()));
    QObject::connect(myapp,SIGNAL(setNotSleep()),susp,SLOT(setNotSleep()));
    QObject::connect(susp,SIGNAL(sendId(int)),myapp,SLOT(setThrID(int)));
    QObject::connect(app.data(),SIGNAL(aboutToQuit()),myapp,SLOT(deleteLater()));


    QObject::connect(proxy,SIGNAL(sigHide()),myapp,SLOT(Unlock()),Qt::QueuedConnection);
    QObject::connect(proxy,SIGNAL(sigRestartTimer()),myapp,SLOT(restartTimer()),Qt::QueuedConnection);
    QObject::connect(proxy,SIGNAL(sigMovingChanged(bool)),myapp,SLOT(MovingChanged(bool)),Qt::QueuedConnection);
    QObject::connect(myapp,SIGNAL(changeSize()),proxy,SLOT(screenChanged()),Qt::QueuedConnection);
    viewer->rootContext()->setContextProperty("proxy",proxy);

    //viewer->setAttribute(Qt::WA_PaintOnScreen);
    viewer->setAttribute(Qt::WA_TranslucentBackground);
    viewer->viewport()->setAutoFillBackground(false);
    viewer->setStyleSheet("background:transparent;");
    viewer->setWindowFlags(Qt::FramelessWindowHint);
    viewer->rootContext()->setContextProperty("lang",User::Language());
    viewer->engine()->addImageProvider(QLatin1String("icons"), new IconProvider);
    viewer->engine()->addImageProvider(QLatin1String("skin"), new SkinBgProvider);
/*
    CCoeControl *control =(viewer->winId());
    qDebug()<<" native control is "<<control;
    RDrawableWindow* rWindow= control->DrawableWindow();
    qDebug()<<" native window is "<<rWindow;
    qDebug()<<rWindow->Position().iX<<rWindow->Position().iY<<rWindow->Size().iWidth<<rWindow->Size().iHeight;
    qDebug()<<rWindow->SetSizeErr(TSize(100,100));
    qDebug()<<rWindow->Position().iX<<rWindow->Position().iY<<rWindow->Size().iWidth<<rWindow->Size().iHeight;
    TInt alpha;
    alpha=0;
    TRgb backgroundColour = KRgbWhite; // for example
    if(KErrNone == rWindow->SetTransparencyAlphaChannel()){backgroundColour.SetAlpha(alpha);qDebug()<<"transp supported";}
    else {qDebug()<<"transp not supported";}
   rWindow->SetBackgroundColor(backgroundColour);
    rWindow->SetPosition(TPoint(100,0));
*/
    qDebug()<<"int main end";
    return app->exec();
}
