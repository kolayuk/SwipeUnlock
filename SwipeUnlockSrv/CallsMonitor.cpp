#include "CallsMonitor.h" 

CCallMonitor* CCallMonitor::NewLC(MCallCallBack& aObserver)
	{
	CCallMonitor* self = new (ELeave) CCallMonitor(aObserver);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}
CCallMonitor* CCallMonitor::NewL(MCallCallBack& aObserver)
	{
	CCallMonitor* self = CCallMonitor::NewLC(aObserver);
	CleanupStack::Pop(); // self;
	return self;
	}
CCallMonitor::CCallMonitor(MCallCallBack& aCallBack)
:CActive(EPriorityStandard),iCallBack(aCallBack),iCurrentStatusPckg(iCurrentStatus)
	{
	CActiveScheduler::Add(this);
	}
CCallMonitor::~CCallMonitor()
	{
	Cancel();
	delete iTelephony;
	}
void CCallMonitor::ConstructL(void)
	{
	iTelephony = CTelephony::NewL();
	StartListening();
	}
void CCallMonitor::CancelOperation(void)
	{
	Cancel();
	}
void CCallMonitor::DoCancel()
	{
	iTelephony->CancelAsync(CTelephony::EVoiceLineStatusChangeCancel);
	}
void CCallMonitor::RunL()
	{
	iCallBack.CallStatusChangedL(iCurrentStatus.iStatus,iStatus.Int());
	if(iStatus != KErrCancel)
		StartListening();
	}
void CCallMonitor::StartListening()
	{
	Cancel();
	iCurrentStatus.iStatus = CTelephony::EStatusUnknown;
	iTelephony->NotifyChange(iStatus,CTelephony::EVoiceLineStatusChange,iCurrentStatusPckg);
	SetActive();
	}
