/*
 ============================================================================
 Name		: CenRepObserver.h
 Author	  : Usanov-Kornilov Nikolay (aka Kolay)
 Version	 : 1.0
 Copyright   : 
 Contacts:
 kolayuk@mail.ru
 http://kolaysoft.ru

 (c) KolaySoft, 2010

 Description : CCenRepObserver declaration
 ============================================================================
 */

#ifndef CENREPOBSERVER_H
#define CENREPOBSERVER_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <e32debug.h>
class CRepository; 
class MCRCallBack
           {
           public:
                   virtual void ValueChanged(TUid uid,TUint32 key,TInt aValue,TInt aErr) = 0;
                   virtual void TextValueChanged(TUid uid,TUint32 key,TPtrC aVal,TInt aErr)=0;
            };


class CCenRepObserver : public CActive
       {
       public:
               static CCenRepObserver* NewL(TUid uid,TUint32 key, MCRCallBack& aObserver);
               static CCenRepObserver* NewLC(TUid uid,TUint32 key,MCRCallBack& aObserver);
                void StartObservingL();
                void StopObserving();
                virtual ~CCenRepObserver();
                void RunL();
                void RunErrorL(TInt aError);
                void DoCancel();
                CCenRepObserver(MCRCallBack& aObserver);
                void ConstructL(TUid uid,TUint32 key);
                CRepository* iRepository;
       private:
              TUint32 iKey;
              TBool iCanceled;
              TUid iUid;
              MCRCallBack& iObserver;
        };
#endif // CENREPOBSERVER_H
