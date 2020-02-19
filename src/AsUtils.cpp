#include "AsUtils.h"

QString AsUtils::DB_FILE() { return R"(Data/mBible.db)"; }
char* AsUtils::APP_DB() { return R"(Data/mBible.db)"; }

QString AsUtils::TBL_BOOKS() { return "books"; }
QString AsUtils::TBL_HISTORY() { return "history"; }
QString AsUtils::TBL_SETTINGS() { return "settings"; }
QString AsUtils::TBL_SETTINGS_NAVI() { return "settings_navi"; }
QString AsUtils::TBL_SONGS() { return "songs"; }
QString AsUtils::TBL_VERSES() { return "verses_"; }

QString AsUtils::BOOKID() { return "bookid"; }
QString AsUtils::TESTAMENT() { return "testament"; }
QString AsUtils::CODE() { return "code"; }
QString AsUtils::CHAPTERS() { return "chapters"; }
QString AsUtils::SWAHILI() { return "swahili"; }
QString AsUtils::CATEGORYID() { return "categoryid"; }
QString AsUtils::ENABLED() { return "enabled"; }
QString AsUtils::TITLE() { return "title"; }
QString AsUtils::CONTENT() { return "content"; }
QString AsUtils::QCOUNT() { return "qcount"; }
QString AsUtils::POSITION() { return "position"; }
QString AsUtils::BACKPATH() { return "backpath"; }
QString AsUtils::NOTES() { return "notes"; }
QString AsUtils::CREATED() { return "created"; }
QString AsUtils::UPDATED() { return "updated"; }

QString AsUtils::ENTRY() { return "entry"; }
QString AsUtils::TYPE() { return "type"; }
QString AsUtils::ITEM() { return "item"; }
QString AsUtils::EXTRA() { return "extra"; }

QString AsUtils::SETTINGID() { return "settingid"; }

QString AsUtils::NAVID() { return "navid"; }
QString AsUtils::TAGS() { return "tags"; }

QString AsUtils::VERSEID() { return "verseid"; }
QString AsUtils::HIGHLIGHT() { return "highlight"; }

QString AsUtils::SONGID() { return "songid"; }
QString AsUtils::POSTID() { return "postid"; }
QString AsUtils::NUMBER() { return "number"; }
QString AsUtils::BASETYPE() { return "basetype"; }
QString AsUtils::ALIAS() { return "alias"; }
QString AsUtils::VIEWS() { return "views"; }
QString AsUtils::KEY() { return "key"; }
QString AsUtils::ISFAV() { return "isfav"; }
QString AsUtils::AUTHOR() { return "author"; }
QString AsUtils::WHAT() { return "metawhat"; }
QString AsUtils::WHEN() { return "metawhen"; }
QString AsUtils::WHERE() { return "metawhere"; }
QString AsUtils::WHO() { return "metawho"; }
QString AsUtils::NETTHUMBS() { return "netthumbs"; }
QString AsUtils::ACOUNT() { return "acount"; }
QString AsUtils::USERID() { return "userid"; }

QString AsUtils::TIMENOW()
{
	uint time_now = QDateTime::currentSecsSinceEpoch();
	return QString::number(time_now);
}

QString AsUtils::CREATE_BOOKS_TABLE_SQL()
{
	return "CREATE TABLE " + TBL_BOOKS() + " (" +
		BOOKID() + " INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, " +
		CATEGORYID() + " INTEGER, " +
		ENABLED() + " INTEGER NOT NULL DEFAULT '0', " +
		TITLE() + " VARCHAR(100), " +
		TAGS() + " VARCHAR(250), " +
		QCOUNT() + " INTEGER NOT NULL DEFAULT '0', " +
		POSITION() + " INTEGER NOT NULL DEFAULT '0', " +
		CONTENT() + " VARCHAR(1000), " +
		BACKPATH() + " VARCHAR(250), " +
		CREATED() + " VARCHAR(20), " +
		UPDATED() + " VARCHAR(20));";
}

QString AsUtils::CREATE_HISTORY_TABLE_SQL()
{
	return "CREATE TABLE " + TBL_HISTORY() + " (" +
		ENTRY() + " INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, " +
		TYPE() + " VARCHAR(50) NOT NULL DEFAULT 'SONG', " +
		ITEM() + " INTEGER NOT NULL DEFAULT '0', " +
		TITLE() + " VARCHAR(100), " +
		EXTRA() + " VARCHAR(200));";
	CREATED() + " VARCHAR(20));";
}

QString AsUtils::CREATE_SETTINGS_TABLE_SQL()
{
	return "CREATE TABLE " + TBL_SETTINGS() + " (" +
		SETTINGID() + " INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, " +
		TITLE() + " VARCHAR(100), " +
		CONTENT() + " VARCHAR(1000), " +
		CREATED() + " VARCHAR(20), " +
		UPDATED() + " VARCHAR(20));";
}

QString AsUtils::CREATE_SETTINGS_NAVI_TABLE_SQL()
{
	return "CREATE TABLE " + TBL_SETTINGS_NAVI() + " (" +
		NAVID() + " INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, " +
		ENABLED() + " INTEGER NOT NULL DEFAULT '0', " +
		TITLE() + " VARCHAR(100), " +
		CONTENT() + " VARCHAR(1000), " +
		EXTRA() + " VARCHAR(100), " +
		TAGS() + " VARCHAR(50));";
}

QString AsUtils::CREATE_SONGS_TABLE_SQL()
{
	return "CREATE TABLE " + TBL_SONGS() + " (" +
		SONGID() + " INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, " +
		POSTID() + " INTEGER, " +
		BOOKID() + " INTEGER, " +
		CATEGORYID() + " INTEGER, " +
		BASETYPE() + " VARCHAR(10), " +
		NUMBER() + " INTEGER NOT NULL DEFAULT '0', " +
		ALIAS() + " VARCHAR(250), " +
		TITLE() + " VARCHAR(100), " +
		TAGS() + " VARCHAR(100), " +
		CONTENT() + " VARCHAR(10000), " +
		KEY() + " VARCHAR(10), " +
		AUTHOR() + " VARCHAR(100), " +
		NOTES() + " VARCHAR(250), " +
		CREATED() + " VARCHAR(20), " +
		UPDATED() + " VARCHAR(20), " +
		WHAT() + " VARCHAR(20), " +
		WHEN() + " VARCHAR(20), " +
		WHERE() + " VARCHAR(20), " +
		WHO() + " VARCHAR(20), " +
		NETTHUMBS() + " INTEGER, " +
		VIEWS() + " INTEGER NOT NULL DEFAULT '0', " +
		ISFAV() + " INTEGER NOT NULL DEFAULT '0', " +
		ACOUNT() + " INTEGER, " +
		USERID() + " INTEGER));";
}

QString AsUtils::BOOK_SELECT_SQL()
{
	return "SELECT " +
		BOOKID() + ", " +
		TESTAMENT() + ", " +
		CODE() + ", " +
		TITLE() + ", " +
		CHAPTERS() + ", " +
		SWAHILI() +
		" FROM " + TBL_BOOKS();
}

QString AsUtils::BOOK_LIST_SQL(QString State)
{
	return BOOK_SELECT_SQL() + " WHERE " + ENABLED() + "=" + State + " ORDER BY " + POSITION();
}

QString AsUtils::BOOK_SINGLE_SQL(QString Book)
{
	return BOOK_SELECT_SQL() + " WHERE " + BOOKID() + "=" + Book;
}

QString AsUtils::BOOK_SEARCH_SQL(QString Search, bool SearchOT, bool SearchNT)
{
	QString Testaments = "", WhereQry = "";
	if (SearchOT && !SearchNT) Testaments = " AND " + TESTAMENT() + "=1";
	else if (!SearchOT && SearchNT) Testaments = " AND " + TESTAMENT() + "=2";

	QString SqlQuery = BOOK_SELECT_SQL();

	if (!Search.isEmpty())
	{
		WhereQry.append(CODE() + " LIKE '%" + Search + "%'" + Testaments);
		WhereQry.append(" OR " + TITLE() + " LIKE '%" + Search + "%'" + Testaments);
		WhereQry.append(" OR " + SWAHILI() + " LIKE '%" + Search + "%'" + Testaments);
	}
	else WhereQry.append(Testaments);

	SqlQuery.append((WhereQry.isEmpty() ? "" : " WHERE " + WhereQry) + " ORDER BY " + BOOKID() + " ASC");
	if (SqlQuery.contains("WHERE  AND")) SqlQuery.replace("WHERE  AND", "WHERE ");
	return SqlQuery;
}

QString AsUtils::BOOK_INSERT_SQL(QString Title, QString Category, QString Tags, QString Content, QString Songs)
{
	return "INSERT INTO " + TBL_BOOKS() +
		"( " + TITLE() + ", " + CATEGORYID() + ", " + TAGS() + ", " + CONTENT() + ", " + QCOUNT() + ", " + CREATED() +
		" ) VALUES ( '" + Title + "', " + Category + "', " + Tags + "', '" + Content + "', " + Songs + ", " + TIMENOW() + ")";
}

QString AsUtils::BOOK_UPDATE_SQL(QString Bookid, QString Title, QString Tags, QString Content)
{
	return "UPDATE " + TBL_BOOKS() + " SET " + TITLE() + "='" + Title + "', " + TAGS() + "='" + Tags +
		"', " + CONTENT() + "='" + Content + "', " + UPDATED() + "='" + TIMENOW() +
		"' WHERE " + BOOKID() + "=" + Bookid;
}

QString AsUtils::BOOK_SONGS_COUNT_SQL(QString Bookid, QString Songs)
{
	return "UPDATE " + TBL_BOOKS() + " SET " + QCOUNT() + "='" + Songs + "', " + UPDATED() + "='" + TIMENOW() +
		"' WHERE " + BOOKID() + "='" + Bookid + "'";
}

char* AsUtils::BOOK_DELETE_SQL(QString Bookid)
{
	QString SqlQuery = "DELETE FROM " + TBL_BOOKS() + " WHERE " + BOOKID() + "= " + Bookid + "; " +
		"DELETE FROM " + TBL_SONGS() + " WHERE " + BOOKID() + "=" + Bookid;
	QByteArray bar = SqlQuery.toLocal8Bit();
	return bar.data();
}

QString AsUtils::HISTORY_SELECT_SQL(QString STATE)
{
	return "SELECT " +
		ENTRY() + ", " +
		TYPE() + ", " +
		ITEM() + ", " +
		TITLE() + ", " +
		EXTRA() + ", " +
		CREATED() +
		" FROM " + TBL_HISTORY(); //" WHERE " + CREATED() + "=" + STATE;
}

char* AsUtils::SETTINGS_SELECT_SQL()
{
	QString SettingsQry = "SELECT " + CONTENT() + " FROM " + TBL_SETTINGS() + " ORDER BY " + SETTINGID();
	QByteArray bar = SettingsQry.toLocal8Bit();
	return bar.data();
}

QString AsUtils::SETTINGS_NAVI_SELECT_SQL(QString Search)
{
	QString SqlQuery = "SELECT " + NAVID() + ", " + ENABLED() + ", " + TITLE() + ", " + CONTENT() + ", " +
		EXTRA() + ", " + TAGS() + " FROM " + TBL_SETTINGS_NAVI();

	if (!Search.isEmpty())
	{
		SqlQuery.append(" WHERE " + TITLE() + " LIKE '%" + Search + "%' " +
			"OR " + CONTENT() + " LIKE '%" + Search + "%'");
	}

	SqlQuery.append(" ORDER BY " + NAVID() + " ASC");
	return SqlQuery;
}

QString AsUtils::SONG_SELECT_SQL()
{
	return "SELECT " +
		SONGID() + ", " +
		TBL_SONGS() + "." + BOOKID() + ", " +
		NUMBER() + ", " +
		ALIAS() + ", " +
		TBL_SONGS() + "." + TITLE() + ", " +
		TBL_SONGS() + "." + TAGS() + ", " +
		TBL_SONGS() + "." + CONTENT() + ", " +
		KEY() + ", " +
		AUTHOR() + ", " +
		ISFAV() + ", " +  
		TBL_SONGS() + "." + CREATED() + ", " +
		TBL_SONGS() + "." + UPDATED() + ", " +
		TBL_BOOKS() + "." + TITLE() +
		" FROM " + TBL_SONGS() +
		" INNER JOIN " + TBL_BOOKS() + " ON " +
		TBL_BOOKS() + "." + CATEGORYID() + "=" + TBL_SONGS() + "." + CATEGORYID();
}

QString AsUtils::SONG_SEARCH_SQL(QString SearchStr, QString Bookid, bool SearchAll)
{

	QString SqlQuery = SONG_SELECT_SQL() + " WHERE ";

	if (SearchStr.isEmpty())
		SqlQuery.append(TBL_SONGS() + "." + BOOKID() + "=" + Bookid);
	else
	{
		bool isNumeric;
		int searchint = SearchStr.toInt(&isNumeric, 10);
		if (SearchAll)
		{
			if (isNumeric)
			{
				SqlQuery.append(NUMBER() + "=" + SearchStr);
			}
			else
			{
				SqlQuery.append(TBL_SONGS() + "." + TITLE() + " LIKE '%" + SearchStr + "%'");
				SqlQuery.append(" OR " + TBL_SONGS() + "." + ALIAS() + " LIKE '%" + SearchStr + "%'");
				SqlQuery.append(" OR " + TBL_SONGS() + "." + CONTENT() + " LIKE '%" + SearchStr + "%'");
			}
		}
		else
		{
			if (isNumeric)
			{
				SqlQuery.append(TBL_SONGS() + "." + NUMBER() + "=" + SearchStr);
				SqlQuery.append(" AND " + TBL_SONGS() + "." + BOOKID() + "=" + Bookid);
			}
			else
			{
				SqlQuery.append(TBL_SONGS() + "." + TITLE() + " LIKE '%" + SearchStr + "%'");
				SqlQuery.append(" AND " + TBL_SONGS() + "." + BOOKID() + "=" + Bookid);
				SqlQuery.append(" OR " + TBL_SONGS() + "." + ALIAS() + " LIKE '%" + SearchStr + "%'");
				SqlQuery.append(" AND " + TBL_SONGS() + "." + BOOKID() + "=" + Bookid);
				SqlQuery.append(" OR " + TBL_SONGS() + "." + CONTENT() + " LIKE '%" + SearchStr + "%'");
				SqlQuery.append(" AND " + TBL_SONGS() + "." + BOOKID() + "=" + Bookid);
			}
		}
	}

	SqlQuery.append(" ORDER BY number ASC");
	return SqlQuery;
}

QString AsUtils::SONG_SINGLE_SQL(QString Song)
{
	return SONG_SELECT_SQL() + " WHERE " + SONGID() + "=" + Song;
}

QString AsUtils::SONG_INSERT_SQL(QString Number, QString Title, QString Alias, QString Content, QString Key, QString Author, QString Bookid, QString Categoryid)
{
	return "INSERT INTO " + TBL_SONGS() +
		"( " + NUMBER() + ", " + TITLE() + ", " + ALIAS() + ", " + CONTENT() + ", " + KEY() + ", " + BOOKID() + ", " +
		CATEGORYID() + ", " + CREATED() + " ) VALUES ( " + Number + "', " + Title + "', " + Alias + "', " +
		Content.replace("\r\n", "\n") + "', " + Key + "', " + Author + "', " + Bookid + "', " + Categoryid + ", " + TIMENOW() + ")";
}

QString AsUtils::SONG_UPDATE_SQL(QString Number, QString Title, QString Alias, QString Content, QString Key, QString Author, QString Songid)
{
	return "UPDATE " + TBL_SONGS() + " SET " + NUMBER() + "=" + Number + ", " + TITLE() + "='" + Title +
		"', " + ALIAS() + "='" + Alias + "', " + CONTENT() + "='" + Content + "', " + KEY() + "='" + Key + 
		"', " + AUTHOR() + "='" + Author + "', " + UPDATED() + "='" + TIMENOW() + "' WHERE " + SONGID() + "=" + Songid;
}

char* AsUtils::SONG_DELETE_SQL(QString Songid)
{
	QString SqlQuery = "DELETE FROM " + TBL_SONGS() + " WHERE " + SONGID() + "=" + Songid;
	QByteArray bar = SqlQuery.toLocal8Bit();
	return bar.data();
}

QString AsUtils::UPDATE_SETTINGS_SQL(QString Title, QString Value)
{
	return "UPDATE " + TBL_SETTINGS() + " SET " + CONTENT() + "='" + Value + "', " +
		UPDATED() + "='" + TIMENOW() + "' WHERE " + TITLE() + "='" + Title + "'";
}

QString AsUtils::SETTINGS_NAVI_SQL()
{
	QString SqlQuery = "INSERT INTO " + TBL_SETTINGS_NAVI() + "(" + ENABLED() + ", " + TITLE() + ", " + CONTENT() + 
		", " + EXTRA() + ", " + TAGS() + ") VALUES ";
	SqlQuery.append("('1', 'General Options', 'Essential preferences', 'general, overrall', NULL),");
	SqlQuery.append("('1', 'App Font Options', 'Font Management for the app, preview, presentation', 'fonts, app', NULL),");
	SqlQuery.append("('1', 'Presentation Themes', 'Set your prefferred theme for presentation', 'projector, projection, presentation', NULL);");
	return SqlQuery;
}

QString AsUtils::SETTINGS_SQL()
{
	QString SqlQuery = "INSERT INTO " + TBL_SETTINGS() + "(" + TITLE() + ", " + CONTENT() + ", " + CREATED() + ") VALUES ";
	SqlQuery.append("('install_date', NULL, " + TIMENOW() + "),");
	SqlQuery.append("('app_user', NULL, " + TIMENOW() + "),");
	SqlQuery.append("('theme', '3', " + TIMENOW() + "),");
	SqlQuery.append("('language', 'English', " + TIMENOW() + "),");
	SqlQuery.append("('show_startpage', '1', " + TIMENOW() + "),");
	SqlQuery.append("('selected_book', NULL, " + TIMENOW() + "),");
	SqlQuery.append("('selected_song', NULL, " + TIMENOW() + "),");
	SqlQuery.append("('list_font_bold', '0', " + TIMENOW() + "),");
	SqlQuery.append("('general_font_size', '18', " + TIMENOW() + "),");
	SqlQuery.append("('general_font_type', 'Trebuchet MS', " + TIMENOW() + "),");
	SqlQuery.append("('general_font_bold','1'," + TIMENOW() + "),");
	SqlQuery.append("('preview_font_size', '20', " + TIMENOW() + "),");
	SqlQuery.append("('preview_font_type', 'Trebuchet MS', " + TIMENOW() + "),");
	SqlQuery.append("('preview_font_bold', '0', " + TIMENOW() + "),");
	SqlQuery.append("('present_font_size', '40', " + TIMENOW() + "),");
	SqlQuery.append("('present_font_type', 'Trebuchet MS', " + TIMENOW() + "),");
	SqlQuery.append("('present_font_bold', '1', " + TIMENOW() + "),");
	SqlQuery.append("('edit_mode', '0', " + TIMENOW() + "),");
	SqlQuery.append("('last_window_startup', '1', " + TIMENOW() + "),");
	SqlQuery.append("('last_window_width', '14085', " + TIMENOW() + "),");
	SqlQuery.append("('last_window_height', '8655', " + TIMENOW() + "),");
	SqlQuery.append("('tablet_mode', '0', " + TIMENOW() + "),");
	SqlQuery.append("('show_help_first', '1', " + TIMENOW() + "),");
	SqlQuery.append("('current_song', NULL, " + TIMENOW() + "),");
	SqlQuery.append("('search_allbooks', '1', " + TIMENOW() + "),");
	SqlQuery.append("('app_theme', '2', " + TIMENOW() + ");");
	SqlQuery.append("('dark_mode', '0', " + TIMENOW() + ");");
	return SqlQuery;
}
QString AsUtils::VERSE_SELECT_SQL(QString Language)
{
	return "SELECT " +
		TBL_VERSES() + Language + "." + VERSEID() + ", " +
		TBL_VERSES() + Language + "." + TITLE() + ", " +
		TBL_VERSES() + Language + "." + CONTENT() + ", " +
		TBL_VERSES() + Language + "." + HIGHLIGHT() + ", " +
		TBL_VERSES() + Language + "." + NOTES() +
		" FROM " + TBL_VERSES() + Language;
}

QString AsUtils::VERSE_SEARCH_SQL(QString Search, QString Language)
{
	QString WhereQry = "";

	QString SqlQuery = VERSE_SELECT_SQL(Language);

	if (!Search.isEmpty())
	{
		WhereQry.append(TITLE() + " LIKE '%" + Search + "%' ");
		WhereQry.append(" OR " + CONTENT() + " LIKE '%" + Search + "%'");
	}

	SqlQuery.append((WhereQry.isEmpty() ? "" : " WHERE " + WhereQry) + " ORDER BY " + VERSEID() + " ASC");
	return SqlQuery;
}

QString AsUtils::VERSE_READING_SQL(QString Book, QString Chapter, QString Language)
{
	QString VersesTbl = TBL_VERSES() + Language;

	QString SqlQuery = "SELECT " +
		VersesTbl + "." + VERSEID() + ", " +
		VersesTbl + "." + TITLE() + ", " +
		VersesTbl + "." + CONTENT() + ", " +
		TBL_BOOKS() + "." + CHAPTERS() + ", " +
		TBL_BOOKS() + "." + SWAHILI() + ", " +
		VersesTbl + "." + HIGHLIGHT() + ", " +
		VersesTbl + "." + NOTES() +
		" FROM " + VersesTbl;
	
	SqlQuery.append(" INNER JOIN " + TBL_BOOKS() + " ON " + 
		TBL_BOOKS() + "." + TITLE() + "='" + Book + "'");
	SqlQuery.append(" WHERE " + VersesTbl + "." + TITLE() + "='" + Book + " " + Chapter + "'");
	SqlQuery.append(" ORDER BY " + VersesTbl + "." + VERSEID() + " ASC");

	return SqlQuery;
}
