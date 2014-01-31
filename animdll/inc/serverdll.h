/*
* ==============================================================================
*  Name        : serverdll.h
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

#ifndef __SERVERDLL_H__
#define __SERVERDLL_H__

// INCLUDES
#include <w32adll.h>

// CLASS DECLARATION

/**
* CServerDll.
* An instance of CServerDll is a 'factory' object which creates a new
* instance of CAnim
*/
class CServerDll : public CAnimDll
    {
    public: // Constructor

        /**
        * CServerDll.
        * Construct an Animation Server dll
        */
        CServerDll();

        // Public destructor not created as this class does not own any data

    public: // From CAnimDll

        /**
        * CreateInstanceL.
        * Create an instance of the Animation Server image aType.
        * @param aType KAnimationSquare implies "construct a bouncing square"
        */
        IMPORT_C CAnim* CreateInstanceL( TInt aType );

    };

#endif // __SERVERDLL_H__

// End of File
