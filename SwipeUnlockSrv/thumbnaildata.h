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
* Description:  Thumbnail object
 *
*/


#ifndef THUMBNAILDATA_H
#define THUMBNAILDATA_H

#include <e32std.h>

class CFbsBitmap;

/**
 *  Thumbnail object.
 *
 *  @since S60 S60 v5.0
 */
NONSHARABLE_CLASS( MThumbnailData )
    {
public:

    /**
     * Get a pointer to a CFbsBitmap containing the thumbnail image. Ownership
     * of the object is not transferred (i.e. client must not delete the
     * pointer).
     *
     * @since S60 v5.0
     * @return Pointer to a bitmap representing the thumbnail or NULL if
     *         thumbnail pointer is not available or it has been detached.
     */
    virtual CFbsBitmap* Bitmap() = 0;

    /**
     * Get a pointer to a CFbsBitmap containing the thumbnail image. Ownership
     * of the object is transferred to the caller. Client must delete the
     * bitmap after it is done processing it.
     *
     * @since S60 v5.0
     * @return Pointer to a bitmap representing the thumbnail or NULL if
     *         thumbnail pointer is not available or it has been detached.
     *         Caller assumes ownership of the bitmap.
     */
    virtual CFbsBitmap* DetachBitmap() = 0;

    /**
     * Get client data structure.
     *
     * @since S60 v5.0
     * @return A pointer for client data specified as a parameter for
     *         GetThumbnailL() or NULL if not specified.
     */
    virtual TAny* ClientData() = 0;
};

#endif // THUMBNAILDATA_H
