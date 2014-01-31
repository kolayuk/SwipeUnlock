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
* Description:  Main interface class to Thumbnail Manager
 *
*/


#ifndef THUMBNAILMANAGER_H
#define THUMBNAILMANAGER_H

#include <e32base.h>
#include <gdi.h>
#include <badesca.h>

#include <thumbnailobjectsource.h>

class MThumbnailManagerObserver;
class MThumbnailManagerRequestObserver;

typedef TInt TThumbnailRequestId;

typedef TUint32 TThumbnailId;
typedef enum 
{
EUnknownThumbnailSize,
ECustomThumbnailSize,
EImageGridThumbnailSize,
EImageListThumbnailSize,
EImageFullScreenThumbnailSize,
EVideoGridThumbnailSize,
EVideoListThumbnailSize,
EVideoFullScreenThumbnailSize,      
EAudioGridThumbnailSize,
EAudioListThumbnailSize,
EAudioFullScreenThumbnailSize,
EGridThumbnailSize,
EListThumbnailSize,
EFullScreenThumbnailSize,
EContactGridThumbnailSize,
EContactListThumbnailSize,
EContactFullScreenThumbnailSize,
EThumbnailSizeCount //last item, don't remove
} TThumbnailSize;
/**
 *  Thumbnail engine.
 *
 *  This is the main interface class to thumbnail engine. Thumbnail engine
 *  can be used to request thumbnails for different kinds of media objects.
 *
 *  The client using thumbnail engine must implement the
 *  MThumbnailManagerObserver. The observer interface is used to provide
 *  thumbnail data when it is available.
 *
 *  Typical use of thumbnail engine consists of 4 parts:
 *  - creating an engine instance using NewL
 *  - setting thumbnail parameters using SetThumbnailSizeL(), SetFlags(),
 *    and so on
 *  - creating an object source (CThumbnailObjectSource) and using it to
 *    request thumbnails
 *  - handling MThumbnailManagerObserver callbacks when the thumbnail request
 *    is complete
 *
 *  Here is an example of how thumbnail engine could be used by a typical
 *  application:
 *
 *  @code
 *
 *  #include <thumbnailmanagerobserver.h>
 *  #include <thumbnailmanager.h>
 *
 *  class CMyThumbnailControl: public CCoeControl,
 *                             public MThumbnailManagerObserver
 *      {
 *  public:
 *      CMyThumbnailControl();
 *      ~CMyThumbnailControl();
 *      ...
 *
 *      // Callbacks from MThumbnailManagerObserver for getting thumbnails
 *      void ThumbnailPreviewReady(
 *          MThumbnailData& aThumbnail,
 *          TThumbnailRequestId aId );
 *      void ThumbnailReady(
 *          TInt aError, 
 *          MThumbnailData& aThumbnail, 
 *          TThumbnailRequestId aId );
 *
 *  private:
 *      void ConstructL();
 *      CThumbnailManager* iManager;
 *      CFbsBitmap* iBitmap;
 *      }
 *
 *  _LIT( KTestFilePath, "e:\\TestImage.jpg" );
 *  _LIT( KTestFileType, "image/jpeg" );
 *
 *  void CMyThumbnailControl::ConstructL()
 *      {
 *      // Create Thumbnail Manager instance. This object is the observer.
 *      iManager = CThumbnailManager::NewL( *this ); 
 *
 *      // Set flags: If the aspect ratio of the media object does not match
 *      // 4:3 then we would like it to be cropped. We don’t mind getting
 *      // smaller images than requested.
 *      iManager->SetFlagsL( CThumbnailManager::ECropToAspectRatio |
 *                           CThumbnailManager::EAllowAnySize );
 *
 *      // Preferred size is 160x120 (or less)
 *      iManager->SetSizeL( TSize( 160, 120 ) );
 *
 *      // Get a preview thumbnail first, if available.
 *      // The preview thumbnail is delivered via a ThumbnailPreviewReady()
 *      // callback.
 *      iManager->SetQualityPreferenceL(
 *          CThumbnailManager::EOptimizeForQualityWithPreview );
 *
 *      // Create an object source representing a path to a file on local
 *      // file system.
 *      CThumbnailObjectSource* source = CThumbnailObjectSource::NewLC(
 *          KTestFilePath,   // File path
 *          KTestFileType ); // Let Thumbnail Manager know it’s a JPEG, so
 *                           // it doesn’t need to recognize the file format
 *
 *      // Issue the request using default priority
 *      iManager->GetThumbnailL( *source );
 *
 *      // If GetThumbnailL() did not leave, the ThumbnailReady() callback is
 *      // now guaranteed to be called, unless the request is cancelled or
 *      // CThumbnailManager instance is deleted.
 *
 *      // The source can be deleted immediately after issuing the request
 *      CleanupStack::PopAndDestroy( source );
 *      }
 *
 *  CMyThumbnailControl::~CMyThumbnailControl()
 *      {
 *      // Bitmap should be destroyed before Thumbnail Manager
 *      delete iBitmap;
 *      delete iManager;
 *      }
 *
 *  void CMyThumbnailControl::ThumbnailReady(
 *      TInt aError,
 *      MThumbnailData& aThumbnail,
 *      TThumbnailRequestId aId )
 *      {
 *      // This function must not leave.
 *
 *      delete iBitmap; iBitmap = NULL;
 *      if ( !aError )
 *          {
 *          // Claim ownership of the bitmap instance for later use
 *          iBitmap = aThumbnail.DetachBitmap();
 *
 *          // We can now use iBitmap in our Draw() method
 *          DrawDeferred();
 *          }
 *      else
 *          {
 *          // An error occurred while getting the thumbnail.
 *          // Perhaps we should show a broken image icon to the user.
 *          }
 *      }
 *
 *  @endcode
 *
 *  @lib thumbnailmanager.lib
 *  @since S60 v5.0
 */
NONSHARABLE_CLASS( CThumbnailManager ): public CBase
    {
public:
    /**
     * Flags for thumbnail creation.
     * These can be combined using bitwise or.
     */
    enum TThumbnailFlags
        {
        /**
         * Default flags. This means that:
         * - Thumbnail must be as large as requested (unless the actual
         *   object is smaller).
         * - Smaller thumbnails may be up scaled to desired resolution.
         * - Aspect ratio is maintained and thumbnails are not cropped. The
         *   resulting thumbnail may smaller in either width or height if
         *   the aspect ratio of the object does not match the aspect ratio
         *   of the requested size.
         */
        EDefaultFlags = 0, 

        /**
         * Allow thumbnails which are smaller than requested are. Thumbnail
         * bitmaps are never up scaled if this flag is set.
         */
        EAllowAnySize = 1, 

        /**
         * New thumbnail images are not created if this flag is set. Only
         * existing thumbnails may be returned. If a requested thumbnail does
         * not exist, KErrNotFound error is returned in ThumbnailReady()
         * callback.
         */
        EDoNotCreate = 2, 

        /**
         * Thumbnail images are cropped to match requested aspect ratio. If
         * this flag is set, the size of the resulting thumbnail always
         * matches the requested size.
         */
        ECropToAspectRatio = 4
    };

    /**  Quality versus speed preference setting */
    enum TThumbnailQualityPreference
        {
        /**
         * Prefer thumbnails in the highest quality possible disregarding
         * any negative impact on performance.
         */
        EOptimizeForQuality, 

        /**
         * Get thumbnails as fast as possible, even if
         * it means lower quality.
         */
        EOptimizeForPerformance, 

        /**
         * Get lower quality preview thumbnail as fast as possible first and
         * then a higher quality thumbnail later. The preview thumbnail is
         * provided in the ThumbnailPreviewReady() callback and the high
         * quality thumbnail in ThumbnailReady(). ThumbnailPreviewReady()
         * is not get called at all if a suitable existing thumbnail is not
         * found or if a high quality version is already available.
         */
        EOptimizeForQualityWithPreview
        };

    /**
     * Two-phased constructor.
     *
     * @since S60 v5.0
     * @param  aObserver Observer to receive notifications about completed
     *                   operations.
     * @return           New CThumbnailManager instance.
     */
    IMPORT_C static CThumbnailManager* NewL( MThumbnailManagerObserver&
        aObserver );

    /**
     * Two-phased constructor.
     *
     * @since S60 v5.0
     * @param  aObserver Observer to receive notifications about completed
     *                   operations.
     * @return           New CThumbnailManager instance (on cleanup stack).
     */
    IMPORT_C static CThumbnailManager* NewLC( MThumbnailManagerObserver&
        aObserver );

    /**
     * Destructor
     *
     * @since S60 v5.0
     */
    virtual ~CThumbnailManager();

    /**
     * Get the current display mode for thumbnail bitmaps.
     *
     * @since S60 v5.0
     * @return Current display mode for the thumbnail bitmaps.
     */
    virtual TDisplayMode DisplayMode()const = 0;

    /**
     * Set the current display mode for thumbnail bitmaps.
     *
     * @since S60 v5.0
     * @param aDisplayMode New display mode value for the thumbnail bitmaps.
     */
    virtual void SetDisplayModeL( TDisplayMode aDisplayMode ) = 0;

    /**
     * Get the current quality versus performance preference.
     *
     * @since S60 v5.0
     * @return Current quality versus performance preference.
     */
    virtual TThumbnailQualityPreference QualityPreference()const = 0;

    /**
     * Set quality versus performance preference.
     *
     * @since S60 v5.0
     * @param aQualityPreference New quality versus performance preference
     *                           value.
     */
    virtual void SetQualityPreferenceL( TThumbnailQualityPreference
        aQualityPreference ) = 0;

    /**
     * Get the current desired size for thumbnail bitmaps.
     *
     * @since S60 v5.0
     * @return Current desired size for thumbnail bitmaps (in pixels).
     */
    virtual const TSize& ThumbnailSize()const = 0;

    /**
     * Set desired size for thumbnail bitmaps.
     *
     * @since S60 v5.0
     * @param aThumbnailSize New quality for the desired thumbnail size.
     */
    virtual void SetThumbnailSizeL( const TSize& aThumbnailSize ) = 0;

    
    /**
     * Get current flags for thumbnail generation.
     *
     * @since S60 v5.0
     * @return Current flags.
     */
    virtual TThumbnailFlags Flags()const = 0;

    /**
     * Set flags for thumbnail generation. Several flags may be enabled
     * by combining the values using bitwise or.
     *
     * @since S60 v5.0
     * @param aFlags New flags.
     */
    virtual void SetFlagsL( TThumbnailFlags aFlags ) = 0;

    /**
     * Get a thumbnail for an object file. If a thumbnail already exists, it
     * is loaded and if a thumbnail does not exist, it is created
     * transparently. ThumbnailReady() callback will be called when the
     * operation is complete. In addition, ThumbnailPreviewReady()
     * callback may be called if EOptimizeForQualityWithPreview mode was
     * defined.
     *
     * Current values for display mode, thumbnail size, flags and performance
     * preference are used.
     *
     * @since S60 v5.0
     * @param aObjectSource      Source object or file
     * @param aClientData        Pointer to arbitrary client data.
     *                           This pointer is not used by the API for
     *                           anything other than returning it in the
     *                           ThumbnailReady callback.
     * @param aPriority          Priority for this operation
     * @return                   Thumbnail request ID. This can be used to
     *                           cancel the request or change priority.
     *                           The ID is specific to this CThumbnailManager
     *                           instance and may not be shared with other
     *                           instances.
     */
    virtual TThumbnailRequestId GetThumbnailL( CThumbnailObjectSource&
        aObjectSource, TAny* aClientData = NULL, TInt aPriority = CActive
        ::EPriorityStandard ) = 0;

    /**
     * Delete all thumbnails for a given object. This is an asynchronous
     * operation, which always returns immediately.
     *
     * @since S60 v5.0
     * @param aObjectSource      Source object or file
     */
    virtual void DeleteThumbnails( CThumbnailObjectSource& aObjectSource ) = 0;

    /**
     * Create thumbnail for a given object. This is an asynchronous
     * operation, which always returns immediately. No callbacks are
     * emitted.
     *
     * @since S60 v5.0
     * @param aObjectSource      Source object or file
     * @param aPriority          Priority for this operation
     * @return                   Thumbnail request ID. This can be used to
     *                           cancel the request or change priority.
     *                           The ID is specific to this CThumbnailManager
     *                           instance and may not be shared with other
     *                           instances.
     */
    virtual TThumbnailRequestId CreateThumbnails( CThumbnailObjectSource&
        aObjectSource, TInt aPriority = CActive::EPriorityIdle ) = 0;

    /**
     * Cancel a thumbnail operation.
     *
     * @since S60 v5.0
     * @param aId      Request ID for the operation to be cancelled.
     * @return         Symbian OS error code or KErrNone if cancelling was
     *                 successful.
     */
    virtual TInt CancelRequest( TThumbnailRequestId aId ) = 0;

    /**
     * Change the priority of a queued thumbnail operation.
     *
     * @since S60 v5.0
     * @param aId           Request ID for the request which to assign a new
     *                      priority.
     * @param aNewPriority  New priority value
     * @return              Symbian OS error code or KErrNone if change was
     *                      successful.
     */
    virtual TInt ChangePriority( TThumbnailRequestId aId, TInt aNewPriority ) = 0;

    /**
     * Get a list of supported file formats for object files.
     * 
     * The return value is a reference to a list that contains each
     * supported MIME type. There may also be wildcards, such as "image/*".
     * 
     * The returned reference is valid until CThumbnailManager is
     * destroyed or GetSupportedMimeTypesL() is called again.
     *
     * @since S60 v5.0
     * @return A list of supported MIME types. May contain wildcards.
     *         Ownership not transferred.
     */
    virtual const CDesCArray& GetSupportedMimeTypesL() = 0;

    /**
     * Delete thumbnails by TThumbnailId. This is an asynchronous
     * operation, which always returns immediately.
     *
     * @since S60 v5.0
     * @param aItemId     TThumbnailId
     */
    virtual void DeleteThumbnails( const TThumbnailId aItemId ) = 0;    

/**
     * Set desired size for thumbnail bitmaps.
     *
     * @since S60 v5.0
     * @param aThumbnailSize Desired thumbnail size.
     */    
    virtual void SetThumbnailSizeL( const TThumbnailSize aThumbnailSize ) = 0;

    /**
     * Get a persistent thumbnail for an object file. If a thumbnail already
     *  exists, it is loaded and if a thumbnail does not exist, it is created
     * transparently. ThumbnailReady() callback will be called when the
     * operation is complete. In addition, ThumbnailPreviewReady()
     * callback may be called if EOptimizeForQualityWithPreview mode was
     * defined.
     *
     * Current values for display mode, thumbnail size, flags and performance
     * preference are used.
     *
     * @since S60 v5.0
     * @param aThumbnailId       Thumbnail ID
     * @param aThumbnailSizeType Thumbnail size enumeration
     * @param aClientData        Pointer to arbitrary client data.
     *                           This pointer is not used by the API for
     *                           anything other than returning it in the
     *                           ThumbnailReady callback.
     * @param aPriority          Priority for this operation
     * @return                   Thumbnail request ID. This can be used to
     *                           cancel the request or change priority.
     *                           The ID is specific to this CThumbnailManager
     *                           instance and may not be shared with other
     *                           instances.
     */    
    virtual TThumbnailRequestId GetThumbnailL( const TThumbnailId aThumbnailId,
        TAny* aClientData = NULL, 
        TInt aPriority = CActive::EPriorityStandard ) = 0;
    
    
    /**
     * Set a thumbnail for an object file generated from buffer delivered in source 
     * object. ThumbnailReady() callback will be called when the
     * operation is complete. In addition, ThumbnailPreviewReady()
     * callback may be called if EOptimizeForQualityWithPreview mode was
     * defined.
     *
     * Current values for display mode, thumbnail size, flags and performance
     * preference are used.
     *
     * @since S60 v5.0
     * @param aThumbnailId       Thumbnail ID
     * @param aThumbnailSizeType Thumbnail size enumeration
     * @param aClientData        Pointer to arbitrary client data.
     *                           This pointer is not used by the API for
     *                           anything other than returning it in the
     *                           ThumbnailReady callback.
     * @param aPriority          Priority for this operation
     * @return                   Thumbnail request ID. This can be used to
     *                           cancel the request or change priority.
     *                           The ID is specific to this CThumbnailManager
     *                           instance and may not be shared with other
     *                           instances.
     */    
    virtual TThumbnailRequestId SetThumbnailL( CThumbnailObjectSource& aObjectSource,
        TAny* = NULL, 
        TInt aPriority = CActive::EPriorityIdle ) = 0;
    
    
    /**
     * Import an image to be used as thumbnail for an object. If a
     * thumbnail already exists, it is loaded and if a thumbnail does not
     * exist, it is created transparently. ThumbnailReady() callback will be
     * called when the operation is complete. In addition, ThumbnailPreviewReady()
     * callback may be called if EOptimizeForQualityWithPreview mode was
     * defined.
     * 
     * Current values for display mode, thumbnail size, flags and performance
     * preference are used.
     *
     * @since S60 v5.0
     * @param aObjectSource      Source object or file
     * @param aTargetUri         Target URI to which the imported thumbnail is linked.
     * @param aClientData        Pointer to arbitrary client data.
     *                           This pointer is not used by the API for
     *                           anything other than returning it in the
     *                           ThumbnailReady callback.
     * @param aPriority          Priority for this operation
     * @return                   Thumbnail request ID. This can be used to
     *                           cancel the request or change priority.
     *                           The ID is specific to this CThumbnailManager
     *                           instance and may not be shared with other
     *                           instances.
     */
     virtual TThumbnailRequestId ImportThumbnailL( CThumbnailObjectSource& aObjectSource,
        const TDesC& aTargetUri, TAny* aClientData = NULL,
        TInt aPriority = CActive::EPriorityIdle ) = 0;

     /**
      * Update Thumbnails by TThumbnailId. This is an asynchronous
      * operation, which always returns immediately.
      *
      * @since S60 v5.0
      * @param aItemId       TThumbnailId
      * @param aPath         (New) path for the Thumbnail
      * @param aOrientation  Thumbnail orientation
      * @param aModified     Last modified
      */
      virtual void UpdateThumbnailsL( const TThumbnailId aItemId, const TDesC& aPath,
                                      const TInt aOrientation, const TInt64 aModified, const TInt aPriority  ) = 0;
      
      /**
       * Rename Thumbnails. This is an asynchronous
       * operation, which always returns immediately.
       *
       * @since S60 v5.0
       * @param aCurrentPath     Current path of the Thumbnail
       * @param aNewPath         New path for the Thumbnail
       * @param aPriority        Priority for this operation
       * @return                 Thumbnail request ID. This can be used to
       *                         cancel the request or change priority.
       *                         The ID is specific to this CThumbnailManager
       *                         instance and may not be shared with other
       *                         instances.
       */
       virtual TThumbnailRequestId RenameThumbnailsL( const TDesC& aCurrentPath, 
               const TDesC& aNewPath, TInt aPriority = CActive::EPriorityIdle ) = 0;

       /**
        * Set optional request observer for getting information about completed 
        * requests that don't include a thumbnail.
        *
        * @since Symbian^3
        * @param aObserver Observer to receive notifications.
        */
       virtual void SetRequestObserver( MThumbnailManagerRequestObserver& aObserver ) = 0;
       
       /**
        * Remove optional request observer.
        *
        * @since Symbian^3
        */
       virtual void RemoveRequestObserver() = 0;
};

#endif // THUMBNAILMANAGER_H
