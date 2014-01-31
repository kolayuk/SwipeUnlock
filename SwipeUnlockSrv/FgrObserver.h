/*
 * FgrObserver.h
 *
 *  Created on: 24.10.2009
 *      Author: Avis
 */

#ifndef FGROBSERVER_H_
#define FGROBSERVER_H_

#include <apgtask.h>
#include <w32std.h>
class MFgrCallBack 
{
public:
	virtual void GroupListChanged() = 0;
	virtual void ScreenChanged() = 0;
        virtual void KeyCaptured(TWsEvent aEvent)=0;
};
 
class CFgrObserver : public CActive 
{
public:
	static CFgrObserver* NewL(RWsSession& aWsSession,MFgrCallBack& aCallBack);
	static CFgrObserver* NewLC(RWsSession& aWsSession,MFgrCallBack& aCallBack);
	virtual ~CFgrObserver();
        TInt CaptureKey(TInt aScancode);
	RWindowGroup    iWg;
	TInt iHandle;
        void CancelCapture(TInt aHandle);
private:
	CFgrObserver(RWsSession& aWsSession,MFgrCallBack& aCallBack);
	void ConstructL();
	void RunL();
	void DoCancel();
	void Listen();
private:
	MFgrCallBack& 	iCallBack;
	RWsSession&     iWsSession; 
};
#endif /* FGROBSERVER_H_ */
