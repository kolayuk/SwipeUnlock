/*
* ==============================================================================
*  Name        : serverimage.cpp
*  Part of     : Animation example
*  Interface   :
*  Description :
*  Version     :
*
*  Copyright (c) 2004 - 2006 Nokia Corporation.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia Corporation.
* ==============================================================================
*/

// INCLUDE FILES
#include <e32std.h>
#include <e32base.h>
#include <e32property.h>

#include "serverimage.h"
#include <const.h>
#include <logger.h>
#include <aknkeylock.h>


// 0x2004423C - swipeunlock
// 0x20067b13 - jellyunlock
#define KPropertyUid 0x2004423C

CImage::CImage(): MPropertyCallBack()
    {
    }
void CImage::ConstructL( TAny* /* aArgs */, TBool /* aHasFocus */ )
    {
	iFunctions->GetRawEvents(ETrue);
	iCapturing=EFalse;
	_LOG(_L("Init dll"));
	iObserver=CPropertyObserver::NewL(TUid::Uid(KPropertyUid),0x200,this);
	iWasDownEvent=EFalse;
    }

CImage::~CImage()
    {
	iObserver->Cancel();
	delete iObserver;
    }

void CImage::Redraw(){}
void CImage::FocusChanged( TBool /* aState */ ){}
void CImage::Animate( TDateTime* /* aDateTime */ ){}
TInt CImage::CommandReplyL( TInt aOpcode, TAny* /* aArgs */ ){return aOpcode;}

void CImage::Command( TInt aOpcode, TAny* aArgs )
	{
	_LOGDATA(_L("command %d"),aOpcode);
	if (aOpcode==EStartCapture) {iCapturing=ETrue;}	
	else if (aOpcode==EStopCapture) {iCapturing=EFalse;}
	                
	}
TBool CImage::OfferRawEvent( const TRawEvent& aEvent )
    {
	if (!iCapturing){return EFalse;}
	if ((aEvent.ScanCode()>='0'&&aEvent.ScanCode()<='9')||aEvent.ScanCode()=='#') return EFalse;
	if (aEvent.Type()==TRawEvent::EKeyDown)
		{
		//if (aEvent.ScanCode()==226||aEvent.ScanCode()==227||aEvent.ScanCode()==171){return EFalse;}
		_LOGDATA(_L("Key down %d"),aEvent.ScanCode());
		iDown.HomeTime();
		iWasDownEvent=ETrue;
		return ETrue;
		}
	if (aEvent.Type()==TRawEvent::EKeyUp) 
		{
		//if (aEvent.ScanCode()==226||aEvent.ScanCode()==227||aEvent.ScanCode()==171){return EFalse;}
		_LOGDATA(_L("Key up %d"),aEvent.ScanCode());
		if (iWasDownEvent)
			{
			TTime up;
			up.HomeTime();
			_LOGDATA(_L("Key in dll: %d"),aEvent.ScanCode());
			TInt ms=(TInt)up.MicroSecondsFrom(iDown).Int64();
			_LOGDATA(_L("delay: %d"),ms);
			RProperty::Set(TUid::Uid(KPropertyUid),0x102,ms);
			RProperty::Set(TUid::Uid(KPropertyUid),0x101,aEvent.ScanCode());
			RProperty::Set(TUid::Uid(KPropertyUid),0x100,1);
			}
		iWasDownEvent=EFalse;
		return ETrue;
		}
	return EFalse;
    }
void CImage::ValChanged(TInt val)
	{
	_LOGDATA(_L("property command %d"),val);
	if (val==EStartCapture){iCapturing=ETrue;}
	else if (val==EStopCapture){iCapturing=EFalse;}
	}

// End of File
