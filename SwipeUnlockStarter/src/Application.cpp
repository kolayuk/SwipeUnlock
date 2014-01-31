/*
 ============================================================================
 Name		: Application.cpp
 Author	  : Usanov-Kornilov Nikolay (aka Kolay)
 Version	 : 1.0
 Copyright   : 
 Contacts:
 kolayuk@mail.ru
 http://kolaysoft.ru

 (c) KolaySoft, 2011

 Description : CApplication implementation
 ============================================================================
 */

#include "Application.h"
#include <apacmdln.h>
#include <apgcli.h>

_LIT(KServer,"SwipeUnlockSrv.exe");

//0x2004423c - swipeunlock
// 0x20067b13 - jellyunlock
#define KServerUid 0x2004423c
CApplication::CApplication(): MProcessCallBack()
	{
	// No implementation required
	}

CApplication::~CApplication()
	{
	if (iMon) delete iMon;
	}

CApplication* CApplication::NewLC()
	{
	CApplication* self = new (ELeave) CApplication();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CApplication* CApplication::NewL()
	{
	CApplication* self = CApplication::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CApplication::ConstructL()
	{
	iMon=CProcessMonitor::NewL(TUid::Uid(KServerUid),*this);
	}
void CApplication::StateChanged()
	{
	RDebug::Print(_L("State changed"));
	RApaLsSession session;
	session.Connect();
	CApaCommandLine* cmdLine = CApaCommandLine::NewLC();
	cmdLine->SetExecutableNameL(KServer);
	cmdLine->SetCommandL(EApaCommandRun);
	cmdLine->SetCommandL(EApaCommandBackground);
	TInt err=session.StartApp(*cmdLine);
	RDebug::Print(_L("Err: %d"),err);
	CleanupStack::PopAndDestroy(cmdLine);
	session.Close();
	}
