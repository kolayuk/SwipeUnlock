#include "operatorobserver.h"

COperatorObserver* COperatorObserver::NewL(MOperatorObserver* aObserver)
    {
    COperatorObserver* self = NewLC(aObserver);
    CleanupStack::Pop(self);
    return self;
    }


COperatorObserver* COperatorObserver::NewLC(MOperatorObserver* aObserver)
    {
    COperatorObserver* self = new (ELeave) COperatorObserver(aObserver);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }


COperatorObserver::COperatorObserver(MOperatorObserver* aObserver)
:CActive(0),iObserver(aObserver),iOperatorNameV1Pckg(iOperatorNameV1)
{
}

COperatorObserver::~COperatorObserver()
{
    Cancel();
    delete iTelephony;
}

void COperatorObserver::GetOperator()
{
    if (IsActive())Cancel();
    iTelephony->GetOperatorName(iStatus,iOperatorNameV1Pckg);
    SetActive();
}

void COperatorObserver::ConstructL(void)
{
    CActiveScheduler::Add(this);

    iTelephony = CTelephony::NewL();
    iTelephony->GetOperatorName(iStatus,iOperatorNameV1Pckg);

    SetActive();
}

void COperatorObserver::DoCancel()
{
    iTelephony->CancelAsync(CTelephony::EGetOperatorNameCancel);
}


void COperatorObserver::RunL()
{
    iObserver->GetOperatorName(iOperatorNameV1.iOperatorName,iStatus.Int());
}
