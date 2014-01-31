#include "AlbumArtProvider.h"
#include <qDebug>
#include <avkon.mbg>
#include <QBitmap>
#include <QObject>
AlbumArtProvider::AlbumArtProvider() :
    QDeclarativeImageProvider(QDeclarativeImageProvider::Pixmap)
{
    iArt = new (ELeave) CFbsBitmap();
}

QPixmap AlbumArtProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    bool ok;
    iSize=new QSize(640,640);
    QPixmap pix=QPixmap::fromSymbianCFbsBitmap(iArt);
    return pix;
}

void AlbumArtProvider::CopyBitmapL(CFbsBitmap *aSource, CFbsBitmap *aTarget)
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

void AlbumArtProvider::setAlbumArt(CFbsBitmap *aFbs)
{
    qDebug()<<"AlbumArtProvider::setAlbumArt"<<aFbs;
    iArt->Reset();
    qDebug()<<1;
    iArt->Create(aFbs->SizeInPixels(), aFbs->DisplayMode());
    qDebug()<<2;
    CopyBitmapL(aFbs, iArt);
    qDebug()<<3;
    emit AlbumArtSaved(aFbs);
    qDebug()<<4;
}

