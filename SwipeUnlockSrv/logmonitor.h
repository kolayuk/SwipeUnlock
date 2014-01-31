#ifndef LOGMONITOR_H
#define LOGMONITOR_H

#include <logcli.h>
#include <logview.h>

#define KLogRecentIncomingCalls 1
#define KLogRecentOutgoingCalls 2
#define KLogRecentMissedCalls 3

class MLogMonitor
{
    public:
        virtual void LogEventL(const CLogEvent& event) = 0;
};

class CLogMonitor : public CActive
{
    enum TMonitorStates
    {
        EUninitalised,
        EInitalised,
        EWaitingChange,
        EReadingLog,
        EReadingFirstLog,
        EDeletingEvent,
        EReadingLogItems
    };
    TTime iLastTime;
    public:
        static CLogMonitor* NewL(MLogMonitor* aCallBack);
        static CLogMonitor* NewLC(MLogMonitor* aCallBack);
        ~CLogMonitor();

    protected:
        CLogMonitor(MLogMonitor* aCallBack);
        void ConstructL(void);
        void StartMonitorL();
        void GetLatest();
        void GetFirstEventL();
        void GetNextEventL();
        void DoCancel();
        void RunL();

    private:
        CLogClient*     iLogClient;
        CLogViewRecent* iRecentLogView;
        TMonitorStates  iState;
        MLogMonitor*    iCallBack;
        RFs             iFsSession;
};

#endif // LOGMONITOR_H
