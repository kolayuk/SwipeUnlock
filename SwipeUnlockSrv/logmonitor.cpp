#include "logmonitor.h"
#include <logwraplimits.h>
#include <QDebug>
#include <logcli.h>
#include <logview.h>
#include <logwrap.hrh>
CLogMonitor* CLogMonitor::NewL(MLogMonitor* aCallBack)
{
    CLogMonitor* self = CLogMonitor::NewLC(aCallBack);
    CleanupStack::Pop(self);
    return self;
}

CLogMonitor* CLogMonitor::NewLC(MLogMonitor* aCallBack)
{
    CLogMonitor* self = new (ELeave) CLogMonitor(aCallBack);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
}

CLogMonitor::CLogMonitor(MLogMonitor* aCallBack)
:CActive(0),iState(EUninitalised),iCallBack(aCallBack)
{
}

CLogMonitor::~CLogMonitor()
{
    Cancel();

    delete iRecentLogView, iRecentLogView = NULL;
    delete iLogClient, iLogClient = NULL;

    iFsSession.Close();
}

void CLogMonitor::ConstructL()
{
    CActiveScheduler::Add(this);

    User::LeaveIfError(iFsSession.Connect());

    iLogClient = CLogClient::NewL(iFsSession);
    iRecentLogView = CLogViewRecent::NewL(*iLogClient);
    //iRecentLogView->SetRecentListL(KLogNullRecentList,iStatus);
    StartMonitorL();
    //iState = EWaitingChange;
    //SetActive();
    //iState = EInitalised;
    //StartMonitorL();
    iLastTime.UniversalTime();
}

void CLogMonitor::DoCancel()
{
    if(iRecentLogView)
        iRecentLogView->Cancel();

    if(iLogClient)
    {
        if(iState == EWaitingChange)
            iLogClient->NotifyChangeCancel();
        else
            iLogClient->Cancel();
    }
}

void CLogMonitor::RunL()
{
    if(iStatus != KErrCancel)
        switch(iState)
        {
            case EWaitingChange:

                // if this doesn't appear to catch the event right
                // you could try sleeping a bit before fetching the event...
                // User::After(2000000);
                GetLatest();
                break;

            case EReadingLog:
                if(iRecentLogView)
                {
                    if(iRecentLogView->CountL() > 0)
                        GetFirstEventL();
                    else
                        StartMonitorL();
                }
                break;

            case EReadingFirstLog:
            case EReadingLogItems:
                if(iStatus == KErrNone && iRecentLogView)
                {
                    TLogFlags iFlags = iRecentLogView->Event().Flags();
                    if( !( iFlags & KLogEventRead ) )
                    {
                        const CLogEvent& ev=iRecentLogView->Event();
                        TTimeIntervalSeconds secs;
                        ev.Time().SecondsFrom(iLastTime,secs);
                        iLastTime=iRecentLogView->Event().Time();
                        qDebug()<<"secs"<<secs.Int();
                        if (abs(secs.Int())>0) iCallBack->LogEventL(ev);
                    }
                    //GetNextEventL();
                    StartMonitorL();
                }
                else
                    StartMonitorL();
                break;

            case EDeletingEvent:
                GetNextEventL();
                break;

            default:
                StartMonitorL();
                break;
        }
}


void CLogMonitor::StartMonitorL()
{
    if(iLogClient)
    {
        if(iRecentLogView)
            iRecentLogView->Cancel();

        iLogClient->Cancel();

        iState = EWaitingChange;
        iLogClient->NotifyChange(TTimeIntervalMicroSeconds32(10),iStatus);
        SetActive();
    }
}

void CLogMonitor::GetLatest()
{
    if(iRecentLogView)
    {
        iState = EReadingLog;
        iRecentLogView->Cancel();
        if(iRecentLogView->SetRecentListL(KLogRecentMissedCalls,iStatus))
            SetActive();
        else
            StartMonitorL();
    }
}

void CLogMonitor::GetFirstEventL()
{
    iRecentLogView->Cancel();
    if(iRecentLogView)
    {
        iState = EReadingFirstLog;
        if(iRecentLogView->FirstL(iStatus)){
            SetActive();

            }
        else{
            StartMonitorL();
            }
    }
}


void CLogMonitor::GetNextEventL()
{
    if(iRecentLogView)
    {
        iState = EReadingLogItems;
        if(iRecentLogView->PreviousL(iStatus))
            SetActive();
        else
            StartMonitorL();
     }
}
