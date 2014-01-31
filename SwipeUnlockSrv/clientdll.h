/*
* ==============================================================================
*  Name        : clientdll.h
*  Part of     : Animation example
*  Interface   :
*  Description :
*  Version     :
*
*  Copyright (c) 2004 - 2006 Nokia Corporation.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia Corporation.
* ==============================================================================
*/

#ifndef __CLIENT_DLL_H__
#define __CLIENT_DLL_H__

// INCLUDES
#include <w32adll.h>

// CLASS DECLARATION

/**
* RClientDll.
* An instance of RClientDll is an Animation Client DLL, used to load
* and destroy the Animation Server
*/
class RClientDll : public RAnimDll
    {
    public:

        /**
        * RClientDll.
        * Construct an Animation Client DLL object for use with the
        * aSession window server session.
        * @param aSession the window server session to use
        */
        IMPORT_C RClientDll( RWsSession& aSession );
    };

#endif //__CLIENT_DLL_H__

// End of File
