/*
* ==============================================================================
*  Name        : serverdll.cpp
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

// INCLUDE FILES
#include "serverdll.h"
#include "serverimage.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CServerDll::CServerDll()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CServerDll::CServerDll()
    : CAnimDll()
    {
    // No implementation required
    }

// -----------------------------------------------------------------------------
// CServerDll::CreateInstanceL()
// Used to create an instance of animation server object.
// -----------------------------------------------------------------------------
//
CAnim* CServerDll::CreateInstanceL( TInt /* aType */ )
    {
    // The aType variable can be used to set what type of animation object
    // should be created but this example only has 1 type so it is ignored.
    return ( new ( ELeave ) CImage );
    }

// ========================== OTHER EXPORTED FUNCTIONS =========================

// -----------------------------------------------------------------------------
// CreateCAnimDllL()
// Create instance of the animation server dll. Called by windows server
// framework
// -----------------------------------------------------------------------------
//
EXPORT_C CAnimDll* CreateCAnimDllL()
    {
    return ( new ( ELeave ) CServerDll );
    }

// End of File
