/*
 ============================================================================
 Name		: SMSReciever.h
 Author	  : Usanov-Kornilov Nikolay (aka Kolay)
 Version	 : 1.0
 Copyright   : 
 Contacts:
 kolayuk@mail.ru
 http://kolaysoft.ru

 (c) KolaySoft, 2011

 Description : CSMSReciever declaration
 ============================================================================
 */

#ifndef SMSRECIEVER_H
#define SMSRECIEVER_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <SMSCLNT.H>
#include <MSVAPI.H>
#include <MTCLREG.H>
#include <QString>
class MSMSRecCallBack 
{
public:
        virtual void GotSMSMessageL(QString aMessage,const TPtrC aSender, TInt32 aId) = 0;
        virtual void MarkSMSRead(TInt32 aId)=0;
};
 
 
class CSMSReceiver : public CBase, MMsvSessionObserver
    {
public:
        void openSMS(TInt32 id);
	static CSMSReceiver* NewL(MSMSRecCallBack& aObserver);
        TInt32 iLastId;
	~CSMSReceiver();
protected:
	CSMSReceiver(MSMSRecCallBack& aObserver);
    void ConstructL(void);	
	void HandleSessionEventL(TMsvSessionEvent aEvent, TAny *aArg1, TAny *aArg2, TAny *aArg3);
private:
	void HandleEntryL(TMsvId& aEntId,TBool aSent);
private:
	MSMSRecCallBack&	iObserver;
	CMsvSession*		iSession;
	CClientMtmRegistry*	iMtmRegistry;
    };

#endif // SMSRECIEVER_H
