/*
 ============================================================================
 Name		: CenRepObserver.cpp
 Author	  : Usanov-Kornilov Nikolay (aka Kolay)
 Version	 : 1.0
 Copyright   : 
 Contacts:
 kolayuk@mail.ru
 http://kolaysoft.ru

 (c) KolaySoft, 2010

 Description : CProcessMonitor implementation
 ============================================================================
 */
#include <e32debug.h>
#include <ProcessMonitor.h>

CProcessMonitor* CProcessMonitor::NewLC(TUid uid,MProcessCallBack& aCB)
	{
	CProcessMonitor* self = new (ELeave) CProcessMonitor(aCB);
	CleanupStack::PushL(self);
	self->ConstructL(uid);
	return self;
	}

CProcessMonitor* CProcessMonitor::NewL(TUid uid,MProcessCallBack& aCB)
	{
	CProcessMonitor* self = CProcessMonitor::NewLC(uid,aCB);
	CleanupStack::Pop(); // self;
	return self;
	}

//trivial NewL and NewLC have been omitted.
void CProcessMonitor::ConstructL(TUid uid)
	{
	CActiveScheduler::Add(this);
	iUid=uid;
	iTimer=CPeriodic::New(CActive::EPriorityLow);
	iCloseWaiter=CPeriodic::New(CActive::EPriorityLow);
	Start();
    }
CProcessMonitor::CProcessMonitor(MProcessCallBack& aObserver) : iObserver(aObserver), CActive (EPriorityHigh)
         {
         //do nothing
         }
CProcessMonitor::~CProcessMonitor()
         {
         Cancel();
         }
void CProcessMonitor::DoCancel()
          {
          iProc.RendezvousCancel(iStatus);
          iProc.Close();
          //  iRepository->NotifyCancelAll();
          }
void CProcessMonitor::RunL()
	{
	iProc.Close();
	iCloseWaiter->Start(1*1000*1000,1*1000*1000,TCallBack(Run,this));
	
	Start();
	//iProc.Rendezvous(iStatus);
	//SetActive();
    }

TInt CProcessMonitor::Tick(TAny* aObj)
	{
	CProcessMonitor* t=((CProcessMonitor*)aObj);
	TFileName res;
	TFindProcess find;
	TBool found=EFalse;
	while(find.Next(res) == KErrNone)
		{	
		t->iProc.Open(res);

		if(t->iProc.SecureId() == t->iUid.iUid)// SID of the process we are looking for
			{
			RDebug::Print(res);
			found=ETrue;
			break;
			}
		t->iProc.Close();
		}
	if (found){t->iProc.Rendezvous(t->iStatus);t->SetActive();RDebug::Print(_L("Started monitoring"));}
	else {RDebug::Print(_L("Proc not found!"));t->iObserver.StateChanged();return 1;}
	t->iTimer->Cancel();
	}
void CProcessMonitor::Start()
{
	iTimer->Start(10*1000*1000,10*1000*1000,TCallBack(Tick,this));
}
TInt CProcessMonitor::Run(TAny* aObj)
	{
	((CProcessMonitor*)aObj)->iObserver.StateChanged();
	((CProcessMonitor*)aObj)->iCloseWaiter->Cancel();
	}
