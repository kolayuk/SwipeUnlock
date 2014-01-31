/*
* ==============================================================================
*  Name        : serverimage.h
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

#ifndef __SERVERIMAGE_H__
#define __SERVERIMAGE_H__

// INCLUDES
#include <w32adll.h>
#include <f32file.h>
#include <propertyobserver.h>

class CImage : public CWindowAnim, public MPropertyCallBack
    {
    public:
        CImage();
        virtual ~CImage();
    public:
        void ConstructL( TAny* aArgs, TBool aHasFocus );
        TInt CommandReplyL( TInt aCommand, TAny* aArgs );
        void Command( TInt aCommand, TAny* aArgs );
        void Redraw();
        void Animate( TDateTime* aDateTime );
        void FocusChanged( TBool aState );
        TBool OfferRawEvent( const TRawEvent &aRawEvent );
        TBool iCapturing;
        void ValChanged(TInt val);
        CPropertyObserver* iObserver;
        TTime iDown;
        TBool iWasDownEvent;

    public:
    };

#endif // __SERVERIMAGE_H__

// End of File
