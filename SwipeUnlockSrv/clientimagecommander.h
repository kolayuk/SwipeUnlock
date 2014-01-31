/*
* ==============================================================================
*  Name        : clientimagecommander.h
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

#ifndef __CLIENTIMAGE_COMMANDER_H__
#define __CLIENTIMAGE_COMMANDER_H__

// INCLUDES
#include <w32adll.h>

// CLASS DECLARATION

/**
* RImageCommander
* An instance of RImageCommander is an Animation Client Commander which
* sends commands to the Animation Server
*/
class RImageCommander : public RAnim
    {
    public: // Constructors

        /**
        * RImageCommander.
        * Construct an Animation Client object for Animation Client DLL aAnimDll
        * @param aAnimDll the Animation Client DLL to use
        */
        IMPORT_C RImageCommander( RAnimDll& aAnimDll );

        /**
        * ImageConstruct.
        * Complete Animation Client construction
        * @param aDevice the window device
        * @param aType KAnimationSquare implies "Construct a bouncing square"
        * @param aParams parameters to pass to the server side to tell it how to
        * construct or initialise itself.
        */
        IMPORT_C void ImageConstruct( const RWindowBase& aDevice, TInt aType,
                                                        const TDesC8& aParams );

    public: // New functions

        /**
        * ImageCommand.
        * Send aCommand to the Animation Server object;
        * aCommand == KAnimationReset implies "reset the animation".
        * Note! Because there is no way to return an error from the server side
        * using this method, it is important that any server side code for these
        * commands should not be able to fail or leave.
        * This command is also buffered and may not be performed immediately.
        * @param aCommand the enumerated code for the option selected
        */
        IMPORT_C void ImageCommand( TInt aCommand );

    public: // Enumerations

        /**
        * KAnimationTypes.
        * Constant used to indicate the animation of a bouncing square should
        * be created, enumeration can be expanded
        */
        enum KAnimationTypes
            {
            KAnimationSquare = 1
            };

        /**
        * KAnimationCommands.
        * Constant used to request a reset of the bouncing square,
        * enumeration can be expanded
        */
        enum KAnimationCommands
            {
            KAnimationReset  = 1,
            KResolutionChange = 2
            };
    };

#endif // __CLIENTIMAGE_COMMANDER_H__

// End of File
