/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description: 
*     Provides implementation of interface to start Logs application 
*
*/

#ifndef LOGSUICMDSTARTER_INL
#define LOGSUICMDSTARTER_INL

//  INCLUDES
#include <apgtask.h>
#include <apgcli.h>
#include <apacmdln.h>
#include <eikenv.h>

// --------------------------------------------------------------------------
// LogsUiCmdStarter::CmdStart
// --------------------------------------------------------------------------
//
inline TInt LogsUiCmdStarter::CmdStart( const TPtrC8 aView )
    {
    TInt err( KErrNone );
    TRAP(err, LogsUiCmdStarter::CmdStartL( aView ));
    return err;
    }


// --------------------------------------------------------------------------
// LogsUiCmdStarter::CmdStartL
// --------------------------------------------------------------------------
//

inline void LogsUiCmdStarter::CmdStartL( const TPtrC8 aView )
    {
    /***********************************************
    FIXME: Replaced by code below. Remove this code when sure that new code 
           works better than this with the new ui effects implementation.
    TApaTaskList taskList( CCoeEnv::Static()->WsSession() );
    TApaTask task = taskList.FindApp( LogsUiCmdStarterConsts::KLogsUID3 );
    TPtrC8 msg;
    msg.Set( aView );
    
    if( task.Exists() ) //Logs already open. Request it to
        {               //activate the correct view
        const TUid dummyUID = { 0x0 };
        task.SendMessage( dummyUID, msg );
        task.BringToForeground();  
        }
    else                //Start Logs and request it to activate
        {               //the correct view
        TApaAppInfo appInfo;
        RApaLsSession lsSession;
        User::LeaveIfError( lsSession.Connect() );        
        CleanupClosePushL( lsSession );
        
        if( lsSession.GetAppInfo( appInfo, LogsUiCmdStarterConsts::KLogsUID3 ) == KErrNone )
            {
            CApaCommandLine* cmdLine = CApaCommandLine::NewLC();
            cmdLine->SetExecutableNameL( appInfo.iFullName );
            cmdLine->SetCommandL( EApaCommandRun );
            cmdLine->SetTailEndL( msg );

            lsSession.StartApp( *cmdLine );
            CleanupStack::PopAndDestroy( cmdLine );
            }

        CleanupStack::PopAndDestroy();  // lsSession
        }
    ***********************************************/        

    TPtrC8 msg;
    msg.Set( aView );

    // Check that Logs application exists
    TApaAppInfo appInfo;
    RApaLsSession lsSession;
    User::LeaveIfError( lsSession.Connect() );        
    CleanupClosePushL( lsSession );
    User::LeaveIfError( lsSession.GetAppInfo( appInfo, LogsUiCmdStarterConsts::KLogsUID3 ) );

    // Create command line for starting Logs
    CApaCommandLine* cmdLine = CApaCommandLine::NewLC();
    cmdLine->SetExecutableNameL( appInfo.iFullName );
    cmdLine->SetCommandL( EApaCommandRun );

    // Check if Logs is already running
    TApaTaskList taskList( CCoeEnv::Static()->WsSession() );
    TApaTask task = taskList.FindApp( LogsUiCmdStarterConsts::KLogsUID3 );

    if( task.Exists() )
        {
        // Logs already running. Request it to activate the correct view
        const TUid dummyUID = { 0x0 };
        task.SendMessage( dummyUID, msg );
        
        // The below is just to secure an unlikely case that StartApp() would in future anyhow 
        // send command line parameter to application that is already running (currently
        // it doesn't). The "dontactivate" just prevents double attempt of activation of
        // view requested in msg SendMessage'd to Logs.
        _LIT8(dontActivate, "dontactivate");
        TPtrC8 dontActivateMsg = dontActivate(); 
        cmdLine->SetTailEndL( dontActivateMsg );  
        }
    else                
        {
        // Logs not yet running. Request it to activate the correct view
        cmdLine->SetTailEndL( msg );  
       	// Start Logs 
    	lsSession.StartApp( *cmdLine );
        }
  
    CleanupStack::PopAndDestroy( cmdLine );
    CleanupStack::PopAndDestroy();  //lsSession 
    }

#endif  //LOGSUICMDSTARTER_INL
