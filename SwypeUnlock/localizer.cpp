#include "localizer.h"
#include <QHash>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <const.h>
#include <qDebug>

Localizer::Localizer(int language,QObject *parent) :
    QObject(parent)
{
    lang=language;
    QFile file(KLangSettingFile);
    file.open (QFile::ReadOnly);
    QTextStream stream ( &file );
    stream.setCodec("UTF-8");
    QString line;
    int j=0;
    QStringList lst;
    while( !stream.atEnd())
    {
         line = stream.readLine();
         lst=line.split(":");
         locs.insert(lst[0].toInt(),lst[1].toInt());
         j++;
    }
    file.close(); // when your done.
   lang=GetLang(lang);

   QString filename;
   filename.append(KLangFile);
   filename.append(QString::number(lang));

   QFile locfile(filename);
   QString txt;
   if (locfile.exists())
   {
   locfile.open (QIODevice::ReadOnly);
   QTextStream locstream ( &locfile );
   locstream.setCodec("UTF-8");
   txt=locstream.readAll();
   file.close(); // when your done.
   }
   stringslist=txt.split("\n***\n");
   qDebug()<<stringslist.count();

}
int Localizer::GetLang(int lang)
{
    const int defaultval=1;
    return locs.value(lang,defaultval);
}

QStringList Localizer::GetStringsAsList()
{
    return stringslist;
}
