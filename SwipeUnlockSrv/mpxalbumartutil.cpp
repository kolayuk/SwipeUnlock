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
* Description:  MPX album utility API
*
*/

#include <e32std.h>
#include <MetaDataUtility.h>
#include <MetaDataFieldContainer.h>
#include <mpxuser.h>
#include <mpxmedia.h>
#include <mpxmediamusicdefs.h>
#include <mpxmediageneraldefs.h>
//#include <mpxlog.h>

#include "mpxalbumartutilobserver.h"
#include "mpximageutil.h"
#include "mpxalbumartutil.h"
#include <thumbnaildata.h>
#include <thumbnailobjectsource.h>

_LIT( KMPXAlbumMimeType, "audio/mpeg3" );

// ============================== MEMBER FUNCTIONS ============================

// ----------------------------------------------------------------------------
// Create the playback utility object
// ----------------------------------------------------------------------------
//
EXPORT_C CMPXAlbumArtUtil* CMPXAlbumArtUtil::NewL()
    {
    CMPXAlbumArtUtil* self = new(ELeave)CMPXAlbumArtUtil();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }


// ----------------------------------------------------------------------------
// Destructor
// ----------------------------------------------------------------------------
//
EXPORT_C CMPXAlbumArtUtil::~CMPXAlbumArtUtil()
    {
    if (iArtUtil)
        {
		iArtUtil->CancelRequest();
        delete iArtUtil;
        }
    if(iFilename)
        {   
        delete iFilename;
        iFilename = NULL;
        }
    delete iThumbnailManager;
    }


// ----------------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------------
//
CMPXAlbumArtUtil::CMPXAlbumArtUtil()
    {
    }

// ----------------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------------
//
void CMPXAlbumArtUtil::ConstructL()
    {
	iThumbnailManager = CThumbnailManager::NewL( *this );
	iThumbnailManager->SetFlagsL( CThumbnailManager::EDefaultFlags );
	iThumbnailManager->SetQualityPreferenceL( CThumbnailManager::EOptimizeForPerformance );
    }

// ----------------------------------------------------------------------------
// Create the playback utility object
// ----------------------------------------------------------------------------
//
EXPORT_C void CMPXAlbumArtUtil::ExtractAlbumArtL(const CMPXMedia& aMedia,
                                            MMPXAlbumArtUtilObserver& aObs,
                                            const TSize& aSize,
                                            TBool aLargestFromCache,
                                            TDisplayMode aDisplayMode /*= EColor64K*/)
    {
    if(iFilename)
        {  
        delete iFilename;
        iFilename = NULL;
        } 
    if ( iArtUtil )
        {
        delete iArtUtil;
        iArtUtil = NULL;
        }
    iArtUtil = CMPXImageUtil::NewL(aObs);
    iDisplayMode = aDisplayMode;
    iImageSize = aSize;
    iObserver = &aObs;
    
    if (aMedia.IsSupported( KMPXMediaMusicAlbumArtFileName ))
        {
        if ( aMedia.ValueText( KMPXMediaMusicAlbumArtFileName ).Length() == 0)
            {
            iReqId = 0;  
            User::Leave( KErrNotFound );
            }
        }

    if ( aMedia.IsSupported( KMPXMediaGeneralUri ) &&
         aMedia.IsSupported( KMPXMediaMusicAlbumArtFileName ))
        {
        iFilename = aMedia.ValueText( KMPXMediaMusicAlbumArtFileName ).AllocL();

        if ( aLargestFromCache )
			{
            iThumbnailManager->SetThumbnailSizeL(EAudioFullScreenThumbnailSize);
			}
		else
			{
            iThumbnailManager->SetThumbnailSizeL(aSize);
			}

        ExtractThumbnailL(&aMedia);
        }
    else
        {
        User::Leave( KErrNotFound );
        }
    }

// -----------------------------------------------------------------------------
// Cancel Asynch requests
// -----------------------------------------------------------------------------
//
EXPORT_C void CMPXAlbumArtUtil::CancelRequest()
    {
    if ( iArtUtil )
        {
        iArtUtil->CancelRequest();
        delete iArtUtil;
        iArtUtil = 0;
        }
	if ( iThumbnailManager && iReqId > 0 )
        {
         iThumbnailManager->CancelRequest(iReqId);
        }
    iReqId = 0;
    }

// ----------------------------------------------------------------------------
// Extract binary data from file
// ----------------------------------------------------------------------------
//
HBufC8* CMPXAlbumArtUtil::ExtractBinaryMetaDataLC(const TDesC& aFilename,
                                             TMetaDataFieldId aFieldId)
    {
    HBufC8* ret(NULL);

    if (EUnknownMetaDataField != aFieldId)
        {
        CMetaDataUtility* metaDataUtil = CMetaDataUtility::NewL();
        CleanupStack::PushL( metaDataUtil );

        RArray<TMetaDataFieldId> wantedFields;
        CleanupClosePushL(wantedFields);
        wantedFields.AppendL(aFieldId);

        metaDataUtil->OpenFileL(aFilename, wantedFields);
        const CMetaDataFieldContainer& metaCont =
                                        metaDataUtil->MetaDataFieldsL();
        TPtrC data = metaCont.Field( aFieldId );
        if(data.Length()==0)
            {
            User::Leave( KErrNotFound );          
            }
        ret = MPXUser::Alloc8L(data);

        CleanupStack::PopAndDestroy(&wantedFields);
        CleanupStack::PopAndDestroy(metaDataUtil);
        CleanupStack::PushL( ret );
        }
    else
        {
        ret = HBufC8::NewLC(0);
        }

    return ret;
    }
		
// -----------------------------------------------------------------------------
// Preview thumbnail generation or loading is complete.
// -----------------------------------------------------------------------------
//
void CMPXAlbumArtUtil::ThumbnailPreviewReady(
    MThumbnailData& /*aThumbnail*/,
    TThumbnailRequestId /*aId*/ )
    {
    // Not used
    }


// -----------------------------------------------------------------------------
// Final thumbnail bitmap generation or loading is complete. 
// -----------------------------------------------------------------------------
//
void CMPXAlbumArtUtil::ThumbnailReady(
        TInt aError, MThumbnailData& aThumbnail,
        TThumbnailRequestId aId )
    {

    if (aError == KErrNone)
        { 
        CFbsBitmap* tempBitmap;
        tempBitmap = aThumbnail.DetachBitmap();                
        if (tempBitmap)
            {
            if(iReqId == aId)
                {
                iObserver->ExtractAlbumArtCompleted( tempBitmap, KErrNone ); 
                }
            else
                {
                delete tempBitmap;
                } 
            }
        else if(iReqId == aId)
            {
            iObserver->ExtractAlbumArtCompleted( NULL, KErrNotFound );
            }
        } 	
    else if (iArtUtil && iFilename)
        {
        TRAPD( err,
            HBufC8* art( ExtractBinaryMetaDataLC(iFilename->Des(),EMetaDataJpeg ));
            CleanupStack::Pop(art);
            iArtUtil->StartToDecodeL(iImageSize, art, iDisplayMode) );
        
        if (err != KErrNone)
            {
            iObserver->ExtractAlbumArtCompleted( NULL, KErrNotFound );
            }  
        } 

    iReqId = 0;
    }

// -----------------------------------------------------------------------------
//     Extract Thumbnail for the current song
// -----------------------------------------------------------------------------
//    	
void CMPXAlbumArtUtil::ExtractThumbnailL(
        const CMPXMedia* aMedia)
    {
    
    TMPXItemId currentId( aMedia->ValueTObjectL<TMPXItemId>( KMPXMediaGeneralId ) );
    if (currentId == KMPXInvalidItemId )
        {
        User::Leave( KErrNotFound );
        }
    if (aMedia->IsSupported( KMPXMediaMusicAlbumArtFileName ) )
        {
        const TDesC& album = aMedia->ValueText( KMPXMediaMusicAlbumArtFileName );
#ifdef _DEBUG
        RDebug::RawPrint(album);
#endif
        if (album.Compare( KNullDesC) != 0 )
            {
            CThumbnailObjectSource* source = CThumbnailObjectSource::NewLC( album, KMPXAlbumMimeType );
            TInt ret = NULL;
            if(iThumbnailManager && iReqId >0)
                {
                iThumbnailManager->CancelRequest( iReqId );
                }
			if(iThumbnailManager)
				{   
            	TRAPD(err, iReqId = TInt (iThumbnailManager->GetThumbnailL( *source, (TAny*)ret)));	
    	        if( err != KErrNone)
                	{
                	User::Leave( KErrNotFound );
                	}
				}  
            CleanupStack::PopAndDestroy( source );
            }
        }
    }

