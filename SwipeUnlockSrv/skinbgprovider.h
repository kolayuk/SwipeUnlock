#ifndef SkinBgProvider_H
#define SkinBgProvider_H

#include <QDeclarativeImageProvider>

#include <gulicon.h>
#include <apgcli.h>
#include <bautils.h>
#include <aknutils.h>
#include <akniconutils.h>
#include <aknsutils.h>
#include <coecntrl.h>
class SkinBgProvider :  public QObject, public QDeclarativeImageProvider,public CCoeControl
{
    Q_OBJECT
private:
    void CopyBitmapL(CFbsBitmap *aSource, CFbsBitmap *aTarget);
    CGulIcon* LoadAppIconHard(TUid aUid);
    CGulIcon* LoadAppIconEasy(TUid aUid);
    const QSize* iSize;
public:
    explicit SkinBgProvider();
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);
signals:

public slots:

};

#endif // SkinBgProvider_H
