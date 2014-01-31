/*
* ==============================================================================
*  Name        : clientimagecommander.cpp
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
#include "clientimagecommander.h"
#include <e32property.h>
#include <const.h>
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// RImageCommander::RImageCommander()
// Create a new animation object.
// -----------------------------------------------------------------------------
//
EXPORT_C RImageCommander::RImageCommander( RAnimDll &aAnimDll ) :
                                                              RAnim( aAnimDll )
    {
    // No implementation required
    }

// -----------------------------------------------------------------------------
// RImageCommander::ImageConstruct()
// Construct a new animation object.
// -----------------------------------------------------------------------------
//
EXPORT_C void RImageCommander::ImageConstruct( const RWindowBase& aDevice,
                                             TInt aType, const TDesC8& aParams )
    {
    // Send the parameters to the animation server object construction
    RAnim::Construct( aDevice, aType, aParams );
    }

// -----------------------------------------------------------------------------
// RImageCommander::ImageCommand()
// Send a command (aCommand) to the animation server object.
// Because there is no way to return an error from the server side using this
// method, it is important that any server side code for these commands should
// not be able to fail or leave.  If the operation can fail, then the method
// TInt CommandReply(TInt aOpcode) should be used instead
// -----------------------------------------------------------------------------
//
EXPORT_C void RImageCommander::ImageCommand( TInt aCommand )
    {
    // Could optionally decode the commands here
    RDebug::Print(_L("Sending: %d"),aCommand);
    RProperty::Set(TUid::Uid(KPropertyUid),0x200,aCommand);
    //RAnim::Command( aCommand );
    }

// End of File
