#ifndef LOCALIZER_H
#define LOCALIZER_H

#include <QObject>
#include <QHash>
#include <QString>
#include <QStringList>
class Localizer : public QObject
{
    Q_OBJECT
public:
    explicit Localizer(int lang,QObject *parent = 0);
    int GetLang(int lang);
    QHash<int,int> locs;
    int lang;
    QStringList GetStringsAsList();
    QStringList stringslist;
signals:

public slots:

};

#endif // LOCALIZER_H
