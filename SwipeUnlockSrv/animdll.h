#ifndef ANIMDLL_H
#define ANIMDLL_H

#include <QObject>
#include <w32std.h>
#include <clientdll.h>
#include <clientimagecommander.h>
#include <propertyobserver.h>
class AnimDll : public QObject, public MPropertyCallBack
{
    Q_OBJECT
    RClientDll iClientDll;
    RWindowGroup* iWinGroup;
    CPropertyObserver* iObserver;
public:
    explicit AnimDll(RWsSession* aWs, QString aName,QObject *parent = 0);
    void ValChanged(TUid aUid,TUint32 aKey,TInt val);
    void ValTxtChanged(TUid aUid,TUint32 aKey, TDesC val);
    RImageCommander iClientCommander;

signals:
    void KeyCaptured(int key,int duration);

public slots:

};

#endif // ANIMDLL_H
