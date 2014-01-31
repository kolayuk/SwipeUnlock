// Copyright (c) 2005-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
//

/**
 @file
 @publishedAll
 @released
*/

#ifndef IMAGEFRAME_H
#define IMAGEFRAME_H

#include <e32std.h>
#include <e32base.h> 
#include <imageframeconst.h>

/** 
The base class for TFrameFormat. Users implement specific frame formats by deriving from this class. 
Symbian provides a particular implementation in the TFrameFormat class.
Each class derived from this class should be identified by a unique UID value, denoting its type.
All subclasses should provide implementations of DuplicateL().

@see TFrameFormat
*/ 
class TFrameFormatBase
	{
public:	
	IMPORT_C TUid Type() const;
	
	/** 
	Creates a duplicate instance of the frame format object on the heap.
	
	@return The pointer to the newly created object cast as class TFrameFormatBase. 
	*/
	virtual TFrameFormatBase* DuplicateL() const=0;
	
protected:
	IMPORT_C explicit TFrameFormatBase(TUid aType);
	
private:
	// reserved for future expansion
	IMPORT_C virtual void Reserved1();
	IMPORT_C virtual void Reserved2();
	IMPORT_C virtual void Reserved3();
	IMPORT_C virtual void Reserved4();
	
private:
	// Format of the specific type holder
	TUid iType; 
		
	// reserved for future expansion
	TInt iReserved1;
	TInt iReserved2;
	TInt iReserved3;
	};

/** 
This class is a specific implementation of TFrameFormatBase. An object of this class provides 
colour space and sampling information based on a specific image format code. 
*/
class TFrameFormat: public TFrameFormatBase
	{
public:	
	IMPORT_C explicit TFrameFormat(TUid aFormatCode);
	IMPORT_C TFrameFormatBase* DuplicateL() const;
	IMPORT_C TUid ColourSpace() const;
	IMPORT_C TUid Sampling() const;
	IMPORT_C TUid FormatCode() const;

	IMPORT_C void SetColourSpace(TUid aColourSpace);	
	
private: 
	// The image frame colour space
	TUid	iColourSpace;
	// The frame sampling 
	TUid 	iSampling;
	// The image frame format code which uniquely identifies all other parameters. */  
	TUid 	iFormatCode; 
	};

/** 
Base class for TFrameLayout. Individual subclasses are identified by their specific UID value.
These classes are used to describe the memory layout of a specific Image Frame. 
*/ 
class TFrameLayoutBase
	{	
public:	
	IMPORT_C TUid Type() const;
	
	/** 
	Creates a duplicate instance of the frame layout object on the heap.
	
	@return The pointer to the newly created object cast as class TFrameLayoutBase. 
	*/
	virtual TFrameLayoutBase* DuplicateL() const=0;
	
protected: 
	IMPORT_C explicit TFrameLayoutBase(TUid aType);

private:
	// reserved for future expansion
	IMPORT_C virtual void Reserved1();
	IMPORT_C virtual void Reserved2();
	IMPORT_C virtual void Reserved3();
	IMPORT_C virtual void Reserved4();
			
private:
	// Layout specific type holder
	TUid iType; 
		
	// Reserved for future expansion
	TInt iReserved1;
	TInt iReserved2;
	TInt iReserved3;
	};

/** 
Class TFrameLayout is a concrete implementation of TFrameLayoutBase class.
It serves as a container for parameters that describe the memory organisation of 
the data encapsulated by a specific CImageFrame object.
Image data is stored in planes. Each plane is characterised by  
the byte offset from the start of the image frame memory, and its maximum size, 
current length and scanlength.
*/	
class TFrameLayout: public TFrameLayoutBase
	{		
 		
public:
	IMPORT_C explicit TFrameLayout(TInt aPlanes);
	IMPORT_C TFrameLayoutBase* DuplicateL() const;	
	
    IMPORT_C TInt Planes() const;
	IMPORT_C TInt Start(TInt aIndex) const;
	IMPORT_C TInt Length(TInt aIndex) const;
	IMPORT_C TInt CurrentLength(TInt aIndex) const;
	IMPORT_C TInt ScanLength(TInt aIndex) const;
	
	IMPORT_C void SetStart(TInt aIndex, TInt aStart);
	IMPORT_C void SetLength(TInt aIndex, TInt aLength );
	IMPORT_C void SetCurrentLength(TInt aIndex, TInt aCurrentLength);
	IMPORT_C void SetScanLength(TInt aIndex, TInt aScanLength);

private:
	// The number of planes in this image. Value < KMaxPlanesInFrame. 
	TInt iPlanes;				   
	// The offset of each plane from the start of the memory referenced by this image frame. 
	TInt iStart[KMaxPlanesInFrame]; 
	// The length of each image plane in bytes.
	TInt iLength[KMaxPlanesInFrame]; 
	// The length of the data stored in each image plane in bytes.
	TInt iCurrentLength[KMaxPlanesInFrame];	
	// The width of the stride for each plane.
	TInt iScanLength[KMaxPlanesInFrame];
	};

/** 
CImageFrame class exposes an API for accessing binary image data in a uniform way.
It is implemented as a wrapper around TDes8 or RChunk objects. 
*/	
class CImageFrame : public CBase 
    {
public:  
    IMPORT_C static CImageFrame* NewL(const TDes8& aBuffer, TInt aMaxBufferSize);
 								  
    IMPORT_C static CImageFrame* NewL(const TDes8& aBuffer,
    								  TInt aMaxBufferSize, 
				 	   				  const TSize& aFrameSize, 
				 					  const TFrameFormatBase& aFrameFormat,
									  const TFrameLayoutBase& aFrameLayout); 
										  
	IMPORT_C static CImageFrame* NewL(const RChunk* aBuffer, 
									  TInt aMaxBufferSize,		
						   			  TInt aDataOffset);

	IMPORT_C static CImageFrame* NewL(const RChunk* aBuffer,
									  TInt aMaxBufferSize, 
								      TInt aDataOffset, 
		 					 	  	  const TSize& aFrameSize,
		 					 	  	  const TFrameFormatBase& aFrameFormat,
		 					 	  	  const TFrameLayoutBase& aFrameLayout); 
    
	IMPORT_C virtual const TFrameFormatBase& FrameFormat() const;	
	IMPORT_C virtual void SetFrameFormatL(const TFrameFormatBase& aFormat);
	
	IMPORT_C virtual const TFrameLayoutBase& FrameLayout() const;	
	IMPORT_C virtual void SetFrameLayoutL(const TFrameLayoutBase& aFrameLayout);

	IMPORT_C virtual const TSize& FrameSizeInPixels() const;	
	IMPORT_C virtual void SetFrameSizeInPixels(const TSize& aFrameSize);

	IMPORT_C virtual TDes8& Data();
	IMPORT_C virtual const TDesC8& Data() const;
	
    IMPORT_C virtual TInt MaxBufferSize() const;
    IMPORT_C virtual TBool IsChunk() const;

	IMPORT_C virtual RChunk& DataChunk();
	IMPORT_C virtual TInt DataOffset() const;
    
    IMPORT_C ~CImageFrame();
	
protected:
	IMPORT_C CImageFrame();
	
    IMPORT_C void ConstructL(const TDes8& aBuffer, TInt aMaxBufferSize);
 								  
    IMPORT_C void ConstructL(const TDes8& aBuffer, 
    						 TInt aMaxBufferSize,
				 	   		 const TSize& aFrameSize, 
				 			 const TFrameFormatBase& aFrameFormat,
							 const TFrameLayoutBase& aFrameLayout); 
										  
	IMPORT_C void ConstructL(const RChunk* aBuffer, 
							 TInt aMaxBufferSize, 
							 TInt aDataOffset);

	IMPORT_C void ConstructL(const RChunk* aBuffer, 
							 TInt aMaxBufferSize,
						  	 TInt aDataOffset, 
 					 	     const TSize& aFrameSize,
 					 	  	 const TFrameFormatBase& aFrameFormat,									
 					 	  	 const TFrameLayoutBase& aFrameLayout); 

private: 					 	  	 
	// for future development
	IMPORT_C virtual void Reserved1();
	IMPORT_C virtual void Reserved2();
	IMPORT_C virtual void Reserved3();
	IMPORT_C virtual void Reserved4();
	
private:
    class CBody; 
    CBody* iBody;
    };

#endif // IMAGEFRAME_H
