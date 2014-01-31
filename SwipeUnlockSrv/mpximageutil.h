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
* Description:  Class declaration of CMPXImageUtil.
*
*/


#ifndef CMPXIMAGEUTIL_H
#define CMPXIMAGEUTIL_H

//  INCLUDES

#include "mpxalbumartutilobserver.h"


// FORWARD DECLARATIONS
class CFbsBitmap;
class CBitmapScaler;
class CImageDecoder;

// CLASS DECLARATION

/**
*  Image Conversion Class.
**/
class CMPXImageUtil : public CActive
    {
public:
   
	// states for this engine
  	enum TState 
	    {
	    EIdle = 0,
	    EDecoding,
	    EScaling
	    };

public:  // Constructors and destructor
        
    /**
    * Two-phased constructor.
    * @param aObserver ablum art observer
    * @return A pointer to a newly created object
    */
    static CMPXImageUtil* NewL(MMPXAlbumArtUtilObserver& aObserver);

    /**
    * Destructor.
    */
    ~CMPXImageUtil();

private:

    /**
    * C++ default constructor.
    */
    CMPXImageUtil(MMPXAlbumArtUtilObserver& aObserver); 

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();  

public: // New functions
        
    /*
    * Starts to decode an image from a file. 
    * @param aFileName Full path and filename of the image to be decoded.
    * @param aSize The size of the required destination BMP.
    * @param aDisplayMode the display mode of the destination BMP
    */
    void StartToDecodeL(const TDesC& aFileName, 
                        const TSize& aSize, 
                        TDisplayMode aDisplayMode = EColor64K);
  
    /*
    * Starts to decode an image from JPG buffer
    * @param aSize The size of the required destination JPG
    * @param aAlbumArt The pointer to the JPG buffer
    * @param aDisplayMode the display mode of the destination JPG
    */
    void StartToDecodeL(const TSize& aSize, 
                        HBufC8* aAlbumArt, 
                        TDisplayMode aDisplayMode = EColor64K);

    /*
    * Cancel outstanding asynch requests
    */
    void CancelRequest();
    
private: // New functions

    /**
    * Scales iBitmap to iSize 
    **/
    void ScaleL();
    TSize CalculateDecodeSize(const TSize& aSize);

private: // Functions from base classes

    /**
    * Cancellation of an outstanding request.
    */
    void DoCancel();

    /**
    * Handles an active object’s request completion event.
    */
    void RunL();
      
private:    // Data

    MMPXAlbumArtUtilObserver&       iObserver;      // Album art util observer
    CFbsBitmap*                     iBitmap;        // decoded image
    CImageDecoder*                  iImageDecoder;  // decoder
    CBitmapScaler*                  iScaler;        // bitmap scaler
    TSize                           iSize;          // desired size of the bitmap
    TState                          iState;         // engine state
    RFs                             iFs;            // for opening/saving images from/to files
    HBufC8*                         iImageData;     // Album art image data (owned)
    TBool                           iScaleRquired;
    };

#endif // CMPXIMAGEUTIL_H   
            
// End of File
