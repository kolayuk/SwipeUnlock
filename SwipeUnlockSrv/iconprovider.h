#ifndef ICONPROVIDER_H
#define ICONPROVIDER_H

#include <QDeclarativeImageProvider>

#include <gulicon.h>
#include <apgcli.h>
#include <bautils.h>
#include <aknutils.h>
#include <akniconutils.h>
#include <aknsutils.h>

class IconProvider :  public QObject, public QDeclarativeImageProvider
{
    Q_OBJECT
private:
    void CopyBitmapL(CFbsBitmap *aSource, CFbsBitmap *aTarget);
    CGulIcon* LoadAppIconHard(TUid aUid);
    CGulIcon* LoadAppIconEasy(TUid aUid);
    const QSize* iSize;
public:
    explicit IconProvider();
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);
signals:

public slots:

};

#endif // ICONPROVIDER_H
