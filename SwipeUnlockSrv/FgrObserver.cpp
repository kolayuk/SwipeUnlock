/*
 * FgrObserver.cpp
 *
 *  Created on: 24.10.2009
 *      Author: Kolay
 */

#include "FgrObserver.h"
#include <apgtask.h>
#include <apgwgnam.h> //CApaWindowGroupName
#ifdef _DEBUG
#include <e32debug.h>
#endif

CFgrObserver* CFgrObserver::NewL(RWsSession& aWsSession,MFgrCallBack& aCallBack)
	{
	CFgrObserver* self = CFgrObserver::NewLC(aWsSession,aCallBack);
	CleanupStack::Pop(self);
	return self;
	}
 
 
CFgrObserver* CFgrObserver::NewLC(RWsSession& aWsSession,MFgrCallBack& aCallBack)
	{
	CFgrObserver* self = new (ELeave) CFgrObserver(aWsSession,aCallBack);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}
 
 
CFgrObserver::CFgrObserver(RWsSession& aWsSession,MFgrCallBack& aCallBack)
:CActive(EPriorityHigh),iCallBack(aCallBack), iWsSession(aWsSession), iWg(aWsSession)
{
}
 
CFgrObserver::~CFgrObserver()
{
	Cancel();
	iWg.Close();
}
 
void CFgrObserver::ConstructL()
{
	CActiveScheduler::Add(this);

	User::LeaveIfError(iWg.Construct((TUint32)&iWg, EFalse));
	iWg.SetOrdinalPosition(-1);
	iWg.EnableReceiptOfFocus(EFalse);
 
	CApaWindowGroupName* wn=CApaWindowGroupName::NewLC(iWsSession);
	wn->SetHidden(ETrue);
	wn->SetWindowGroupName(iWg);
	CleanupStack::PopAndDestroy();

	iWg.EnableScreenChangeEvents();
        //iWg.EnableGroupListChangeEvents();
	iWg.EnableFocusChangeEvents();
	iHandle=-1;
	Listen();
}
 
void CFgrObserver::RunL()
	{
		TWsEvent wsEvent;
		iWsSession.GetEvent(wsEvent); 
		switch (wsEvent.Type())
			{
			case EEventScreenDeviceChanged:
				{
				iCallBack.ScreenChanged();	
				break;
				}
			case EEventWindowGroupListChanged:
				{
				iCallBack.GroupListChanged();
				break;
				}
			case EEventFocusGroupChanged:
				{
				iCallBack.GroupListChanged();
				break;
				}
			case EEventKeyUp:
				{
                                //iCallBack.KeyCaptured(wsEvent);
				break;
				}
			case EEventKeyDown:
				{
                                //iCallBack.KeyCaptured(wsEvent);
				break;
				}
			default:
				//iCallBack.ForegroundEventL();
				break;
			}	 

		if (iStatus != KErrCancel) 
		{
			Listen();
		}
	}
 
void CFgrObserver::DoCancel()
{
	iWsSession.EventReadyCancel();
}
 
void CFgrObserver::Listen()
{
	iWsSession.EventReady(&iStatus);
	SetActive();
}
TInt CFgrObserver::CaptureKey(TInt aScancode)
	{
        //if (iHandle!=-1){iWg.CancelCaptureKeyUpAndDowns(iHandle);}
        return iWg.CaptureKeyUpAndDowns(aScancode,0,0);
}

void CFgrObserver::CancelCapture(TInt aHandle)
{
    if (aHandle>0){iWg.CancelCaptureKeyUpAndDowns(aHandle);}
}
