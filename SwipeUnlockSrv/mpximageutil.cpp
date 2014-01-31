/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description:  Implementation of CMPXImageUtil.
*
*/

// INCLUDE FILES
#include <e32std.h>
#include <e32base.h>
#include <bitmaptransforms.h>
#include <mda/common/video.h>
#include <eikenv.h>
#include <icl/imagedata.h>
#include <imageconversion.h>
#include <IclExtJpegApi.h>

#include "mpximageutil.h"

//This value is used to stretch so the image fills the container.
const TReal MaxStretchRatio = 1.1f;

LOCAL_C TInt Stretch (TInt aValue, TInt aLimit)
    {
    TInt ret( aValue * MaxStretchRatio );
    ret = (ret>aLimit) ? aLimit : ret;
    return ret;
    }

// ============================ MEMBER FUNCTIONS ===============================


// -----------------------------------------------------------------------------
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CMPXImageUtil* CMPXImageUtil::NewL(
                                    MMPXAlbumArtUtilObserver& aObserver)
    {
    CMPXImageUtil* self = new ( ELeave ) CMPXImageUtil(aObserver);
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop(); // self
    return self; 
    }

// -----------------------------------------------------------------------------
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CMPXImageUtil::CMPXImageUtil(MMPXAlbumArtUtilObserver& aObserver) 
:   CActive(EPriorityStandard), iObserver(aObserver) 
    {
    iBitmap = NULL;
    iState = EIdle;
    }

// -----------------------------------------------------------------------------
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CMPXImageUtil::ConstructL()
    {
    iScaler = CBitmapScaler::NewL();
    User::LeaveIfError(iFs.Connect());
    CActiveScheduler::Add( this );
    }

// -----------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------
//
CMPXImageUtil::~CMPXImageUtil()
    {
    Cancel();
    delete iImageDecoder; // CImageDecoder must be deleted before the 
    delete iScaler;
    iFs.Close();
    delete iImageData;
    }

// -----------------------------------------------------------------------------
// Starts to decode an image from a file. 
// -----------------------------------------------------------------------------
//
void CMPXImageUtil::StartToDecodeL(const TDesC& aFileName, 
                                      const TSize& aSize, 
                                      TDisplayMode aDisplayMode /*=EColor64K*/)
    {
    if(iState)
        {
        User::Leave(KErrNotReady);
        }

    delete iImageDecoder; 
    iImageDecoder = NULL;
    delete iBitmap; 
    iBitmap = NULL;
    delete iImageData;
    iImageData = NULL;
    
    // create the decoder

    TRAPD( err, iImageDecoder = CExtJpegDecoder::FileNewL( 
            CExtJpegDecoder::EHwImplementation, 
            iFs, 
            aFileName, 
            CImageDecoder::EOptionNone ) );
    if (KErrNone != err)
        {
            TRAP(err,iImageDecoder = CExtJpegDecoder::FileNewL( 
                    CExtJpegDecoder::ESwImplementation, 
                    iFs, 
                    aFileName, 
                    CImageDecoder::EOptionNone ) );
        if (KErrNone != err)
            {
            iImageDecoder = CImageDecoder::FileNewL(
                    iFs, 
                    aFileName,
                    CImageDecoder::EOptionNone);
            }
        }

    // Get image size
    TSize bitmapSize = CalculateDecodeSize(aSize);
    // create the destination bitmap
    iBitmap = new (ELeave) CFbsBitmap();
    User::LeaveIfError(iBitmap->Create(bitmapSize, aDisplayMode)); 

    // start conversion to bitmap
    iState = EDecoding;
    iImageDecoder->Convert(&iStatus, *iBitmap);
    
    iObserver.ExtractAlbumArtStarted();
    SetActive();
    }

// -----------------------------------------------------------------------------
// CMPXImageUtil::DoCancel
// Implementation of CActive
// -----------------------------------------------------------------------------
//
void CMPXImageUtil::DoCancel()
    {
    switch ( iState )
        {
        case EDecoding:
            {
            iImageDecoder->Cancel();
            // need to delete bitmap as we have are still the owner until the 
            // operation completes
            if ( iBitmap )
                {
                delete iBitmap;
                iBitmap = NULL;
                }
            break;
            }
        case EScaling:
            {
            iScaler->Cancel();
            if ( iBitmap )
                {
                delete iBitmap;
                iBitmap = NULL;
                }
            break;
            }
        default: // No Asynchronous events are taking place, do nothing.
            {
            break;
            }
        }

    delete iImageData;
    iImageData = NULL;
    delete iImageDecoder;
    iImageDecoder = NULL;
    }

// -----------------------------------------------------------------------------
// Implementation of CActive
// -----------------------------------------------------------------------------
//
void CMPXImageUtil::RunL()
    {
    TInt deleteDecoder( ETrue );
    switch( iState ) 
        {
        case EDecoding:
            {
            if( iStatus == KErrNone ) 
                {
                if ( !iScaleRquired )
                    {   
                    iState = EIdle;
                    iObserver.ExtractAlbumArtCompleted(iBitmap,KErrNone);
                    iBitmap = NULL;
                    }
                else 
                    {
                    deleteDecoder = EFalse;
                    ScaleL();
                    }
                break;
                }
            else
                {
                // some error
                if ( iBitmap )
                    {
                    delete iBitmap;
                    iBitmap = NULL;                        
                    }
                iState = EIdle;
                iObserver.ExtractAlbumArtCompleted(iBitmap, iStatus.Int());
                break;   
                }
            }
        case EScaling:
            {
            iState = EIdle;
            iObserver.ExtractAlbumArtCompleted(iBitmap,iStatus.Int());
            iBitmap = NULL; 
            }
            break;

        default: // some error
            {
            iState = EIdle;
            if ( iBitmap )
                {
                delete iBitmap;
                iBitmap = NULL;                        
                }
            iObserver.ExtractAlbumArtCompleted(iBitmap,iStatus.Int());
            break;
            }
        }

    // It's safe to destroy iImageData here
    delete iImageData;
    iImageData = NULL;
    
    if ( deleteDecoder )
        {
        delete iImageDecoder;
        iImageDecoder = NULL;
        }
    }

// -----------------------------------------------------------------------------
// Scales iBitmap by iSize
// -----------------------------------------------------------------------------
//
void CMPXImageUtil::ScaleL()
    {
    iScaler->Scale(&iStatus, *iBitmap, iSize, EFalse);
    iState = EScaling;
    SetActive();
    }

// -----------------------------------------------------------------------------
// Starts to decode an image from a buffer. 
// -----------------------------------------------------------------------------
//
void CMPXImageUtil::StartToDecodeL( const TSize& aSize,
        HBufC8* aAlbumArt, TDisplayMode aDisplayMode/*=EColor64K*/ )
    {
    if(iState)
        {
        User::Leave( KErrNotReady );
        }
                               
    delete iImageDecoder; 
    iImageDecoder = NULL;
    delete iBitmap; 
    iBitmap = NULL;
    delete iImageData;
    iImageData = NULL;
    // storing the pointer to aAlbumArt, ownership was transferred to us.
    iImageData = aAlbumArt;
    // create the decoder
    
    
    TRAPD( err, iImageDecoder = CExtJpegDecoder::DataNewL( 
            CExtJpegDecoder::EHwImplementation, 
            iFs, 
            *iImageData, 
            CImageDecoder::EOptionNone ) );
    if ( KErrNone != err )
        {
        TRAP(err,iImageDecoder = CExtJpegDecoder::DataNewL( 
                CExtJpegDecoder::ESwImplementation, 
                iFs, 
                *iImageData, 
                CImageDecoder::EOptionNone ) );
        if ( KErrNone != err )
            {
            iImageDecoder = CImageDecoder::DataNewL( 
                    iFs, 
                    *iImageData, 
                    CImageDecoder::EOptionNone );
            }
        }
    
    

    
    TSize bitmapSize = CalculateDecodeSize( aSize );

    // create the destination bitmap
    iBitmap = new ( ELeave ) CFbsBitmap();
    User::LeaveIfError( iBitmap->Create( bitmapSize, aDisplayMode ) );
    // start conversion to bitmap
    iState = EDecoding;
    iImageDecoder->Convert( &iStatus, *iBitmap );
    
    iObserver.ExtractAlbumArtStarted();
    SetActive();
    }
// -----------------------------------------------------------------------------
// Calculates the decode size and prepares members for scaling. 
// -----------------------------------------------------------------------------
//
TSize CMPXImageUtil::CalculateDecodeSize(const TSize& aSize)
    {
    const TFrameInfo& frameInfo = iImageDecoder->FrameInfo();
    TSize bitmapSize = frameInfo.iOverallSizeInPixels;
    TReal sourceAspectRatio( TReal( bitmapSize.iWidth) / bitmapSize.iHeight );
    TReal destinationAspectRatio( TReal( aSize.iWidth ) / aSize.iHeight );
    TReal xScale = TReal( bitmapSize.iWidth ) / aSize.iWidth;
    TReal yScale = TReal( bitmapSize.iHeight ) / aSize.iHeight;
    TReal scale(0.0f);
    
    if ( sourceAspectRatio > destinationAspectRatio )
        {
        scale = xScale;
        iSize.iWidth = aSize.iWidth;
        iSize.iHeight = Stretch( TReal( bitmapSize.iHeight ) / scale , 
                                 aSize.iHeight );
        }
    else
        {
        scale = yScale;
        iSize.iWidth = Stretch( TReal( bitmapSize.iWidth ) / scale ,
                                aSize.iWidth);
        iSize.iHeight = aSize.iHeight;
        }
     
    if ((frameInfo.iFlags & TFrameInfo::EFullyScaleable))
        {
        iScaleRquired = EFalse;
        bitmapSize = iSize;
        }
    else
        //Decoder only supports 2, 4 and 8 scallyng, the image will need 
        //to be reescaled after decoding.
        //Decoding to a scale that is just a bit bigger thant the target,
        //this will save memory and resources and we will get a sharp image 
        //after scaling.
        {
        TInt intscale = ( scale >= 8 ) ? 8 : 
                ( scale >= 4 ) ? 4 :
                ( scale >= 2 ) ? 2 : 1;
        TUint xCorrection = ( bitmapSize.iWidth % intscale ) ? 1 : 0;
        TUint yCorrection = ( bitmapSize.iHeight % intscale ) ? 1 : 0;
        bitmapSize.iWidth /= intscale;
        bitmapSize.iHeight /= intscale;
        bitmapSize += TSize( xCorrection, yCorrection );
        iScaleRquired = ETrue;
        }
    return bitmapSize;
    }

// -----------------------------------------------------------------------------
// CMPXImageUtil::CancelRequest
// Cancel Asynch requests
// -----------------------------------------------------------------------------
//
void CMPXImageUtil::CancelRequest()
    {
    Cancel();
    }

//  End of File  
