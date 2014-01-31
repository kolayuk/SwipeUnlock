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
// This feature is documented in ICL_Design_EXIF.doc
// 
//

/**
 @file
 @publishedAll
 @released
*/

#ifndef ICLEXIFIMAGEFRAME_H
#define ICLEXIFIMAGEFRAME_H

#include <imageconversion.h>
#include <icl/imageplugin.h>
#include <iclexif.h>
#include "imageframe.h"


/**
This class provides access to an extension of the EXIF JPEG decoder that supports
decoding of JPEG images held either in files or in descriptors to a destination of type CImageFrame.

This is an addition to the features provided by CJPEGExifDecoder.
*/

class CJPEGImageFrameDecoder : public CJPEGExifDecoder
	{
public:
	IMPORT_C static CJPEGImageFrameDecoder* NewL();
	IMPORT_C ~CJPEGImageFrameDecoder();

	IMPORT_C void ConvertFrame(TRequestStatus* aRequestStatus, CImageFrame& aDestFrame);
	IMPORT_C void ConvertFrame(TRequestStatus* aRequestStatus, CImageFrame& aDestFrame, TInt aFrameNumber);
	IMPORT_C void ContinueConvertFrame(TRequestStatus* aRequestStatus);

	IMPORT_C TBool RecommendedBufferSize(TUid aFormatCode, TInt& bufferSize);
	IMPORT_C TBool RecommendedBufferSize(TInt& bufferSize);

protected:
	IMPORT_C CJPEGImageFrameDecoder();
	};

/**
This class provides access to an extension of the EXIF JPEG encoder that supports
encoding JPEG images from a source of type CImageFrame to either a file or a descriptor. 

This is an addition to the features provided by CJPEGExifEncoder.
*/

class CJPEGImageFrameEncoder : public CJPEGExifEncoder
	{
public:
	IMPORT_C static CJPEGImageFrameEncoder* NewL();
	IMPORT_C ~CJPEGImageFrameEncoder();

	IMPORT_C void ConvertFrame(TRequestStatus* aRequestStatus, const CImageFrame& aSrcFrame);
	IMPORT_C void ConvertFrame(TRequestStatus* aRequestStatus, const CImageFrame& aSrcFrame, const CFrameImageData* aFrameImageData);

protected:
	IMPORT_C CJPEGImageFrameEncoder();
	};
	

/**
This is the plugin API for Image Converter Library decoder plugins relating to CImageFrames.

It is an extension of the ICL EXIF decoder plugin which provides a container for specific
data required to decode a JPEG file or descriptor to a destination of type CImageFrame.
*/
class CJPEGImageFrameDecoderPlugin : public CJPEGExifDecoderPlugin
	{
public:
	IMPORT_C ~CJPEGImageFrameDecoderPlugin();
	IMPORT_C CImageFrame& DstImageFrame();
	IMPORT_C TInt FrameNumber() const;
	IMPORT_C TUid FormatCode() const;
	IMPORT_C void SetRecommendedBufferSize(TInt aBufferSize);

	void SetConvertParameters(CImageFrame& aDestFrame, TInt aFrameNumber);
	void SetFormatCode(TUid aFormatCode);
	TInt RecommendedBufferSize();

protected:
	IMPORT_C CJPEGImageFrameDecoderPlugin();

private:
	// reserved for future expansion
	IMPORT_C virtual void Reserved1();
	IMPORT_C virtual void Reserved2();
	IMPORT_C virtual void Reserved3();
	
private:
	CImageFrame* iDstImageFrame;
	TInt iFrameNumber;
	TUid iFormatCode;		
	TInt iRecommendedBufferSize;

	TAny* iReserved;
	};

/**
This is the plugin API for Image Converter Library encoder plugins relating to CImageFrames. 

It is an extension of the ICL EXIF encoder plugin which provides a container for specific
data required to encode image data from a source of type CImageFrame to a JPEG file or descriptor.
*/
class CJPEGImageFrameEncoderPlugin : public CJPEGExifEncoderPlugin
	{
public:
	IMPORT_C ~CJPEGImageFrameEncoderPlugin();
	IMPORT_C const CImageFrame& SrcImageFrame() const;
	IMPORT_C const CFrameImageData& FrameImageData() const;

	void SetConvertParameters(const CImageFrame& aSrcFrame, const CFrameImageData* aFrameImageData);

protected:
	IMPORT_C CJPEGImageFrameEncoderPlugin();

private:
	// reserved for future expansion
	IMPORT_C virtual void Reserved1();
	IMPORT_C virtual void Reserved2();
	IMPORT_C virtual void Reserved3();
		
private:
	const CImageFrame* iSrcImageFrame;
	const CFrameImageData* iFrameImageData;

	TAny* iReserved;
	};

#endif // ICLEXIFIMAGEFRAME_H
