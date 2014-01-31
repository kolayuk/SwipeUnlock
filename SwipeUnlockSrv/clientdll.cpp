/*
* ==============================================================================
*  Name        : clientdll.cpp
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
#include "clientdll.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// RClientDll::RClientDll()
// Animation client dll construction code all encapsulated in original class.
// -----------------------------------------------------------------------------
//
EXPORT_C RClientDll::RClientDll( RWsSession& aSession )
    : RAnimDll( aSession )
    {
    }

// ========================== OTHER EXPORTED FUNCTIONS =========================

// End of File
