#include "AsBase.h"

#include "sqlite.h"
#include "RunSql.h"
#include "sqlitetablemodel.h"

bool AsBase::isTrue(int value)
{
    bool result = false;
    if (value == 0) result = false;
    else if (value == 1) result = true;
    return result;
}

QString AsBase::ReplaceList(QString text)
{
    text = text.replace("\\n", " ");
    text = text.replace("\\", "");
    return text;
}

QString AsBase::ReplaceView(QString text)
{
    text = text.replace("\\n", "\r\n");
    text = text.replace("\\", "");
    return text;
}

QString AsBase::booltoInt(bool value)
{
    QString booltoint = "0";
    if (value == true) booltoint = "1";
    else if (value == false) booltoint = "0";
    return booltoint;
}

int AsBase::setCmbValue(std::vector<QString> values, QString value)
{
    int retvalue;
    for (int v = 0; v < values.size(); v++)
    {
        if (value == values[v]) retvalue = v;
    }
    return retvalue;
}

void AsBase::SetOption(QString Title, QString Content)
{
    sqlite3* db;
    char* zErrMsg = NULL;
    int rc = sqlite3_open("Data/vSongBook.db", &db);

    QByteArray bar = AsUtils::UPDATE_SETTINGS_SQL(Title, Content).toLocal8Bit();
    char* sqlQuery = bar.data();

    rc = sqlite3_exec(db, sqlQuery, 0, 0, &zErrMsg);

    if (rc != SQLITE_OK) sqlite3_free(zErrMsg);
    sqlite3_close(db);
}

std::vector<QString> AsBase::AppSettings()
{
    std::vector<QString> settings;
    sqlite3* songsDb;
    char* err_msg = NULL, ** qryResult = NULL;
    int row, col;
    int rc = sqlite3_open_v2(AsUtils::APP_DB(), &songsDb, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);

    if (rc == SQLITE_OK)
    {
        rc = sqlite3_get_table(songsDb, AsUtils::SETTINGS_SELECT_SQL(), &qryResult, &row, &col, &err_msg);

        for (int i = 1; i < row + 1; i++)
        {
            settings.push_back(*(qryResult + i * col + 0));
        }
        sqlite3_free_table(qryResult);
        sqlite3_close(songsDb);
    }

    return settings;
}

void AsBase::UpdateSongCount(QString Bookid, QString Count)
{
    sqlite3* db;
    char* zErrMsg = NULL;
    int rc = sqlite3_open(AsUtils::APP_DB(), &db);

    QByteArray bar = AsUtils::BOOK_SONGS_COUNT_SQL(Bookid, Count).toLocal8Bit();
    char* sqlQuery = bar.data();

    rc = sqlite3_exec(db, sqlQuery, 0, 0, &zErrMsg);

    if (rc != SQLITE_OK) sqlite3_free(zErrMsg);
    sqlite3_close(db);
}

void AsBase::execSQL(QString SqlQuery)
{
    sqlite3* db;
    char* zErrMsg = NULL;
    int rc = sqlite3_open(AsUtils::APP_DB(), &db);

    QByteArray bar = SqlQuery.toLocal8Bit();
    char* sqlQuery = bar.data();

    rc = sqlite3_exec(db, sqlQuery, 0, 0, &zErrMsg);

    if (rc != SQLITE_OK) sqlite3_free(zErrMsg);

    sqlite3_close(db);
}

void AsBase::NewBook(QString Title, QString Category, QString Tags, QString Content, QString Songs)
{
    sqlite3* db;
    char* zErrMsg = NULL;
    int rc = sqlite3_open(AsUtils::APP_DB(), &db);

    uint timenow = QDateTime::currentSecsSinceEpoch();
    QString timeStr = QString::number(timenow);

    QByteArray bar = AsUtils::BOOK_INSERT_SQL(Title, Category, Tags, Content, Songs).toLocal8Bit();
    char* sqlQuery = bar.data();

    rc = sqlite3_exec(db, sqlQuery, 0, 0, &zErrMsg);

    if (rc != SQLITE_OK) sqlite3_free(zErrMsg);
    sqlite3_close(db);
}

void AsBase::NewSong(QString Bookid, QString Category, QString Number, QString Title, QString Alias, QString Content, QString Key, QString Author)
{
    sqlite3* db;
    char* zErrMsg = NULL;
    int rc = sqlite3_open(AsUtils::APP_DB(), &db);

    QByteArray bar = AsUtils::SONG_INSERT_SQL(Number, Title, Alias, Content, Key, Author, Bookid, Category).toLocal8Bit();
    char* sqlQuery = bar.data();

    rc = sqlite3_exec(db, sqlQuery, 0, 0, &zErrMsg);

    if (rc != SQLITE_OK) sqlite3_free(zErrMsg);
    sqlite3_close(db);
}

void AsBase::InitialDbOps()
{
    QString timenow = AsUtils::TIMENOW();
    AsBase::execSQL(AsUtils::CREATE_BOOKS_TABLE_SQL());
    AsBase::execSQL(AsUtils::CREATE_HISTORY_TABLE_SQL());
    AsBase::execSQL(AsUtils::CREATE_SETTINGS_NAVI_TABLE_SQL());
    AsBase::execSQL(AsUtils::CREATE_SETTINGS_TABLE_SQL());
    AsBase::execSQL(AsUtils::CREATE_SONGS_TABLE_SQL());

    AsBase::execSQL(AsUtils::SETTINGS_NAVI_SQL());
    AsBase::execSQL(AsUtils::SETTINGS_SQL());
}

void AsBase::ResetSettings()
{
    sqlite3* db;
    char* zErrMsg = NULL;
    int rc = sqlite3_open(AsUtils::APP_DB(), &db);

    QByteArray bar = "DROP TABLE " + AsUtils::TBL_SETTINGS().toLocal8Bit();
    char* sqlQuery = bar.data();

    rc = sqlite3_exec(db, sqlQuery, 0, 0, &zErrMsg);

    if (rc != SQLITE_OK) sqlite3_free(zErrMsg);
    sqlite3_close(db);

    AsBase::execSQL(AsUtils::SETTINGS_NAVI_SQL());
}
