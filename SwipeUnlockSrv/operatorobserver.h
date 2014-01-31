#ifndef OPERATOROBSERVER_H
#define OPERATOROBSERVER_H

#include <Etel3rdParty.h>
class MOperatorObserver
{
public:
    virtual void GetOperatorName(const TDesC& aOperatorName,TInt err) = 0;

};

class COperatorObserver : public CActive
    {
public:
    static COperatorObserver* NewL(MOperatorObserver* aObserver);
    static COperatorObserver* NewLC(MOperatorObserver* aObserver);
    void ConstructL(void);
    ~COperatorObserver();
    void GetOperator();
protected:
    void DoCancel();
    void RunL();
private:
    COperatorObserver(MOperatorObserver* aObserver);

private:
    MOperatorObserver* 			iObserver;
    CTelephony* 					iTelephony;
    CTelephony::TOperatorNameV1 iOperatorNameV1;
    CTelephony::TOperatorNameV1Pckg iOperatorNameV1Pckg;
};

#endif // OPERATOROBSERVER_H
