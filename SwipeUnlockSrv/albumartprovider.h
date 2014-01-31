#ifndef AlbumArtProvider_H
#define AlbumArtProvider_H

#include <QDeclarativeImageProvider>

#include <gulicon.h>
#include <apgcli.h>
#include <bautils.h>
#include <aknutils.h>
#include <akniconutils.h>
#include <aknsutils.h>

class AlbumArtProvider :  public QObject, public QDeclarativeImageProvider
{
    Q_OBJECT
private:
    void CopyBitmapL(CFbsBitmap *aSource, CFbsBitmap *aTarget);
    const QSize* iSize;
    CFbsBitmap* iArt;
public:
    explicit AlbumArtProvider();
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);
signals:
    void AlbumArtSaved(CFbsBitmap*);
public slots:
    void setAlbumArt(CFbsBitmap* aFbs);
};

#endif // AlbumArtProvider_H
