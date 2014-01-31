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

 Description : CCenRepObserver implementation
 ============================================================================
 */

#include <centralrepository.h>
#include <CenRepObserver.h>

CCenRepObserver* CCenRepObserver::NewLC(TUid uid,TUint32 key,MCRCallBack& aCB)
	{
	CCenRepObserver* self = new (ELeave) CCenRepObserver(aCB);
	CleanupStack::PushL(self);
        self->ConstructL(uid,key);
	return self;
	}

CCenRepObserver* CCenRepObserver::NewL(TUid uid,TUint32 key,MCRCallBack& aCB)
	{
        CCenRepObserver* self = CCenRepObserver::NewLC(uid,key,aCB);
	CleanupStack::Pop(); // self;
	return self;
	}

//trivial NewL and NewLC have been omitted.
void CCenRepObserver::ConstructL(TUid uid,TUint32 key)
        {
        iUid = uid; //observe profile engine to
        iKey = key; //see which profile is active
        iRepository = CRepository::NewL( iUid );
        CActiveScheduler::Add(this);
        iCanceled=ETrue;
         }
CCenRepObserver::CCenRepObserver(MCRCallBack& aObserver) : iObserver(aObserver), CActive (EPriorityHigh)
         {
         //do nothing
         }
CCenRepObserver::~CCenRepObserver()
         {
         Cancel(); //first cancel because iRepository is used there
         delete iRepository;
         iRepository=NULL;
         }
void CCenRepObserver::StartObservingL()
         {
         if( IsActive() )
         {
         RDebug::Print(_L("CR already active"));
         return; //do nothing if allready observing
         }
         TInt err=iRepository->NotifyRequest( iKey, iStatus );
         RDebug::Print(_L("error while CR srarted: %d"),err);
         iCanceled=EFalse;
         RDebug::Print(_L("Started"));
         SetActive();
          }
void CCenRepObserver::StopObserving()
          {
          iCanceled=ETrue;
          RDebug::Print(_L("Stopped"));
          Cancel();
          }
void CCenRepObserver::DoCancel()
          {
          iRepository->NotifyCancel(iKey);
          //  iRepository->NotifyCancelAll();
          }
void CCenRepObserver::RunL()
          {
          TInt value = -1;
          TBuf<512> buf;
          TInt error = iRepository->Get( iKey, value);
          //always check the error cod
          if( error == KErrNone)
                 {
                 //observer received the profile value as integer
                 //this happens even if the value hasnt really changed
                 //some application may have set the same value again
                 if (!iCanceled){iObserver.ValueChanged(iUid,iKey,value,iStatus.Int());}
                 }
          else if (error==KErrArgument)
          {
              TInt error2 = iRepository->Get( iKey, buf);
              if (!iCanceled) {iObserver.TextValueChanged(iUid,iKey,buf,error2);}
          }
          // Re-subscribe
          error = iRepository->NotifyRequest( iKey, iStatus );
          if( error == KErrNone ){SetActive();}
           }

