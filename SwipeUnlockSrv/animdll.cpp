#include "animdll.h"
#include <propertyobserver.h>
#include <qdebug.h>
#include <apgwgnam.h>
#include <coedef.h>


AnimDll::AnimDll(RWsSession* aWs, QString aName,QObject *parent) :
    QObject(parent), iClientDll(*aWs), iClientCommander(iClientDll),MPropertyCallBack()
{
    qDebug()<<"connecting dll";
    TPtrC name (static_cast<const TUint16*>(aName.utf16()),aName.length());
    iClientDll.Load(name);
    qDebug()<<RProperty::Define(TUid::Uid(0x2004423C),0x100,RProperty::EInt);
    qDebug()<<RProperty::Set(TUid::Uid(0x2004423C),0x100,0);
    qDebug()<<RProperty::Define(TUid::Uid(0x2004423C),0x101,RProperty::EInt);
    qDebug()<<RProperty::Set(TUid::Uid(0x2004423C),0x101,0);
    qDebug()<<RProperty::Define(TUid::Uid(0x2004423C),0x102,RProperty::EInt);
    qDebug()<<RProperty::Set(TUid::Uid(0x2004423C),0x102,50000);
    qDebug()<<RProperty::Define(TUid::Uid(0x2004423C),0x200,RProperty::EInt);
    qDebug()<<RProperty::Set(TUid::Uid(0x2004423C),0x200,0);

    iObserver=CPropertyObserver::NewL(TUid::Uid(0x2004423C),0x100,this);

    iWinGroup=new (ELeave) RWindowGroup(*aWs);
    iWinGroup->Construct((TUint32)&iWinGroup, EFalse);
    iWinGroup->SetOrdinalPosition(-1);
    iWinGroup->EnableReceiptOfFocus(ETrue);
    CApaWindowGroupName* wn=CApaWindowGroupName::NewL(*aWs);
    wn->SetHidden(ETrue);
    wn->SetWindowGroupName(*iWinGroup);
    delete wn;

    TBuf8<1> params( TInt8( 0 ) );
    RWindow wnd(*aWs);
    User::LeaveIfError(wnd.Construct(*iWinGroup,TUint32(&wnd)));
    wnd.SetOrdinalPosition(0,1000000);
    iClientCommander.ImageConstruct(wnd,1,params );
    qDebug()<<"dll connected";
    qDebug()<<"animdll thread"<<RThread().Id().Id();
}

void AnimDll::ValChanged(TUid aUid,TUint32 aKey,TInt val)
{
    RProperty::Set(aUid,aKey,0);
    int key=0,duration=50000;
    RProperty::Get(TUid::Uid(0x2004423C),0x101,key);
    RProperty::Get(TUid::Uid(0x2004423C),0x102,duration);
    qDebug()<<"key captured"<<key;
    emit KeyCaptured(key,duration);
}

void AnimDll::ValTxtChanged(TUid aUid, TUint32 aKey,TDesC val)
{
}
