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
    TBuf<255> txtval;
    TInt errint=RProperty::Get(iUid,iKey,val);
    TInt errtxt=RProperty::Get(iUid,iKey,txtval);
    RDebug::Print(_L("RunL %d %d"), errint,val);
    // resubscribe before processing new value to prevent missing updates
    iProperty.Subscribe( iStatus );
    SetActive();
    if (errint!=KErrArgument)
    {
    if (iObserver&&errint==-1)iObserver->ValChanged(iUid,iKey,val);
    if (iObserver&&(val!=0||iUid==TUid::Uid(0x10207A89))){iObserver->ValChanged(iUid,iKey,val);}
    }
    else
    {
    if (iObserver){iObserver->ValTxtChanged(iUid,iKey,txtval);}
    }
  }
