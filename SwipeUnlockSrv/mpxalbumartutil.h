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
* Description:  MPX album art utility
*
*/


#ifndef CMPXALBUMARTUTIL_H
#define CMPXALBUMARTUTIL_H

#include <gdi.h>
#include <MetaDataField.hrh>
#include <thumbnailmanager.h>
#include <thumbnailmanagerobserver.h>

class CMPXMedia;
class MMPXAlbumArtUtilObserver;
class CMPXImageUtil;
class CRepository;
/**
*  Music Player common utility class
*/
class CMPXAlbumArtUtil: public CBase, public MThumbnailManagerObserver
    {
public:
    /**
    *  Two phased contructor
    */
    IMPORT_C static CMPXAlbumArtUtil* NewL();

    /**
    *  Destuctor
    */
    IMPORT_C ~CMPXAlbumArtUtil();

    /**
    *  Extract album art data,
    *
    * @since S60 3.2.3
    * @param aProp media property. the media must contain the following
    *              attributes:
    *              TMPXAttribute( KMPXMediaIdMusic, EMPXMediaMusicAlbumArtFileName )
    *              TMPXAttribute( KMPXMediaIdGeneral, EMPXMediaGeneralUri )
    * @param aObs callback after the operation completed.
    * @param aSize The size of the required destination BMP.
    * @param aLargestFromCache ETrue, get the largest available from image cache, EFalse
    *                          get the size specified in aSize.
    * @param aDisplayMode the display mode of the destination BMP
    * @return bitmap object
    */
    IMPORT_C void ExtractAlbumArtL(const CMPXMedia& aProp,
                                   MMPXAlbumArtUtilObserver& aObs,
                                   const TSize& aSize,
                                   TBool aLargestFromCache = ETrue,
                                   TDisplayMode aDisplayMode = EColor64K);

   /**
    * Cancel outstanding asynch requests
    * @since S60 3.2.3
    */
   IMPORT_C void CancelRequest();
   
   
public: // from base class MThumbnailManagerObserver

    /**
     * From MThumbnailManagerObserver
     * Preview thumbnail generation or loading is complete.
     *
     * @param aThumbnail     An object representing the resulting thumbnail.
     * @param aId            Request ID for the operation
     */
    void ThumbnailPreviewReady( MThumbnailData& aThumbnail, TThumbnailRequestId aId );

    /**
     * From MThumbnailManagerObserver
     * Final thumbnail bitmap generation or loading is complete.
     *
     * @param aError         Error code.
     * @param aThumbnail     An object representing the resulting thumbnail.
     * @param aId            Request ID for the operation.
     */
    void ThumbnailReady( TInt aError, MThumbnailData& aThumbnail, TThumbnailRequestId aId );

private:
    /**
    * C++ constructor
    */
    CMPXAlbumArtUtil();

    /**
    * Second phase constructor
    *
    */
    void ConstructL();

    /**
    * Extract binary meta data from file
    *
    * @since S60 3.2.3
    * @param aFileName file name
    * @param aFieldId metadata field id
    *
    */
    HBufC8* ExtractBinaryMetaDataLC(const TDesC& aFilename,
                                    TMetaDataFieldId aFieldId);
									
	/** -----------------------------------------------------------------------------
    * Extract Thumbnail for the current song
    * -----------------------------------------------------------------------------
    */								
   void ExtractThumbnailL( const CMPXMedia* aMedia);

private:
    CMPXImageUtil* iArtUtil;
    CThumbnailManager*          iThumbnailManager;      // Owned
    TDisplayMode            iDisplayMode ; //Owned
    TSize                       iImageSize;
    TInt iReqId;
    HBufC* iFilename;
    MMPXAlbumArtUtilObserver* iObserver;
    };

#endif      // CMPXALBUMARTUTIL_H

// End of File
