// Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef IMAGEFRAMECONST_H
#define IMAGEFRAMECONST_H


#include <imageframeformats.hrh>
#include <imageframeconst.hrh>


/** 
Constant which defines the maximum number of planes within TFrameLayout. 
*/
const TInt KMaxPlanesInFrame = 4;

/** 
Identifier for TFrameFormat type. 
 @see KIclImageFrameFormatUidValue
*/ 
static const TUid KUidIclImageFrameFormat   = {KIclImageFrameFormatUidValue};

/** 
Identifier for TFrameLayout type.
 @see KIclImageFrameLayoutUidValue
*/ 
static const TUid KUidIclImageFrameLayout	= {KIclImageFrameLayoutUidValue};


/* Format Uids */

/** 
    TFrameFormat format code.
    
    Format Description:
    YUV Monochrome image format.
    Planar, 8 bit per pixel. 
    Single Y plane for monochrome images.
    Pixel order: Y00Y01..
    @note greyscale values, 0=black, 255=white.

    Equivalent to ECam format code CCamera::EFormatMonochrome.
    
    Equivalent to Video FourCC code Y800, Y8.
    
    @see CCamera::TFormat
    @see KFormatYUVMonochromeUidValue
*/
const TUid KUidFormatYUVMonochrome = {KFormatYUVMonochromeUidValue};

/** 
    TFrameFormat format code.
    
    Format Description:
    YUV 4:2:2 image format. 
    Interleaved, 16 bits per pixel, 8 bits per sample.
    Pixel order: UY0VY1.

    Equivalent to ECam format code CCamera::EFormatYUV422.
    
    Equivalent to Video FourCC code UYVY.
    
    @see CCamera::TFormat
    @see KFormatYUV422InterleavedUidValue  
*/
const TUid KUidFormatYUV422Interleaved = {KFormatYUV422InterleavedUidValue};

/** 
    TFrameFormat format code.
    
    Format Description:
	YUV 4:2:0 image format.
    Planar, 12 bits per pixel.
    8 bit Y plane followed by 8 bit 2x2 subsampled U and V planes.
    Pixel order: Y00Y01Y02Y03...U0...V0...
    
    Equivalent to ECam format code CCamera::EFormatYUV420Planar.
    
    Equivalent to Video FourCC code I420.
    
    @see CCamera::TFormat
    @see KFormatYUV420PlanarUidValue  
*/
const TUid KUidFormatYUV420Planar 		= {KFormatYUV420PlanarUidValue};

/**     
	TFrameFormat format code.
	
	Format Description:
	YUV 4:2:0 image format.
    Planar, 12 bits per pixel.
    8 bit Y plane followed by 8 bit 2x2 subsampled V and U planes.
    Pixel order: Y00Y01Y02Y03...V0...U0...
    
    No equivalent ECam format code.
    
    Equivalent to Video FourCC code YV12.
    
    @see CCamera::TFormat
    @see KFormatYUV420InterleavedUidValue  
*/
const TUid KUidFormatYUV420PlanarReversed = {KFormatYUV420PlanarReversedUidValue};

/** 
	TFrameFormat format code.
	
	Format Description:
	RGB Packed image format. 
    Interleaved in triplets, 12 bits per pixel.
    Pixel order: BGR - 4 bits per pixel with red in the least significant bits
    and the 4 most significant bits unused. 

    Equivalent to ECam format code CCamera::EFormat16bitRGB444.
    
    No equivalent Video FourCC code.
    
    @see CCamera::TFormat
    @see KFormat16bitRGB444InterleavedUidValue      
*/
const TUid KUidFormat16bitRGB444Interleaved = {KFormat16bitRGB444InterleavedUidValue};

/** 
	TFrameFormat format code.
	
	Format Description:
	RGB Packed image format. 
    Interleaved in triplets, 16 bits per pixel. 
    Pixel order: BGR - 5 bits per pixel for red and blue and 6 bits for green,
    with red in the least significant bits.
	 
    Equivalent to ECam format code  CCamera::EFormat16bitRGB565.
    
    No equivalent Video FourCC code.
    
    @see CCamera::TFormat     
    @see KFormat16BitRGB565InterleavedUidValue      
*/
const TUid KUidFormat16BitRGB565Interleaved = {KFormat16BitRGB565InterleavedUidValue};

/** 
	TFrameFormat format code.
	
	Format Description:
	RGB Packed image format. 
    Interleaved in triplets, 32 bits per pixel. 
    Pixel order: BGR - 8 bits per pixel with red in the least significant bits
    and the 8 most significant bits unused. 
    
    Equivalent to ECam format code CCamera::EFormat32BitRGB888.
    
    No equivalent Video FourCC code. 
    
    @see CCamera::TFormat 
    @see KFormat32BitRGB888InterleavedUidValue          
*/
const TUid KUidFormat32BitRGB888Interleaved = {KFormat32BitRGB888InterleavedUidValue};

/** 
	TFrameFormat format code.
	
	Format Description:
	YUV 4:2:0 image format.
    Interleaved, 12 bits per pixel. 
    8 bit, 4 Y plane samples  followed by 2 8 bit U and V samples.
    Pixel order: Y00Y01Y10Y11UV. 
    
    Equivalent to ECam format code 	CCamera::EFormatYUV420Interleaved.
    
    No equivalent Video FourCC code.  
      
    @see CCamera::TFormat
    @see KFormatYUV420InterleavedUidValue    
*/
const TUid KUidFormatYUV420Interleaved 		= {KFormatYUV420InterleavedUidValue};

/** 
	TFrameFormat format code.

	Format Description:
	YUV 4:2:2 image format. 
    Interleaved, 16 bits per pixel, 8 bits per sample.
    Pixel order: Y1VY0U.

    Equivalent to ECam format code CCamera::EFormatYUV422Reversed.
    
    No equivalent Video FourCC code.
    
    @see CCamera::TFormat
    @see KFormatYUV422InterleavedReversedUidValue
*/
const TUid KUidFormatYUV422InterleavedReversed = {KFormatYUV422InterleavedReversedUidValue};

/** 
	TFrameFormat format code.

	Format Description:
	YUV 4:2:2 image format. 
    Interleaved, 16 bits per pixel, 8 bits per sample.
    Pixel order: Y0Y1UV.

    No equivalent ECam format code.
    
    No equivalent Video FourCC code.
    
    @see CCamera::TFormat
    @see KFormatYYUV422InterleavedUidValue
*/
const TUid KUidFormatYYUV422Interleaved = {KFormatYYUV422InterleavedUidValue};

/** 
	TFrameFormat format code.

	Format Description:
	YUV 4:2:2 image format. 
    Planar, 16 bits per pixel, 8 bits per sample.
    Pixel order: Y00Y01Y02Y03...U00U02...V00V02...

    No equivalent ECam format code.
    
    No equivalent Video FourCC code.
    
    @see CCamera::TFormat
    @see KFormatYUV422PlanarUidValue
*/
const TUid KUidFormatYUV422Planar = {KFormatYUV422PlanarUidValue};

/** 
	TFrameFormat format code.

	Format Description:
	YUV 4:4:4 image format. 
    Planar, 24 bits per pixel, 8 bits per sample.
    Pixel order: Y00Y01Y02Y03...U00U01U02U03...V00V01V02V03...

    No equivalent ECam format code.
    
    No equivalent Video FourCC code.
    
    @see CCamera::TFormat
    @see KFormatYUV444PlanarUidValue
*/
const TUid KUidFormatYUV444Planar = {KFormatYUV444PlanarUidValue};

/** 
	TFrameFormat format code.
	
	Format Description:
	YUV 4:4:4 image format.
    Interleaved, 24 bit per pixel, 8 bits per sample.
    Pixel order: Y00U00V00 Y01U01V01... 
	
    Equivalent to ECam format code CCamera::EFormatYUV444.
    
    No equivalent Video FourCC code. 
    
    @see CCamera::TFormat
    @see KFormatYUV444InterleavedUidValue    
*/
const TUid KUidFormatYUV444Interleaved 		= {KFormatYUV444InterleavedUidValue};

/** 
	TFrameFormat format code.
	
	Format Description:
	YUV 4:2:0 image format.
    Semiplanar, 12 bits per pixel, 8-bit per sample. 
    Y plane followed by an interleaved U/V plane with 2x2 subsampling.
    Pixel order: Y00Y01Y02Y03...U0V0...
    
    Equivalent to ECam format code 	CCamera::EFormatYUV420SemiPlanar.
    
    Equivalent to Video FourCC code 	NV12. 
    
    @see CCamera::TFormat    
    @see KFormatYUV420SemiPlanarUidValue    
*/
const TUid KUidFormatYUV420SemiPlanar 		= {KFormatYUV420SemiPlanarUidValue};


/* Colour spaces */

/** 
TFrameFormat image frame color space for YCbCr.
 @see KColourSpaceYCbCrUidValue
*/
const TUid KUidColourSpaceYCbCr = {KColourSpaceYCbCrUidValue};

/** 
TFrameFormat image frame color space for YUV.
 @see KColourSpaceYUVUidValue
*/
const TUid KUidColourSpaceYUV = {KColourSpaceYUVUidValue};

/** 
TFrameFormat image frame color space for RGB.
 @see KColourSpaceRGBUidValue
*/
const TUid KUidColourSpaceRGB = {KColourSpaceRGBUidValue};


/* Sampling */

/** 
TFrameFormat frame sampling for monochrome image data.
 @see KSamplingMonochromeUidValue
*/
const TUid KUidSamplingMonochrome = {KSamplingMonochromeUidValue};

/** 
TFrameFormat frame sampling for YUV444 image data.
 @see KSamplingColor444UidValue
*/
const TUid KUidSamplingColor444 = {KSamplingColor444UidValue};

/** 
TFrameFormat frame sampling for YUV422 image data.
 @see KSamplingColor422UidValue
*/
const TUid KUidSamplingColor422 = {KSamplingColor422UidValue};

/** 
TFrameFormat frame sampling for YUV420 image data.
 @see KSamplingColor420UidValue
*/
const TUid KUidSamplingColor420 = {KSamplingColor420UidValue};

/** 
TFrameFormat frame sampling for YUV411 image data.
 @see KSamplingColor411UidValue
*/
const TUid KUidSamplingColor411 = {KSamplingColor411UidValue};


/** 
Specific JPEG ImageFrame Decoder/Encoder option for the ConvertFrame API.
 @see KOptionConvertFrameUidValue
*/
const TUid KUidOptionConvertFrame = {KOptionConvertFrameUidValue};

/** 
Specific JPEG ImageFrame Decoder option for the RecommendBufferSize API.
This option allows the client of the decoder to obtain the recommended size for a ImageFrame 
and allocate memory accordingly.
 @see KRecommendBufferSizeUidValue
*/
const TUid KUidOptionRecommendBufferSize = {KOptionRecommendBufferSizeUidValue};

#endif // IMAGEFRAMECONST_H
