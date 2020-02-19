#ifndef ASBASE_H
#define ASBASE_H

#include "AsUtils.h"
#include <QtCore>
#include <vector>

#include "sqlite.h"
#include "RunSql.h"
#include "sqlitetablemodel.h"

class AsBase
{
public:
    static bool isTrue(int value);
    static QString ReplaceList(QString text);
    static QString ReplaceView(QString text);
    static QString booltoInt(bool value);

    static std::vector<QString> AppSettings();

    static int setCmbValue(std::vector<QString> values, QString value);
    static void SetOption(QString Title, QString Content);
    static void UpdateSongCount(QString Bookid, QString Count);

    static void execSQL(QString SqlQuery);
    static void InitialDbOps();

    static void NewBook(QString Title, QString Category, QString Tags, QString Content, QString Songs);
    static void NewSong(QString Bookid, QString Category, QString Number, QString Title, QString Alias, QString Content, QString Key, QString Author);

    static void ResetSettings();
};

#endif