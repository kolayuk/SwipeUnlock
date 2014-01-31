/*
* Copyright (c) 2007-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Provides Command line API to start LogsUI application 
*
*/

#ifndef LOGSUICMDSTARTER_H
#define LOGSUICMDSTARTER_H

#include <LogsUiCmdStarterConsts.h> 
#include <msvids.h>
#include <vwsdef.h>
const TUid KCRUidMuiuSettings = {0x101F87EB};
const TUint32 KMuiuMceDefaultView = 0x0000001C;
const TUid KMceShowMail  = { 0x01 };
const TUid KMCEAppUid = { 0x100058C5 };
const TUid KMCEMessageListViewUid = { 0x02 };
const TUid KMCEMainViewUid = { 0x01 };
const TUid KConversationAppUid = { 0x2002A540 };
const TUid KConversationListViewUid = { 0x01 };
const TMsvId KConversationListViewid = 0x01;
const TVwsViewId KMessagingCentreView( KMCEAppUid, KMCEMessageListViewUid  );
const TVwsViewId KMessagingCentreMainView( KMCEAppUid, KMCEMainViewUid  );
const TVwsViewId KConversationView( KConversationAppUid, KConversationListViewUid  );
const TUid KUidEmailUi = { 0x2001E277 };
const TUid KMailListId = { 0x00000002 };
const TVwsViewId KEmailView(KUidEmailUi,KMailListId);
const TUid KStartListWithFolderIdFromHomeScreen = { 3 };

namespace LogsUiCmdStarter
    {
    /**
     * Requests to start Logs application. If Logs is already running,
     * activates the requested view.
     *
     * @since S60 3.2
     * @param aView   The view to be activated in Logs. Constants are defined
     *                in LogsUiCmdStarterConsts.h
     */
    void CmdStartL( const TPtrC8 aView ); 
    
    /**
     * Requests to start Logs application. If Logs is already running,
     * activates the requested view.
     *
     * @since S60 3.2     
     * @param aView   The view to be activated in Logs. Constants are defined
     *                in LogsUiCmdStarterConsts.h
     *
     * @return        KErrNone when request submitted successfully. Otherwise  
     *                system wide error code.     
     */
    TInt CmdStart( const TPtrC8 aView );
    }

#include <LogsUiCmdStarter.inl> 

#endif  //LOGSUICMDSTARTER_H
