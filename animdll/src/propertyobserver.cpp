#include <propertyobserver.h>
#include <e32property.h>
#include <e32base.h>
#include <e32debug.h>
CPropertyObserver::CPropertyObserver(
        const TUid aUid, const TUint32 aKey,
        MPropertyCallBack* aObserver )
            : CActive(EPriorityHigh), iUid( aUid ),
              iKey( aKey ), iObserver( aObserver)
        {
        }

CPropertyObserver* CPropertyObserver::NewL( const TUid aUid, const TUint32 aKey,
                               MPropertyCallBack* aObserver )
        {
        CPropertyObserver* self=
            new(ELeave) CPropertyObserver( aUid, aKey, aObserver );
        CleanupStack::PushL(self);
        self->ConstructL();
        CleanupStack::Pop(self);
        return self;
        }

void CPropertyObserver::ConstructL()
        {
        RThread t;
        RDebug::Print(_L("Property init, thread %d"),t.Id().Id());
        User::LeaveIfError( iProperty.Attach( iUid, iKey ) );
        CActiveScheduler::Add(this);
        // initial subscription and process current property value
        RunL();
        }

CPropertyObserver::~CPropertyObserver()
        {
        Cancel();
        iProperty.Close();
        }

void CPropertyObserver::DoCancel()
        {
        iProperty.Cancel();
        }

void CPropertyObserver::RunL()
  {
    TInt val;
    RProperty::Get(iUid,iKey,val);
    // resubscribe before processing new value to prevent missing updates
    iProperty.Subscribe( iStatus );
    SetActive();
    if (iObserver){iObserver->ValChanged(val);}

  }
