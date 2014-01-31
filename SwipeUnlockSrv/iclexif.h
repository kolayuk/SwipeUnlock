// Copyright (c) 2004-2009 Nokia Corporation and/or its subsidiary(-ies).
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
// This is the public client API for EXIF-enabled ICL modules
// 
//

#ifndef __CEXIFICL_H__
#define __CEXIFICL_H__


#include <imageconversion.h>
#include <icl/imagetransformpluginext.h>
#include <icl/imageplugin.h>

/**
@publishedAll
@released

IFD number representing Exif IFD 0.

For use in MExifMetadata methods when reading or writing IFD 0 tags other than GPS tags.
In other words, for reading or writing any of the following tags:
	- IFD 0 TIFF tags (i.e. IFD 0 tags)
	- IFD 0 Exif tags (i.e. Exif sub-IFD tags)
	- Interoperability IFD tags

Note: To read or write GPS tags, use the IFD constant KExifGpsIfd instead.
*/
const TUint KExifIfdZero = 0;

/**
@publishedAll
@released

IFD number representing Exif IFD 1.

For use in MExifMetadata methods when reading or writing tags related to thumbnail (i.e. IFD 1 tags).
*/
const TUint KExifIfdOne = 1;

/**
@publishedAll
@released

IFD number representing the IFD 0 sub-IFD for GPS (i.e. the GPS IFD).

For use in MExifMetadata methods when reading or writing GPS tags.
*/
const TUint KExifGpsIfd = 0x00040000;

/**
@publishedAll
@released

describes a rational value
*/
struct TRational
	{
	/** numerator of the rational
	*/
	union
		{
		TInt iNumerator;
		TUint iUNumerator;	
		};
	/** denominator of the rational. No checking is processed to know if this is null or not
	*/
	union
		{
		TInt iDenominator;
		TUint iUDenominator;
		};
	};


/**
@publishedAll
@released

generic accessor to read the tags from exif metadata.

Note: The aIfd argument in MExifMetadataReader methods should be set as follows:
	- When reading an IFD 0 tag that is not a GPS tag, use KExifIfdZero. 
	- When reading a tag related to thumbnail, use KExifIfdOne.
	- When reading a GPS tag, use KExifGpsIfd.
 
The TExifReaderUtility class offers a friendlier interface to access these tags.

@see TExifReaderUtility
*/
class MExifMetadataReader 
	{
public:
	/**
	Get the data associated with a signed or unsigned 32-bit integer EXIF/DCF tag/IFD. 
	If used to get unsigned data, it is up to the caller to do the appropriate typecast of aParam. 
	
	@param  aTag
		the tag id where the data is stored
	@param	aIfd
		the ifd section in which the tag is stored.
	@param aParam
		on return, the value of the tag
		
	@return error code
		KErrArgument if the requested data type does not match with the tag.
		KErrNotSupported if called on an encoding module.
		KErrNotFound if the tag cannot be found.
	*/
	virtual TInt GetIntegerParam(TUint aTag, TUint aIfd, TInt& aParam) const = 0;

	/**
	Get the data associated with an unsigned short (16-bit) integer EXIF/DCF tag/IFD. 
	
	@param  aTag
		the tag id where the data is stored
	@param	aIfd
		the ifd section in which the tag is stored.
	@param aParam
		on return, the value of the tag
		
	@return error code
		KErrArgument if the requested data type does not match with the tag.
		KErrNotSupported if called on an encoding module.
		KErrNotFound if the tag cannot be found.
	*/
	virtual TInt GetShortParam(TUint aTag, TUint aIfd, TUint16& aParam) const = 0;

	/**
	Get the data associated with a signed or unsigned rational EXIF/DCF tag/IFD. 
	If used to get an unsigned rational, it is up to the caller to typecast aNumer & aDenom as appropriate. 
	
	@param  aTag
		the tag id where the data is stored
	@param	aIfd
		the ifd section in which the tag is stored.
	@param aNumer
		on return, the numerator value of the tag
	@param aDenom
		on return, the denominator value of the tag
		
	@return error code
		KErrArgument if the requested data type does not match with the tag.
		KErrNotSupported if called on an encoding module.
		KErrNotFound if the tag cannot be found.
	*/
	virtual TInt GetRationalParam(TUint aTag, TUint aIfd, TInt& aNumer, TInt& aDenom) const = 0;
	/**
	Get the data associated with an 8-bit (e.g. ASCII, Undefined or Byte) EXIF/DCF tag/IFD. 
	
	Ownership of the buffer pointed to by aParam transfers to the client, which is therefore responsible for deleting the buffer when required. 

	Note: The client should always initialise aParam to NULL, and the plugin should only assign to this parameter when ready to transfer ownership.

	Note: If using this method to retrieve ASCII data, the returned data will not be NULL terminated.

	Note: If using this method to retrieve Undefined data, the raw data will be returned, exactly as it appears in the tag value.  Thus if the tag
	is one that includes a character code prefix, then this prefix will be included in the returned data. See table 6 of the Exif 2.2 specification for a list of character code prefixes.
	
	@param  aTag
		the tag id where the data is stored
	@param	aIfd
		the ifd section in which the tag is stored.
	@param aParam
		on return, the value of the tag
		
	@return error code
		KErrArgument if the requested data type does not match with the tag.
		KErrNotSupported if called on an encoding module.
		KErrNotFound if the tag cannot be found.
	*/
	virtual TInt GetParam8(TUint aTag, TUint aIfd, HBufC8*& aParam) const = 0;

	/**
	Get the data associated with a 16-bit EXIF/DCF tag/IFD. 
	
	Ownership of the buffer pointed to by aParam transfers to the client, which is therefore responsible for deleting the buffer when required. 

	Note: The client should always initialise aParam to NULL, and the plugin should only assign to this parameter when ready to transfer ownership.

	Note: This method is not recommended.  To get 16-bit data from a tag of undefined type, it is recommended that GetParam8() be used instead. The HBufC8* returned by GetParam8() can then be converted into an HBufC16* as needed.

	If this method is used, please be aware of the following:
		- It may only be used with the tags 0x9286 (UserComment), 0x001B (GpsProcessingMethod) & 0x001C (GpsAreaInformation).
		- The supported tags might not contain 16-bit data.  Only use this method if you are certain that the tag contain 16-bit data.  If used on a tag containing 8-bit data, the 8-bit
		data will be returned in the HBufC16* which will have to be manually converted to an HBufC8*.
		- The first 8 bytes of the returned HBufC16* may contain a Character Code prefix. See table 6 of the Exif 2.2 specification for a list of Character Code prefixes.
		- The length of the returned HBufC16* will include the length of the character code prefix if present.

	@param  aTag
		the tag id where the data is stored
	@param	aIfd
		the ifd section in which the tag is stored.
	@param aParam
		on return, the value of the tag
		
	@return error code
		KErrArgument if the requested data type does not match with the tag.
		KErrNotSupported if called on an encoding module.
		KErrNotFound if the tag cannot be found.
	*/
	virtual TInt GetParam16(TUint aTag, TUint aIfd, HBufC16*& aParam) const = 0;

	/**
	Get the data associated with an array of signed or unsigned 32-bit integers EXIF/DCF tag/IFD. 
	If being used to get unsigned integers, it is up to the caller to typecast them as appropriate. 
	
	@param  aTag
		the tag id where the data is stored
	@param	aIfd
		the ifd section in which the tag is stored.
	@param aParam
		on return, the array is filled with the list of values in this tag
		
		Note: aParam will be resized to fit the number of data elements read.
		
	@return error code
		KErrArgument if the requested data type does not match with the tag.
		KErrNotSupported if called on an encoding module.
		KErrNotFound if the tag cannot be found.
	*/
	virtual TInt GetIntegerArrayParam(TUint aTag, TUint aIfd, CArrayFix<TInt>& aParam) const = 0;

	/**
	Get the data associated with an array of unsigned short (16-bit) integers EXIF/DCF tag/IFD. 
	
	@param  aTag
		the tag id where the data is stored
	@param	aIfd
		the ifd section in which the tag is stored.
	@param aParam
		on return, the array is filled with the list of values in this tag
		
		Note: aParam will be resized to fit the number of data elements read.
		
	@return error code
		KErrArgument if the requested data type does not match with the tag.
		KErrNotSupported if called on an encoding module.
		KErrNotFound if the tag cannot be found.
	*/
	virtual TInt GetShortArrayParam(TUint aTag, TUint aIfd, CArrayFix<TUint16>& aParam) const = 0;

	/**
	Get the data associated with an array of signed or unsigned rationals EXIF/DCF tag/IFD. 
	If used to get unsigned rational data, it is up to the client to typecast the components as appropriate.  
	
	@param  aTag
		the tag id where the data is stored
	@param	aIfd
		the ifd section in which the tag is stored.
	@param aParam
		on return, the array is filled with the list of values in this tag
		
		Note: aParam will be resized to fit the number of data elements read.
		
	@return error code
		KErrArgument if the requested data type does not match with the tag.
		KErrNotSupported if called on an encoding module.
		KErrNotFound if the tag cannot be found.
	*/
	virtual TInt GetRationalArrayParam(TUint aTag, TUint aIfd, CArrayFix<TRational>& aParam) const = 0;
	};


/**
@publishedAll
@released

generic accessor to write the tags from exif metadata.

Note: The aIfd argument in MExifMetadataWriter methods should be set as follows:
	- When writing to an IFD 0 tag that is not a GPS tag, use KExifIfdZero. 
	- When writing to a tag related to thumbnail, use KExifIfdOne.
	- When writing to a GPS tag, use KExifGpsIfd.

The TExifWriterUtility class offers a friendlier interface to access these tags.

@see TExifWriterUtility 
*/
class MExifMetadataWriter
	{
public:
	// Setters
	/**
	Set the data associated with an 8-bit (e.g. ASCII, Undefined or Byte) EXIF/DCF tag/IFD.
	
	Note: If setting non-NULL terminated ASCII data, this method will add a NULL terminator to it provided that doing so will not cause the length of the tag value to be exceeded. If the length would be exceeded KErrArgument will be returned.

	Note: This method will set other (non-ASCII) 8-bit data exactly as-is.

	@param  aTag
		the tag id where the data is stored
	@param	aIfd
		the ifd section in which the tag is stored.
	@param aParam
		the value of the tag
		
	@return error code
		KErrNotSupported if called on a decoding module. 
		KErrNotSupported if the plugin does not support the specified tag.
		KErrArgument if the requested data type does not match with the tag.
	*/
	virtual TInt SetParam8(TUint aTag, TUint aIfd, HBufC8* aParam) = 0;

	/**
	Set 16-bit Unicode data into EXIF/DCF tag/IFDs that support it (e.g.0x9286 (UserComment), 0x001B (GpsProcessingMethod) or 0x001C (GpsAreaInformation) ).
	
	Note: This method will add the 8-byte prefix "UNICODE/0" to aParam before setting the tag value in the metadata.  It may only be used to set Unicode data.
	
	@param  aTag
		the tag id where the data is stored
	@param	aIfd
		the ifd section in which the tag is stored.
	@param aParam
		the value of the tag
		
		
	@return error code
		KErrNotSupported if called on a decoding module. 
		KErrNotSupported if the plugin does not support the specified tag.
		KErrArgument if the requested data type does not match with the tag.
	*/
	virtual TInt SetParam16(TUint aTag, TUint aIfd, HBufC16* aParam) = 0;

	/**
	Sets the data associated with a signed or unsigned 32-bit integer EXIF/DCF tag/IFD. 
	
	@param  aTag
		the tag id where the data is stored
	@param	aIfd
		the ifd section in which the tag is stored.
	@param aParam
		the value of the tag
		
	@return error code
		KErrNotSupported if called on a decoding module. 
		KErrNotSupported if the plugin does not support the specified tag.
		KErrArgument if the requested data type does not match with the tag.
	*/
	virtual TInt SetIntegerParam(TUint aTag, TUint aIfd, TInt aParam) = 0;

	/**
	Sets the data associated with an unsigned short (16-bit) EXIF/DCF tag/IFD. 
	
	@param  aTag
		the tag id where the data is stored
	@param	aIfd
		the ifd section in which the tag is stored.
	@param aParam
		the value of the tag
		
	@return error code
		KErrNotSupported if called on a decoding module. 
		KErrNotSupported if the plugin does not support the specified tag.
		KErrArgument if the requested data type does not match with the tag.
	*/
	virtual TInt SetShortParam(TUint aTag, TUint aIfd, TUint16 aParam) = 0;

	/**
	Sets the data associated with a signed or unsigned rational EXIF/DCF tag/IFD. 
	
	@param  aTag
		the tag id where the data is stored
	@param	aIfd
		the ifd section in which the tag is stored.
	@param aNumerator
		the numerator value of the rational tag
	@param aDenominator
		the denominator value of the rational tag
		
	@return error code
		KErrNotSupported if called on a decoding module. 
		KErrNotSupported if the plugin does not support the specified tag.
		KErrArgument if the requested data type does not match with the tag.
	*/
	virtual TInt SetRationalParam(TUint aTag, TUint aIfd, TInt aNumerator, TInt aDenominator) = 0;
	
	/**
	Sets the data associated with an array of signed or unsigned 32-bit integers EXIF/DCF tag/IFD. 
	
	@param  aTag
		the tag id where the data is stored
	@param	aIfd
		the ifd section in which the tag is stored.
	@param aParam
		the list of values value for the tag
		
	@return error code
		KErrNotSupported if called on a decoding module. 
		KErrNotSupported if the plugin does not support the specified tag.
		KErrArgument if the requested data type does not match with the tag.
	*/
	virtual TInt SetIntegerArrayParam(TUint aTag, TUint aIfd, CArrayFix<TInt>& aParam) = 0;

	/**
	Sets the data associated with an array of unsigned short (16-bit) EXIF/DCF tag/IFD. 
	
	@param  aTag
		the tag id where the data is stored
	@param	aIfd
		the ifd section in which the tag is stored.
	@param aParam
		the list of values value for the tag
		
	@return error code
		KErrNotSupported if called on a decoding module. 
		KErrNotSupported if the plugin does not support the specified tag.
		KErrArgument if the requested data type does not match with the tag.
	*/
	virtual TInt SetShortArrayParam(TUint aTag, TUint aIfd, CArrayFix<TUint16>& aParam) = 0;

	/**
	Sets the data associated with an array of signed or unsigned rationals EXIF/DCF tag/IFD. 
	
	@param  aTag
		the tag id where the data is stored
	@param	aIfd
		the ifd section in which the tag is stored.
	@param aParam
		the list of values value for the tag
		
	@return error code
		KErrNotSupported if called on a decoding module. 
		KErrNotSupported if the plugin does not support the specified tag.
		KErrArgument if the requested data type does not match with the tag.
	*/
	virtual TInt SetRationalArrayParam(TUint aTag, TUint aIfd, CArrayFix<TRational>& aParam) = 0;
	};


/**
@publishedAll
@released

generic accessor to access the tags from exif metadata.
The TExifWriterUtility & TExifReaderUtility classes offer friendlier interfaces to access these tags.
*/
class MExifMetadata: public MExifMetadataReader, public MExifMetadataWriter
	{
public:
	};

	
/**
@publishedAll
@released

Provides access to the exif jpeg decoder.

This class provides functions to decode jpeg images held in files or descriptors. 
*/
class CJPEGExifDecoder : public CImageDecoder
	{	
public:
	class CBody;
	friend class CBody;

	IMPORT_C static CJPEGExifDecoder* NewL();
	IMPORT_C ~CJPEGExifDecoder();

	IMPORT_C MExifMetadata* ExifMetadata();
		
protected:
	IMPORT_C CJPEGExifDecoder();
	IMPORT_C void ConstructL();
	
private:
	CBody* iBody;
	};

/**
@publishedAll
@released

Provides access to the exif jpeg encoder.

This class provides functions to encode jpeg images held in files or descriptors. 
*/
class CJPEGExifEncoder : public CImageEncoder
	{
public:
	class CBody;
	friend class CBody;

	IMPORT_C static CJPEGExifEncoder* NewL();
	IMPORT_C ~CJPEGExifEncoder();

	IMPORT_C MExifMetadata* ExifMetadata();

protected:
	IMPORT_C CJPEGExifEncoder();
	IMPORT_C void ConstructL();

private:
	CBody* iBody;
	};

/**
@publishedAll
@released

The plugin API for Image Converter Library EXIF decoder plugins. 
*/
class CJPEGExifDecoderPlugin : public CImageDecoderPlugin
	{
public:
	/**
	Returns the EXIF metadata associated with the image being decoded.
	This is a pure virtual function that each individual plugin must implement.

    @return A pointer to the metadata. NULL if there is no metadata available.
	*/
	IMPORT_C virtual MExifMetadata* ExifMetadata() = 0;	
	};

/**
@publishedAll
@released

The plugin API for Image Converter Library EXIF encoder plugins. 
*/
class CJPEGExifEncoderPlugin : public CImageEncoderPlugin
	{
public:
	/**
	Returns the EXIF metadata associated with the image being encoded.
	This is a pure virtual function that each individual plugin must implement.

	@return A pointer to the metadata. NULL if there is no metadata available.
	*/
	IMPORT_C virtual MExifMetadata* ExifMetadata() = 0;	
	};

/**
@publishedAll
@released

extension for exif Image Transform 

This class gives access to the exif metadata in a jpeg image during the transform operation

@see CImageTranform
*/
class CJPEGExifTransformExtension : public CImageTransformPluginExtension
	{
public:
	IMPORT_C virtual MExifMetadata* ExifMetadata();
	};

#endif // __CEXIFICL_H__

