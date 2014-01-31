/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies). 
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
* Description:  Thumbnail Manager observer.
 *
*/


#ifndef THUMBNAILMANAGEROBSERVER_H
#define THUMBNAILMANAGEROBSERVER_H

#include "thumbnailobjectsource.h"

class MThumbnailData;

/**
 *  Thumbnail observer.
 *
 *  Callback interface for getting information about completed thumbnail
 *  operations. This should be implemented by the client using the API.
 *
 *  Example of how the client may implement the ThumbnailReady()
 *  method:
 *  @code
 *  void CMyThumbnailControl::ThumbnailReady(
 *      TInt aError,
 *      MThumbnailData& aThumbnail,
 *      TThumbnailRequestId aId )
 *      {
 *      // This function must not leave.
 *      delete iBitmap;
 *      iBitmap = NULL;
 *
 *      if ( !aError )
 *          {
 *          // Claim ownership of the bitmap instance for later use
 *          iBitmap = aThumbnail.DetachBitmap();
 *          // We can now use iBitmap in our Draw() method
 *          DrawDeferred();
 *          }
 *      else
 *          {
 *          // An error occurred while getting the thumbnail.
 *          // Perhaps we should show a broken image icon to the user.
 *          }
 *      }
 *  @endcode
 *  @since S60 v5.0
 */
class MThumbnailManagerObserver
    {
public:

    /**
     * Preview thumbnail generation or loading is complete.
     *
     * This callback is not called unless EOptimizeForQualityWithPreview flag
     * was specified.
     *
     * This callback is not called if any of the following is true:
     * - an error occurred while processing the preview thumbnail
     * - a suitable existing thumbnail was not found
     * - a high quality thumbnail is already available
     *
     * The MThumbnailData instance is only valid for the duration of
     * this call. It may not be stored for later use. If the client should
     * want to use the bitmap data later, it can claim ownership of the
     * CFbsBitmap object by calling DetachBitmap().
     *
     * @since S60 v5.0
     * @param aThumbnail     An object representing the resulting thumbnail.
     * @param aId            Request ID for the operation
     */
    virtual void ThumbnailPreviewReady( MThumbnailData& aThumbnail,
        TThumbnailRequestId aId ) = 0;

    /**
     * Final thumbnail bitmap generation or loading is complete.
     *
     * The MThumbnailData instance is only valid for the duration of
     * this call. It may not be stored for later use. If the client should
     * want to use the bitmap data later, it can claim ownership of the
     * CFbsBitmap object by calling DetachBitmap().
     *
     * @since S60 v5.0
     * @param aError         Error code.
     * @param aThumbnail     An object representing the resulting thumbnail.
     * @param aId            Request ID for the operation.
     */
    virtual void ThumbnailReady( TInt aError, MThumbnailData& aThumbnail,
        TThumbnailRequestId aId ) = 0;
};

/**  Thumbnail request types */
enum TThumbnailRequestType
    {
    ERequestDeleteThumbnails = 0
    };

/**
 *  Optional callback interface for getting information about other completed 
 *  requests that don't include a thumbnail. 
 *  
 *  Request types:
 *  - ERequestDeleteThumbnails
 *  
 *  Can be added using SetRequestObserver(MThumbnailManagerRequestObserver& aObserver)
 *  and removed using RemoveRequestObserver().
 *
 *  @since Symbian^3
 */
class MThumbnailManagerRequestObserver
    {
public:
    /**
     * A request is complete.
     *
     * @since Symbian^3
     * @param aError         Error code.
     * @param aRequestType   Type of the completed request.
     * @param aId            Request ID for the operation.
     */
    virtual void ThumbnailRequestReady( TInt aError, TThumbnailRequestType aRequestType,
        TThumbnailRequestId aId ) = 0;
};

#endif // THUMBNAILMANAGEROBSERVER_H
