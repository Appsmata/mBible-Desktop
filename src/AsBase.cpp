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
    int retvalue = 0;
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
    int rc = sqlite3_open("data/mBible.db", &db);

    QByteArray bar = AsUtils::UpdateSettingsSql(Title, Content).toLocal8Bit();
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
    int rc = sqlite3_open_v2(AsUtils::DbNameChar(), &songsDb, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);

    if (rc == SQLITE_OK)
    {
        rc = sqlite3_get_table(songsDb, AsUtils::SettingsSelectSql(), &qryResult, &row, &col, &err_msg);

        for (int i = 1; i < row + 1; i++)
        {
            settings.push_back(*(qryResult + i * col + 0));
        }
        sqlite3_free_table(qryResult);
        sqlite3_close(songsDb);
    }

    return settings;
}

/*
	Save app logs & exception to vSongBook.log
*/
void AsBase::WriteLogs(QString Source, QString Message, QString Details, QString Exception)
{
	QDir DataDir;
	if (!DataDir.exists("data")) DataDir.mkpath("data");

	QFile Logfile("data/mBible.log");
	if (!Logfile.exists()) Logfile.open(QIODevice::Append);
	else Logfile.open(QIODevice::Append);

	QString LogText = "\n<mbiblelog>";
	LogText.append("\n\t<source>" + Source + "</source>");
	LogText.append("\n\t<time>" + AsUtils::TimeDateNow() + "</time>");
	LogText.append("\n\t<message>" + Message + "</message>");
	if (!Details.isEmpty())
	{
		if (Source == "SQLite") LogText.append("\n\t<SqlQuery>" + Details + "</SqlQuery>");
		else LogText.append("\n\t<details>" + Details + "</details>");
	}

	if (!Exception.isEmpty())
		LogText.append("\n\t<exception>" + Exception + "</exception>");
	LogText.append("\n</mbiblelog>\n");

	QByteArray bar = LogText.toLocal8Bit();
	char* logText = bar.data();

	Logfile.write(logText, qstrlen(logText));
	Logfile.close();
}

void AsBase::execSql(QString SqlQuery)
{
    sqlite3* db;
    char* zErrMsg = NULL;
    int rc = sqlite3_open(AsUtils::DbNameChar(), &db);

    QByteArray bar = SqlQuery.toLocal8Bit();
    char* sqlQuery = bar.data();

    rc = sqlite3_exec(db, sqlQuery, 0, 0, &zErrMsg);

    if (rc != SQLITE_OK) sqlite3_free(zErrMsg);

    sqlite3_close(db);
}

void AsBase::NewBook(QString Title, QString Category, QString Tags, QString Content, QString Position, QString Songs)
{
    sqlite3* db;
    char* zErrMsg = NULL;
    int rc = sqlite3_open(AsUtils::DbNameChar(), &db);

    uint timenow = QDateTime::currentSecsSinceEpoch();
    QString timeStr = QString::number(timenow);

    //QByteArray bar = AsUtils::BookInsertSql(Title, Category, Tags, Content, Position, Songs).toLocal8Bit();
    //char* sqlQuery = bar.data();

    //rc = sqlite3_exec(db, sqlQuery, 0, 0, &zErrMsg);

    if (rc != SQLITE_OK) sqlite3_free(zErrMsg);
    sqlite3_close(db);
}

QString AsBase::CountSongs(QString Bookid)
{
	sqlite3* db;
	char* err_msg = NULL, ** qryResult = NULL;
	int row, col;
	int rc = sqlite3_open(AsUtils::DbNameChar(), &db);

	QString SqlQuery = "SELECT COUNT() FROM " + AsUtils::TableSongs() + 
		" ColumnWhere " + AsUtils::TableSongs() + "." + AsUtils::ColumnBookid() + "=" + Bookid;
	QByteArray bar = SqlQuery.toLocal8Bit();
	char* sqlQuery = bar.data();

	rc = sqlite3_get_table(db, sqlQuery, &qryResult, &row, &col, &err_msg);
	QString songcount = *(qryResult + 1 * col + 0);
	sqlite3_free(err_msg);
	sqlite3_close(db);

	return songcount;
}

void AsBase::UpdateSongCount(QString Bookid, QString Count)
{
	sqlite3* db;
	char* zErrMsg = NULL;
	int rc = sqlite3_open(AsUtils::DbNameChar(), &db);

	uint timenow = QDateTime::currentSecsSinceEpoch();
	QString timeStr = QString::number(timenow);
	
	//QString SqlQuery = "UPDATE " + AsUtils::TableBooks() + " SET " + AsUtils::ColumnQcount() + "='" + Count + "', " + 
		AsUtils::ColumnUpdated() + "='" + AsUtils::TimeNow() + "' WHERE " + AsUtils::ColumnBookid() + "=" + Bookid;
	//QByteArray bar = SqlQuery.toLocal8Bit();
	//char* sqlQuery = bar.data();

	//rc = sqlite3_exec(db, sqlQuery, 0, 0, &zErrMsg);

	if (rc != SQLITE_OK) sqlite3_free(zErrMsg);
	sqlite3_close(db);
}

void AsBase::NewSong(QString Number, QString Title, QString Alias, QString Content, QString Key, QString Author, QString Bookid, QString Categoryid)
{
    sqlite3* db;
    char* zErrMsg = NULL;
    int rc = sqlite3_open(AsUtils::DbNameChar(), &db);

    //QByteArray bar = AsUtils::SongSingleSql(Number, Title, Alias, Content, Key, Author, Bookid, Categoryid).toLocal8Bit();
    //char* sqlQuery = bar.data();

    //rc = sqlite3_exec(db, sqlQuery, 0, 0, &zErrMsg);

    if (rc != SQLITE_OK) sqlite3_free(zErrMsg);
    sqlite3_close(db);
}

void AsBase::InitialDbOps()
{
    QString timenow = AsUtils::TimeNow();
    AsBase::execSql(AsUtils::CreateBooksTableSql());
    AsBase::execSql(AsUtils::CreateHistoryTableSql());
    AsBase::execSql(AsUtils::CreateSettingsNaviTableSql());
    AsBase::execSql(AsUtils::CreateSettingsTableSql());
    AsBase::execSql(AsUtils::CreateSongsTableSql());

    AsBase::execSql(AsUtils::SettingsNaviSql());    
    AsBase::execSql(AsUtils::SettingsSql());
}

void AsBase::ResetSettings()
{
    sqlite3* db;
    char* zErrMsg = NULL;
    int rc = sqlite3_open(AsUtils::DbNameChar(), &db);

    QByteArray bar = "DROP TABLE " + AsUtils::TableSettings().toLocal8Bit();
    char* sqlQuery = bar.data();

    rc = sqlite3_exec(db, sqlQuery, 0, 0, &zErrMsg);

    if (rc != SQLITE_OK) sqlite3_free(zErrMsg);
    sqlite3_close(db);
    
    AsBase::execSql(AsUtils::SettingsNaviSql());
}
