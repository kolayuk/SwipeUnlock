#ifndef PROPERTYOBSERVER_H
#define PROPERTYOBSERVER_H
#include <e32property.h>
#include <e32base.h>

class MPropertyCallBack
{
public:
  virtual void ValChanged(TInt aValue) = 0;
};

class CPropertyObserver : public CActive
        {
        enum {EPriority=0};
public:
        static CPropertyObserver* NewL( const TUid aUid,
                                    const TUint32 aKey,
                                    MPropertyCallBack* aNotifier );
        virtual ~CPropertyObserver();

private:
        CPropertyObserver( const TUid aUid, const TUint32 aKey,
                         MPropertyCallBack* aNotifier );
        void ConstructL();
        void RunL();
        void DoCancel();
private:
        RProperty               iProperty;
        const TUid              iUid;
        const TUint32           iKey;
        MPropertyCallBack*  iObserver;
        };

#endif // PROPERTYOBSERVER_H
