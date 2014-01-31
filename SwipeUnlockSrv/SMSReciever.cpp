/*
 ============================================================================
 Name		: SMSReciever.cpp
 Author	  : Usanov-Kornilov Nikolay (aka Kolay)
 Version	 : 1.0
 Copyright   : 
 Contacts:
 kolayuk@mail.ru
 http://kolaysoft.ru

 (c) KolaySoft, 2011

 Description : CSMSReciever implementation
 ============================================================================
 */

#include "SMSReciever.h"
#include <mtclbase.h>
#include <txtrich.h>
#include <const.h>
#include <QDebug>
#include <QString>
#include <mtuireg.h>
#include <MTMUIBAS.H>
CSMSReceiver* CSMSReceiver::NewL(MSMSRecCallBack& aObserver)
	{
	CSMSReceiver* self = new(ELeave)CSMSReceiver(aObserver);
	self->ConstructL();
	return self;
	}
 
CSMSReceiver::CSMSReceiver(MSMSRecCallBack& aObserver):iObserver(aObserver)
{
}
 
CSMSReceiver::~CSMSReceiver()
{
	delete iMtmRegistry;
    iMtmRegistry = NULL;
 
	delete iSession;    
    iSession = NULL;
}
 
void CSMSReceiver::ConstructL(void)
{	
	iSession = CMsvSession::OpenSyncL(*this);
        iLastId=0;
	iMtmRegistry = CClientMtmRegistry::NewL(*iSession);
}
 
 
void CSMSReceiver::HandleSessionEventL(TMsvSessionEvent aEvent, TAny* aArg1, TAny* aArg2, TAny* /*aArg3*/)
{
    switch (aEvent)
    {
    case EMsvEntriesChanged:
    {
        qDebug()<<"sms changed event";
        TMsvId* entryId;
        entryId = static_cast<TMsvId*>(aArg2);          // entry id from the session event

        if ( *entryId == KMsvGlobalInBoxIndexEntryId )  // new entry has been created in Inbox folder
        {
            TMsvSelectionOrdering sort;
            sort.SetShowInvisibleEntries(EFalse);    // we dont want to handle the invisible entries
            // Take a handle to the Inbox entry
            CMsvEntry* parentEntry = CMsvEntry::NewL(*iSession, KMsvGlobalInBoxIndexEntryId, sort);
            CleanupStack::PushL(parentEntry);

            CMsvEntrySelection* entries = static_cast<CMsvEntrySelection*>(aArg1);
            if(entries)
            {
                //Process each created entry, one at a time.
                for(TInt i = 0; i < entries->Count(); i++)
                {

                    HandleEntryL(entries->At(i),EFalse);
                }
            }

            CleanupStack::PopAndDestroy(1);   //  parentEntry
        }
    }
        break;
    case EMsvEntriesCreated:
    case EMsvEntriesMoved:
    {
        TMsvId* entryId;
        entryId = static_cast<TMsvId*>(aArg2);          // entry id from the session event

        if ( *entryId == KMsvGlobalInBoxIndexEntryId )  // new entry has been created in Inbox folder
        {
            TMsvSelectionOrdering sort;
            sort.SetShowInvisibleEntries(EFalse);    // we dont want to handle the invisible entries
            // Take a handle to the Inbox entry
            CMsvEntry* parentEntry = CMsvEntry::NewL(*iSession, KMsvGlobalInBoxIndexEntryId, sort);
            CleanupStack::PushL(parentEntry);

            CMsvEntrySelection* entries = static_cast<CMsvEntrySelection*>(aArg1);
            if(entries)
            {
                //Process each created entry, one at a time.
                for(TInt i = 0; i < entries->Count(); i++)
                {

                    HandleEntryL(entries->At(i),EFalse);
                }
            }

            CleanupStack::PopAndDestroy(1);   //  parentEntry
        }
        /*
        if (*entryId==KMsvSentEntryId)
        {
            CMsvEntrySelection* entries = static_cast<CMsvEntrySelection*>(aArg1);
            if(entries)
            {
                //Process each created entry, one at a time.
                for(TInt i = 0; i < entries->Count(); i++)
                {

                    HandleEntryL(entries->At(i),ETrue);
                }
            }
        }
        */
    }
        break;
    case EMsvCloseSession:
        iSession->CloseMessageServer();
        break;
    default:
        // All other events are ignored
        break;
    }
}
 
void CSMSReceiver::HandleEntryL(TMsvId& aEntId,TBool aSent)
{	
	CMsvEntry* entry = iSession->GetEntryL(aEntId);  
	CleanupStack::PushL(entry);
 
	if(entry->Entry().iMtm == KUidMsgTypeSMS)
	{        
		CBaseMtm* SmsMtm = iMtmRegistry->NewMtmL(KUidMsgTypeSMS);	
		if(SmsMtm)
		{
			CleanupStack::Pop(1);//entry
			CleanupStack::PushL(SmsMtm);
			SmsMtm->SetCurrentEntryL(entry);
			SmsMtm->LoadMessageL();
			HBufC* BodyBuffer = HBufC::NewLC(SmsMtm->Body().DocumentLength());
			TPtr BodyPoint(BodyBuffer->Des());
			SmsMtm->Body().Extract(BodyPoint,0,SmsMtm->Body().DocumentLength());
                        if (entry->Entry().Unread())
				{
				CSmsClientMtm* specificMtm = STATIC_CAST(CSmsClientMtm*, SmsMtm);
				CSmsHeader& h=specificMtm->SmsHeader();
                                QString message((QChar*)BodyBuffer->Des().Ptr(),BodyBuffer->Length());
                                if (iLastId!=entry->Entry().Id()) iObserver.GotSMSMessageL(message,h.FromAddress(),entry->Entry().Id());
                                iLastId=entry->Entry().Id();

                                }
                        else {
                               iObserver.MarkSMSRead(entry->Entry().Id());
                             }
			CleanupStack::PopAndDestroy(2);//SmsMtm,BodyBuffer		
		}
		else
		{
			CleanupStack::PopAndDestroy(1);//entry
		}
	}	
	else
	{
		CleanupStack::PopAndDestroy(1);//entry
        }
}

void CSMSReceiver::openSMS(TInt32 id)
{
qDebug()<<"openSMS"<<id;
CBaseMtm* BasMTM = iMtmRegistry->NewMtmL(KUidMsgTypeSMS);
CleanupStack::PushL(BasMTM);
qDebug()<<2;
CMtmUiRegistry* Reg = CMtmUiRegistry::NewL(*iSession);
CleanupStack::PushL(Reg);
qDebug()<<3;
BasMTM->SwitchCurrentEntryL(id);
qDebug()<<4;
CBaseMtmUi* mtmUi = Reg->NewMtmUiL(*BasMTM);
CleanupStack::PushL(mtmUi);
qDebug()<<5;

CMsvOperationWait* wait = CMsvOperationWait::NewLC(); // left in CS
qDebug()<<6;
wait->iStatus = KRequestPending;
CMsvOperation* oper = (CMsvOperation*)mtmUi->ViewL( wait->iStatus );
qDebug()<<7;
CleanupStack::PushL(oper);
wait->Start();
qDebug()<<8;
CActiveScheduler::Start();
qDebug()<<9;
// The following is to ignore the completion of other active objects. It is not
// needed if the app has a command absorbing control.
while( wait->iStatus.Int() == KRequestPending )
{
CActiveScheduler::Start();
}
qDebug()<<10;
CleanupStack::PopAndDestroy(5);//Reg,BasMTM,mtmUi,oper,wait

}
