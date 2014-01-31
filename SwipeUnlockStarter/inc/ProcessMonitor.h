#include <e32base.h>

class MProcessCallBack
       {
       public:
               virtual void StateChanged() = 0;
        };


class CProcessMonitor : public CActive
       {
       public:
               static CProcessMonitor* NewL(TUid uid, MProcessCallBack& aObserver);
               static CProcessMonitor* NewLC(TUid uid,MProcessCallBack& aObserver);
                virtual ~CProcessMonitor();
                void RunL();
                void RunErrorL(TInt aError);
                void DoCancel();
                CProcessMonitor(MProcessCallBack& aObserver);
                void ConstructL(TUid uid);
                RProcess iProc;
                CPeriodic* iTimer;
                static TInt Tick(TAny* aObj);
                void Start();
                TUid iUid;
                CPeriodic* iCloseWaiter;
                static TInt Run(TAny* aObj);
       private:
              MProcessCallBack& iObserver;
        };
