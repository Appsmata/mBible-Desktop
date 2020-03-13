#ifndef ASUTILS_H
#define ASUTILS_H

#include <QtCore>

class AsUtils
{
public:
	static QString DB_FILE();
    static char const *APP_DB();

	static QString TBL_BOOKS();
	static QString TBL_HISTORY();
	static QString TBL_SETTINGS();
	static QString TBL_SETTINGS_NAVI();
	static QString TBL_SONGS();
	
	
	static QString BOOKID();
	static QString CATEGORYID();
	static QString ENABLED();
	static QString TITLE();
	static QString CONTENT();
	static QString QCOUNT();
	static QString POSITION();
	static QString BACKPATH();
	static QString NOTES();
	static QString CREATED();
	static QString UPDATED();

	static QString ENTRY();
	static QString TYPE();
	static QString ITEM();
	static QString EXTRA();

	static QString SETTINGID();

	static QString NAVID();
	static QString TAGS();

	static QString SONGID();
	static QString POSTID();
	static QString NUMBER();
	static QString BASETYPE();
	static QString ALIAS();
	static QString VIEWS();
	static QString KEY();
	static QString ISFAV();
	static QString AUTHOR();
	static QString WHAT();
	static QString WHEN();
	static QString WHERE();
	static QString WHO();
	static QString NETTHUMBS();
	static QString ACOUNT();
	static QString USERID();

	static QString TIMENOW();

	static QString CREATE_BOOKS_TABLE_SQL();
	static QString CREATE_HISTORY_TABLE_SQL();
	static QString CREATE_SETTINGS_TABLE_SQL();
	static QString CREATE_SETTINGS_NAVI_TABLE_SQL();
	static QString CREATE_SONGS_TABLE_SQL();

	static QString BOOK_SELECT_SQL();
	static QString BOOK_LIST_SQL(QString State);
	static QString BOOK_SINGLE_SQL(QString Book);
	static QString BOOK_SEARCH_SQL(QString Search);
	static QString BOOK_INSERT_SQL(QString Title, QString Category, QString Tags, QString Content, QString Position, QString Songs);
	static QString BOOK_UPDATE_SQL(QString Bookid, QString Title, QString Tags, QString Content, QString Songs);
	static QString BOOK_SONGS_COUNT_SQL(QString Bookid, QString Songs);
	static char* BOOK_DELETE_SQL(QString Bookid);

    static QString HISTORY_SELECT_SQL();

	static QString SETTINGS_SQL();
	static char* SETTINGS_SELECT_SQL();
	static QString SETTINGS_NAVI_SQL();
	static QString SETTINGS_NAVI_SELECT_SQL(QString Search);

	static QString SONG_SELECT_SQL();
	static QString SONG_SEARCH_SQL(QString SearchStr, QString Bookid, bool SearchAll);
	static QString SONG_SINGLE_SQL(QString Song);
	static QString SONG_INSERT_SQL(QString Number, QString Title, QString Alias, QString Content, QString Key, QString Author, QString Bookid, QString Categoryid);
	static QString SONG_UPDATE_SQL(QString Number, QString Title, QString Alias, QString Content, QString Key, QString Author, QString Songid);
    static char const *SONG_DELETE_SQL(QString Songid);

	static QString UPDATE_SETTINGS_SQL(QString Title, QString Value);
};

#endif
