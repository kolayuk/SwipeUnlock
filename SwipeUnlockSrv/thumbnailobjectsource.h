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
* Description:  Class for encapsulating the data source for objects.
 *
*/


#ifndef THUMBNAILOBJECTSOURCE_H
#define THUMBNAILOBJECTSOURCE_H

#include <e32base.h>
#include <f32file.h>

typedef TUint32 TThumbnailId;

class CFbsBitmap;

/**
 *  Object source for thumbnails.
 *
 *  Class for encapsulating the data source for objects.
 *
 *  @since S60 v5.0
 */
NONSHARABLE_CLASS( CThumbnailObjectSource ): public CBase
    {
public:
    /**
     * Construct a new CThumbnailObjectSource referring to an URI.
     * @param aUri      Object URI or a full path to a file in the file system.
     * @param aMimeType MIME type. Optional, but should be specified if known.
     * @since S60 v5.0
     * @return New CThumbnailObjectSource instance.
     */
    IMPORT_C static CThumbnailObjectSource* NewL( const TDesC& aUri, const
        TDesC& aMimeType = KNullDesC );

    /**
     * Construct a new CThumbnailObjectSource referring to an URI.
     * @param aUri      Object URI or a full path to a file in the file system.
     * @param aMimeType MIME type. Optional, but should be specified if known.
     * @since S60 v5.0
     * @return New CThumbnailObjectSource instance.
     */
    IMPORT_C static CThumbnailObjectSource* NewLC( const TDesC& aUri, const
        TDesC& aMimeType = KNullDesC );

    /**
     * Construct a new CThumbnailObjectSource referring to a file handle.
     * The file handle must refer to an open file and it must remain
     * valid until this object source is deleted.
     *
     * @param aFile     File handle.
     * @param aMimeType MIME type. Optional, but should be specified if known.
     * @since S60 v5.0
     * @return New CThumbnailObjectSource instance.
     */
    IMPORT_C static CThumbnailObjectSource* NewL( const RFile& aFile, const
        TDesC& aMimeType = KNullDesC );

    /**
     * Construct a new CThumbnailObjectSource referring to a file handle.
     * The file handle must refer to an open file and it must remain
     * valid until this object source is deleted.
     *
     * @param aFile     File handle.
     * @param aMimeType MIME type. Optional, but should be specified if known.
     * @since S60 v5.0
     * @return New CThumbnailObjectSource instance.
     */
    IMPORT_C static CThumbnailObjectSource* NewLC( const RFile& aFile, const TDesC& aMimeType = KNullDesC ); 

    /**
     * Destructor
     *
     * @since S60 v5.0
     */
    virtual ~CThumbnailObjectSource();

public:

    /**
     * Returns file handle.
     *
     * @since S60 v5.0
     * @return reference to file handle
     */
    IMPORT_C RFile& FileHandle();

    /**
     * Returns source uri.
     *
     * @since S60 v5.0
     * @return uri
     */
    IMPORT_C const TDesC& Uri();

private:

    /**
     * C++ default constructor
     *
     * @since S60 v5.0
     */
    CThumbnailObjectSource();

    /**
     * Symbian 2nd phase constructor can leave.
     *
     * @since S60 v5.0
     * @param aUri Object URI or a full path to a file in the file system.
     * @param aMimeType MIME type. Optional, but should be specified if known.
     */
    void ConstructL( const TDesC& aUri, const TDesC& aMimeType );

    /**
     * Symbian 2nd phase constructor can leave.
     *
     * @since S60 v5.0
     * @param aFile File handle.
     * @param aMimeType MIME type. Optional, but should be specified if known.
     */
    void ConstructL( const RFile& aFile, const TDesC& aMimeType );

    /**
     * Symbian 2nd phase constructor can leave.
     *
     * @since S60 v5.0
     * @param aURI URI.
     * @param aMimeType MimeType.
     * @param aThumbnailId ThumbnailId
     */
    void ConstructL( const TDesC& aUri, const TDesC& aMimeType, TThumbnailId aThumbnailId );

    /**
     * Symbian 2nd phase constructor can leave.
     *
     * @since S60 v5.0
     * @param aBitmap Bitmap.
     * @param aURI URI.
     */   
    void ConstructL( CFbsBitmap* aBitmap, const TDesC& aUri );

    /**
     * Symbian 2nd phase constructor can leave.
     *
     * @since S60 v5.0
     * @param aBuffer Buffer.
     * @param aMimeType MIME type. Optional, but should be specified if known.
     * @param aURI URI.
     */
    void ConstructL( TDesC8* aBuffer, const TDesC& aMimeType, const TDesC& aUri );    
    
    /**
     * Symbian 2nd phase constructor can leave.
     *
     * @since Symbian^3
     * @param aUri Object URI or a full path to a file in the file system.
     * @param aTargetUri      For linking the thumbnail to a different URI.
     * @param aMimeType MIME type. Optional, but should be specified if known.
     */
    void ConstructL( const TDesC& aUri, const TDesC& aTargetUri, const TDesC& aMimeType );
    
private:
    // data

    /**
     * File
     */
    RFile iFile;

    /**
     * Uri
     */
    HBufC* iUri; // own

    /**
     * Mime type
     */
    HBufC8* iMimeType; // own
    
    /**
     * Buffer
     */
    TDesC8* iBuffer; // own
    
    /**
     * Bitmap
     */
    CFbsBitmap* iBitmap; // own
    
    /**
     * ThumbnailId
     */    
    TThumbnailId iThumbnailId; //own
    
    /**
     * Uri
     */
    HBufC* iTargetUri; // own
	
public:
	    
    /**
     * Construct a new CThumbnailObjectSource referring to a buffer 
     * containing an image.
     *
     * @param aBuffer   Buffer.
     * @param aUri      Object URI or a full path to a file in the file system.
     * @since S60 v5.0
     * @return New CThumbnailObjectSource instance.
     */    
    IMPORT_C static CThumbnailObjectSource* NewL( CFbsBitmap*  aBitmap, const TDesC& aUri );

    /**
     * Construct a new CThumbnailObjectSource referring to a buffer 
     * containing an image.
     *
     * @param aFile     File handle.
     * @param aUri      Object URI or a full path to a file in the file system.
     * @since S60 v5.0
     * @return New CThumbnailObjectSource instance.
     */        
    IMPORT_C static CThumbnailObjectSource* NewLC( CFbsBitmap*  aBitmap, const TDesC& aUri );
 
    /**
     * Construct a new CThumbnailObjectSource referring to a buffer 
     * containing an image.
     *
     * @param aBuffer   Buffer.
     * @param aUri      Object URI or a full path to a file in the file system.
     * @since S60 v5.0
     * @return New CThumbnailObjectSource instance.
     */       
    IMPORT_C static CThumbnailObjectSource* NewL( TDesC8* aBuffer,  TDesC& aMimeType, 
        const TDesC& aUri );
    
    /**
     * Construct a new CThumbnailObjectSource referring to a buffer 
     * containing an image.
     *
     * @param aBuffer   Buffer.
     * @param aMimeType MIME type. Optional, but should be specified if known.
     * @param aUri      Object URI or a full path to a file in the file system.
     * @since S60 v5.0
     * @return New CThumbnailObjectSource instance.
     */       
    IMPORT_C static CThumbnailObjectSource* NewLC( TDesC8* aBuffer,  TDesC& aMimeType, 
        const TDesC& aUri);

    /**
     * Construct a new CThumbnailObjectSource referring to an URI.
     * @param aUri      Object URI or a full path to a file in the file system.
     * @param aMimeType MIME type. Optional, but should be specified if known.
     * @since S60 v5.0
     * @return New CThumbnailObjectSource instance.
     */
    IMPORT_C static CThumbnailObjectSource* NewL( const TDesC& aUri, 
        TThumbnailId aThumbnailId = 0, const TDesC& aMimeType = KNullDesC );

    /**
     * Construct a new CThumbnailObjectSource referring to an URI.
     * @param aUri      Object URI or a full path to a file in the file system.
     * @param aMimeType MIME type. Optional, but should be specified if known.
     * @since S60 v5.0
     * @return New CThumbnailObjectSource instance.
     */
    IMPORT_C static CThumbnailObjectSource* NewLC( const TDesC& aUri,
        TThumbnailId aThumbnailId = 0, const TDesC& aMimeType = KNullDesC );
    	 
    /**
     * Returns source buffer.
     *
     * @since S60 v5.0
     * @return buffer
     */  
    IMPORT_C TDesC8* Buffer();
    
    /**
     * Gets ownership of buffer from source object.
     * After that Buffer() returns NULL.
     *
     * @since S60 v5.0
     * @return buffer
     */
    IMPORT_C TDesC8* GetBufferOwnership();
    
    /**
     * Gets MIME type.
     *
     * @since S60 v5.0
     * @return MIME type
     */   
    IMPORT_C const TDesC8& MimeType();
    
    /**
     * Gets ThumbnailId.
     *
     * @since S60 v5.0
     * @return ThumbnailId 
     */     
    IMPORT_C TThumbnailId Id(); 	    
    
    /**
     * Returns source bitmap.
     *
     * @since S60 v5.0
     * @return bitmap
     */  
    IMPORT_C CFbsBitmap* Bitmap();
    
    /**
     * Gets ownership of bitmap from source object.
     * After that Bitmap() returns NULL.
     *
     * @since S60 v5.0
     * @return bitmap
     */
    IMPORT_C CFbsBitmap* GetBitmapOwnership();
    
    /**
     * Construct a new CThumbnailObjectSource referring to an URI.
     * @param aUri      Object URI or a full path to a file in the file system.
     * @param aTargetUri      For linking the thumbnail to a different URI.
     * @param aMimeType MIME type. Optional, but should be specified if known.
     * @since Symbian^3
     * @return New CThumbnailObjectSource instance.
     */
    IMPORT_C static CThumbnailObjectSource* NewL( const TDesC& aUri, 
            const TDesC& aTargetUri, const TDesC& aMimeType );

    /**
     * Construct a new CThumbnailObjectSource referring to an URI.
     * @param aUri      Object URI or a full path to a file in the file system.
     * @param aTargetUri      For linking the thumbnail to a different URI.
     * @param aMimeType MIME type. 
     * @since Symbian^3
     * @return New CThumbnailObjectSource instance.
     */
    IMPORT_C static CThumbnailObjectSource* NewLC( const TDesC& aUri, 
            const TDesC& aTargetUri, const TDesC& aMimeType );
    
    /**
     * Returns target uri.
     *
     * @since Symbian^3
     * @return uri
     */
    IMPORT_C const TDesC& TargetUri();
};

#endif // THUMBNAILOBJECTSOURCE_H
