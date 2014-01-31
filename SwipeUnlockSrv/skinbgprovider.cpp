#include "SkinBgProvider.h"
#include <qDebug>
#include <avkon.mbg>
#include <QBitmap>
#include <aknsbasicbackgroundcontrolcontext.h>
#include <aknsdrawutils.h>

SkinBgProvider::SkinBgProvider() :
    QDeclarativeImageProvider(QDeclarativeImageProvider::Pixmap)
{

}

QPixmap SkinBgProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    bool ok;
    iSize=new QSize(360,640);
    int w=CEikonEnv::Static()->ScreenDevice()->SizeInPixels().iWidth;
    int h=CEikonEnv::Static()->ScreenDevice()->SizeInPixels().iHeight;
    TSize tsize=TSize(w,h);
    qDebug()<<"requestSkinBg"<<id<<iSize->width()<<iSize->height();
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    const TAknsItemID idle = { 0x10005A26, 0x1001 };

    CAknsBasicBackgroundControlContext* iSkinContext = CAknsBasicBackgroundControlContext::NewL( idle, TRect(TPoint(0,0),tsize), EFalse );
    CFbsBitmap* offScreenBitmap = new (ELeave) CFbsBitmap();
    User::LeaveIfError( offScreenBitmap->Create( tsize, EColor16M ) );
    CFbsBitGc* bitGc = 0;
    CFbsBitmapDevice* bitmapDevice = CFbsBitmapDevice::NewL( offScreenBitmap );
    User::LeaveIfError( bitmapDevice->CreateContext( bitGc ) );

    // Draw the content on the off-screen bitmap
    qDebug()<<"draw";
    AknsDrawUtils::DrawBackground( AknsUtils::SkinInstance(), iSkinContext,(CCoeControl*) this, *bitGc,TPoint(0,0), TRect(TPoint(0,0),tsize), KAknsDrawParamDefault );
    qDebug()<<"drawed";
    QPixmap pix=QPixmap::fromSymbianCFbsBitmap(offScreenBitmap);
    return pix;
}
CGulIcon* SkinBgProvider::LoadAppIconEasy(TUid aUid)
        {
        RApaLsSession ls;
        ls.Connect();
        TApaAppInfo info;
        User::LeaveIfError(ls.GetAppInfo(info,aUid));
        HBufC* path=HBufC::NewL(255);
        TInt err=ls.GetAppIcon(aUid,path);
        User::LeaveIfError(err);
        CFbsBitmap*	AppIcon(NULL);
        CFbsBitmap*	AppIconMsk(NULL);
        //MAknsSkinInstance* skin = AknsUtils::SkinInstance();
        if ((err==KErrNone)&&(path->Length()!=0))
                {AknsUtils::CreateAppIconLC(AknsUtils::SkinInstance(),aUid, EAknsAppIconTypeContext,AppIcon,AppIconMsk);}
        else {User::Leave(KErrNotFound);}
        AknIconUtils::SetSize(AppIcon,TSize(iSize->width(),iSize->height()));
        AknIconUtils::SetSize(AppIconMsk,TSize(iSize->width(),iSize->height()));
        CleanupStack::Pop(2);
        qDebug()<<"easy"<<AppIcon->Handle();
        CGulIcon* icon=CGulIcon::NewL(AppIcon,AppIconMsk);
        ls.Close();
        return icon;
        }

CGulIcon* SkinBgProvider::LoadAppIconHard(TUid aUid)
        {
        qDebug()<<"hard";
        RApaLsSession ls;
        ls.Connect();
        CGulIcon *retval = NULL;
        CArrayFixFlat<TSize> *array = new CArrayFixFlat<TSize>(3);
        CleanupStack::PushL(array);
        qDebug()<<"0"<<array;
        TInt err = ls.GetAppIconSizes(aUid, *array);
        if(err == KErrNone && array->Count() > 0)
                {
                qDebug()<<1;
                CApaMaskedBitmap *bitmap = CApaMaskedBitmap::NewLC();
                err = ls.GetAppIcon(aUid, (*array)[0], *bitmap);
                if(err == KErrNone)
                        {
                        qDebug()<<2;
                        CFbsBitmap* bmp = new (ELeave) CFbsBitmap();
                        CleanupStack::PushL(bmp);
                        CFbsBitmap* bmp_mask = new (ELeave) CFbsBitmap();
                        CleanupStack::PushL(bmp_mask);
                        qDebug()<<3;
                        User::LeaveIfError(bmp->Create(bitmap->SizeInPixels(), bitmap->DisplayMode()));
                        User::LeaveIfError(bmp_mask->Create(bitmap->Mask()->SizeInPixels(), bitmap->Mask()->DisplayMode()));
                        qDebug()<<4;
                        CopyBitmapL(bitmap, bmp);
                        CopyBitmapL(bitmap->Mask(), bmp_mask);
                        qDebug()<<"hard"<<bmp->Handle();
                        retval = CGulIcon::NewL(bmp, bmp_mask);
                        CleanupStack::Pop(2); // bmp, bmp_mask
                        }
                        CleanupStack::PopAndDestroy(bitmap);
                }
                CleanupStack::PopAndDestroy(array);
                ls.Close();
                qDebug()<<"err"<<err;
                return retval;
        }

void SkinBgProvider::CopyBitmapL(CFbsBitmap *aSource, CFbsBitmap *aTarget)
        {
        qDebug()<<"CopyBitmapL";
        if(aSource != NULL && aTarget != NULL)
                {
                if(aSource->SizeInPixels() != aTarget->SizeInPixels() || aSource->DisplayMode() != aTarget->DisplayMode())
                        {User::Leave(KErrArgument);}
                CFbsBitmapDevice* device = CFbsBitmapDevice::NewL(aTarget);
                CleanupStack::PushL(device);
                CFbsBitGc* gc = NULL;
                User::LeaveIfError(device->CreateContext(gc));
                CleanupStack::PushL(gc);
                gc->BitBlt(TPoint(0, 0), aSource);
                CleanupStack::PopAndDestroy(gc);
                CleanupStack::PopAndDestroy(device);
                }
        }
