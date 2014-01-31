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
* Description:  Provides constants for Logs Command line API to start LogsUI 
*                application 
*
*/

#ifndef LOGSUICMDSTARTERCONSTS_H
#define LOGSUICMDSTARTERCONSTS_H

namespace LogsUiCmdStarterConsts
    {
    _LIT8( KMissedView,         "missed");          //Logs missed calls view
    _LIT8( KDialledView,        "dialled");         //Logs dialled calls view
    _LIT8( KReceivedView,       "received");        //Logs received calls view
    _LIT8( KCountersView,       "counters");        //Logs main view  
    
    const TUid KLogsUID3    =   { 270486741 };      //101F4CD5
    }
    
#endif  //LOGSUICMDSTARTERCONSTS_H
