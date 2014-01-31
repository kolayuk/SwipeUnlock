#ifndef __CALLMONITOR_H__
#define __CALLMONITOR_H__

#include <Etel3rdParty.h> 
class MCallCallBack
	{
	public:
		virtual void CallStatusChangedL(CTelephony::TCallStatus& aStatus, TInt aError)=0;
	};

class CCallMonitor : public CActive
	{
	public:
		~CCallMonitor();
		static CCallMonitor* NewLC(MCallCallBack& aObserver);
		static CCallMonitor* NewL(MCallCallBack& aObserver);
	private:
		CCallMonitor(MCallCallBack& aCallBack);
		void ConstructL();
	protected:
		void DoCancel();
		void RunL();
	private:
		void CancelOperation(void);
		void StartListening();
	private:
		MCallCallBack&                iCallBack;
		TInt                          iState;
		CTelephony::TCallStatusV1     iCurrentStatus;
		CTelephony::TCallStatusV1Pckg iCurrentStatusPckg;
		CTelephony*                   iTelephony;
	};

#endif
