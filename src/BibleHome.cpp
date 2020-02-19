#include "Application.h"
#include "BibleHome.h"
#include "ui_BibleHome.h"

#include "AsBase.h"
#include "AsUtils.h"
#include "sqlite.h"
#include "RunSql.h"
#include "sqlitetablemodel.h"

#include <QWhatsThis>
#include <QMessageBox>
#include <limits>
#include <QStandardItemModel>
#include <QObject>
#include "AsItem.h"
#include "AsDelegate.h"
#include "BibleAbout.h"
#include "BiblePreferences.h"
#include "BiblePresent.h"
#include "BibleTutorial.h"

bool isReady, isReady1, isDarkMode, isReadingBold;
int home_fontgen, home_fontprev, home_fonttype, chapters, reading_theme;
QString language, book, chapter, verse;
std::vector<QString> histories, home_fonts, home_sets, list_items, list_titles;

QFont HomeFontReading, HomeFontGeneral;

BibleHome::BibleHome(QWidget* parent) : QMainWindow(parent), ui(new Ui::BibleHome)
{
    ui->setupUi(this);
    ui->SplitterMain->setStretchFactor(1, 3);
	isReady = isReady1 = false;
    this->setWindowTitle(qApp->applicationName() + " v" + qApp->applicationVersion());

	ui->CmbLanguages->addItem("English");
	ui->CmbLanguages->addItem("Swahili");
	language = "english";

    if (QFile::exists(AsUtils::DB_FILE())) HomeInit();
    else
    {
        QDir().mkdir("Data");
        db.create(AsUtils::DB_FILE());
        AsBase::InitialDbOps();
        HomeInit();
    }
}

void BibleHome::HomeInit()
{
    home_sets = AsBase::AppSettings();
    ReloadSettings();
    SearchBible("");
	chapter = "1";
	verse = "1";
	book = "Genesis";
	ui->TxtTitle->setText(book + " " + chapter);
	OpenReading();
	for (int c=1; c < chapters; c++) ui->CmbChapter->addItem(QString::number(c));
	isReady = isReady1 = true;
}

void BibleHome::ReloadSettings()
{
    isReadingBold = AsBase::isTrue(home_sets[13].toInt());

    home_fontgen = home_sets[8].toInt();
    home_fontprev = home_sets[11].toInt();

    HomeFontGeneral.setFamily(home_sets[9]);
    HomeFontGeneral.setPointSize(home_fontgen);
    HomeFontGeneral.setBold(AsBase::isTrue(home_sets[10].toInt()));
    HomeFontGeneral.setWeight(50);

    HomeFontReading.setFamily(home_sets[12]);
    HomeFontReading.setPointSize(home_fontprev);
    HomeFontReading.setBold(isReadingBold);
    HomeFontReading.setWeight(50);

    home_fonts.push_back("Arial");
    home_fonts.push_back("Calibri");
    home_fonts.push_back("Century Gothic");
    home_fonts.push_back("Comic Sans MS");
    home_fonts.push_back("Corbel");
    home_fonts.push_back("Courier New");
    home_fonts.push_back("Palatino");
    home_fonts.push_back("Linotype");
    home_fonts.push_back("Tahoma");
    home_fonts.push_back("Tempus Sans ITC");
    home_fonts.push_back("Times New Roman");
    home_fonts.push_back("Trebuchet MS");
    home_fonts.push_back("Verdana");

    if (home_sets[12] == "Arial") home_fonttype = 1;
    else if (home_sets[12] == "Calibri") home_fonttype = 2;
    else if (home_sets[12] == "Century Gothic") home_fonttype = 3;
    else if (home_sets[12] == "Comic Sans MS") home_fonttype = 4;
    else if (home_sets[12] == "Corbel") home_fonttype = 5;
    else if (home_sets[12] == "Courier New") home_fonttype = 6;
    else if (home_sets[12] == "Palatino") home_fonttype = 7;
    else if (home_sets[12] == "Linotype") home_fonttype = 8;
    else if (home_sets[12] == "Tahoma") home_fonttype = 9;
    else if (home_sets[12] == "Tempus Sans ITC") home_fonttype = 10;
    else if (home_sets[12] == "Trebuchet MS") home_fonttype = 11;
    else if (home_sets[12] == "Verdana") home_fonttype = 12;

	reading_theme = home_sets[25].toInt();
    ReloadControls();
}

void BibleHome::SetTheme()
{
	switch (reading_theme)
	{
	case 1:
		ui->TxtContent->setStyleSheet("* { background-color: #000000; color: #FFFFFF; }");
		break;

	case 2:
		ui->TxtContent->setStyleSheet("* { background-color: #FFFFFF; color: #000000; }");
		break;

	case 3:
		ui->TxtContent->setStyleSheet("* { background-color: #A9A9A9; color: #FFFFFF; }");
		break;

	case 4:
		ui->TxtContent->setStyleSheet("* { background-color: #FFFFFF; color: #000000; }");
		break;

	case 5:
		ui->TxtContent->setStyleSheet("* { background-color: #0000FF; color: #FFFFFF; }");
		break;

	case 6:
		ui->TxtContent->setStyleSheet("* { background-color: #FFFFFF; color: #0000FF; }");
		break;

	case 7:
		ui->TxtContent->setStyleSheet("* { background-color: #00FF00; color: #FFFFFF; }");
		break;

	case 8:
		ui->TxtContent->setStyleSheet("* { background-color: #FFFFFF; color: #00FF00; }");
		break;

	case 9:
		ui->TxtContent->setStyleSheet("* { background-color: #FFA500; color: #FFFFFF; }");
		break;

	case 10:
		ui->TxtContent->setStyleSheet("* { background-color: #FFFFFF; color: #FFA500; }");
		break;

	case 11:
		ui->TxtContent->setStyleSheet("* { background-color: #FF0000; color: #FFFFFF; }");
		break;

	case 12:
		ui->TxtContent->setStyleSheet("* { background-color: #FFFFFF; color: #FF0000; }");
		break;

	case 13:
		ui->TxtContent->setStyleSheet("* { background-color: #000000; color: #FFFF00; }");
		break;

	case 14:
		ui->TxtContent->setStyleSheet("* { background-color: #FFFF00; color: #000000; }");
		break;

	case 15:
		ui->TxtContent->setStyleSheet("* { background-color: #000000; color: #FFFFFF; }");
		break;

	}
}

void BibleHome::ReloadControls()
{
    ui->TxtSearch->setFont(HomeFontGeneral);
    ui->CmbLanguages->setFont(HomeFontGeneral);
    ui->TxtContent->setFont(HomeFontReading);
	SetTheme();
}

void BibleHome::FontChange()
{
    switch (home_fonttype)
    {
        case 12:
            home_fonttype = 1;
            HomeFontReading.setFamily(home_fonts[home_fonttype]);
            AsBase::SetOption("reading_font_type", home_fonts[home_fonttype]);
            ReloadControls();

        default:
            home_fonttype = home_fonttype + 1;
            HomeFontReading.setFamily(home_fonts[home_fonttype]);
            AsBase::SetOption("reading_font_type", home_fonts[home_fonttype]);
            ReloadControls();
    }
}

void BibleHome::FontSmaller()
{
    if ((home_fontprev - 2) > 9)
    {
        home_fontprev = home_fontprev - 2;
        HomeFontReading.setPointSize(home_fontprev);
        AsBase::SetOption("reading_font_size", QString::number(home_fontprev));
        ReloadControls();
    }
}

void BibleHome::FontBigger()
{
    if ((home_fontprev + 2) < 51)
    {
        home_fontprev = home_fontprev + 2;
        HomeFontReading.setPointSize(home_fontprev);
        AsBase::SetOption("reading_font_size", QString::number(home_fontprev));
        ReloadControls();
    }
}

void BibleHome::FontBold()
{
    if (isReadingBold) isReadingBold = false;
    else isReadingBold = true;
    HomeFontReading.setBold(isReadingBold);
    ReloadControls();
}

void BibleHome::on_TxtSearch_textChanged(const QString& SearchStr)
{
    SearchBible(SearchStr);
}

void BibleHome::on_CmbLanguages_currentIndexChanged(const QString &arg1)
{
	language = arg1.toLower();
	if (isReady) GotoReading();
}

void BibleHome::on_ChkNewTestament_stateChanged(int arg1)
{
    SearchBible(ui->TxtSearch->text());
}

void BibleHome::on_ChkOldTestament_stateChanged(int arg1)
{
    SearchBible(ui->TxtSearch->text());
}

void BibleHome::SearchBible(QString SearchStr)
{
    QStringList strList;
    QStandardItemModel* listModel = new QStandardItemModel();
    bool SearchOT, SearchNT;

	int bookcount = 0, versecount = 0;

	SearchOT = ui->ChkOldTestament->isChecked();
	SearchNT = ui->ChkNewTestament->isChecked();
	ui->LblResult->hide();

	QString Results = "";

	if (list_items.size() > 0)
	{
		list_items.clear();
		list_titles.clear();
	}

    sqlite3* db;
    char* err_msg = NULL, ** qryResult = NULL;
    int row, col, rc = sqlite3_open_v2(AsUtils::APP_DB(), &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);

    QByteArray bar1 = AsUtils::BOOK_SEARCH_SQL(SearchStr, SearchOT, SearchNT).toLocal8Bit();
    char* sqlQuery1 = bar1.data();
	
    rc = sqlite3_get_table(db, sqlQuery1, &qryResult, &row, &col, &err_msg);

    for (int i = 1; i < row + 1; i++)
    {
		QString bookid = *(qryResult + i * col + 0);

        QStandardItem* listItem = new QStandardItem;
        AsItem listing;
        //listing.image = "res/settings.png";
        QString testament = "OT";
        QString tstStr = *(qryResult + i * col + 1);
        QString title1 = *(qryResult + i * col + 3);
        QString title2 = *(qryResult + i * col + 5);

		list_items.push_back(bookid);
		list_titles.push_back(title1 + " 1");

        if (tstStr == "1") testament = "OT";
        else if (tstStr == "2") testament = "NT";

        listing.title = bookid + "# " + title1.toUpper() + " (" + *(qryResult + i * col + 2) + ")";
        listing.content = testament + "; " + title2 + " (SW); " + *(qryResult + i * col + 4) + " Chapters;";

        listItem->setData(QVariant::fromValue(listing), Qt::UserRole + 1);
        listModel->appendRow(listItem);
        bookcount++;
    }

	if (SearchOT && !SearchNT) Results = QString::number(bookcount) + " books in the Old Testament";
	else if (!SearchOT && SearchNT) Results = QString::number(bookcount) + " books in the New Testament";
	else Results = QString::number(bookcount) + " books in the Bible";

	if (!SearchStr.isEmpty())
	{
		QByteArray bar2 = AsUtils::VERSE_SEARCH_SQL(SearchStr, language).toLocal8Bit();

		char* sqlQuery2 = bar2.data();
		
		rc = sqlite3_get_table(db, sqlQuery2, &qryResult, &row, &col, &err_msg);

		for (int k = 1; k < row + 1; k++)
		{
			QString verseid = *(qryResult + k * col + 0);

			QStandardItem* listItem = new QStandardItem;
			AsItem listing;
			QString title = *(qryResult + k * col + 1);
			QString content = *(qryResult + k * col + 2);

			list_items.push_back(verseid);
			list_titles.push_back(title);

			listing.title = title.toUpper();
			listing.content = content;

			listItem->setData(QVariant::fromValue(listing), Qt::UserRole + 1);
			listModel->appendRow(listItem);
			versecount++;
		}

	}

    AsDelegate* homeDelegate = new AsDelegate(this);
    ui->LstResults->setItemDelegate(homeDelegate);
    ui->LstResults->setModel(listModel);
    ui->LstResults->setSpacing(1);
    ui->LstResults->setStyleSheet("* { background-color: #D3D3D3; }");

    sqlite3_free_table(qryResult);
    sqlite3_close(db);

	ui->LblResult->setText(Results);
	if (bookcount > 0 || versecount > 0)
	{
		ui->LstResults->setCurrentIndex(listModel->index(0, 0));
	}
}

void BibleHome::on_LstResults_clicked(const QModelIndex& index)
{
	GetReading(index);
}

void BibleHome::on_CmbChapter_currentIndexChanged(const QString &arg1)
{
	if (isReady1) GotoReading();
}

void BibleHome::GetReading(const QModelIndex& index)
{
	isReady1 = false;
	int item = index.row();
	QString item_title = list_titles[item];
	AsBase::SetOption("current_song", item_title);

	QStringList bookstr = item_title.split(" ");

	switch (bookstr.size())
	{
		case 2:
			book = bookstr[0];
			chapter = bookstr[1];
			break;

		case 3:
			book = bookstr[0] + " " + bookstr[1];
			chapter = bookstr[2];
			break;

		case 4:
			book = bookstr[0] + " " + bookstr[1] + " " + bookstr[2];
			chapter = bookstr[3];
			break;

		default:
			book = item_title;
			chapter = "1";
			break;
	}

	ui->TxtTitle->setText(book + " " + chapter);

	ui->CmbChapter->clear();
	ui->CmbVerse->clear();
	
	OpenReading();
	for (int c = 1; c < chapters; c++) ui->CmbChapter->addItem(QString::number(c));
	isReady1 = true;
}

void BibleHome::GotoReading()
{
	chapter = ui->CmbChapter->currentText();
	verse = "1";
	ui->TxtTitle->setText(book + " " + chapter);
	OpenReading();
}

void BibleHome::OpenReading()
{
	sqlite3* db;
	char* err_msg = NULL, ** qryResult = NULL;
	int row, col, rc = sqlite3_open_v2(AsUtils::APP_DB(), &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);

	QByteArray bar2 = AsUtils::VERSE_READING_SQL(book, chapter, language).toLocal8Bit();
	char* sqlQuery2 = bar2.data();

	rc = sqlite3_get_table(db, sqlQuery2, &qryResult, &row, &col, &err_msg);

	QString Scripture = "";
	int rows = row + 1;

	for (int r = 1; r < rows; r++)
	{
		QString verseid = *(qryResult + r * col + 0);
		QString reading = *(qryResult + r * col + 2);

		if (r != rows) Scripture.append(reading + "\n");

		ui->CmbVerse->addItem(QString::number(r));
	}
	ui->TxtContent->setPlainText(Scripture);

	QString book_chapters = *(qryResult + 1 * col + 3);
	QString book_swahili = *(qryResult + 1 * col + 4);

	if (language == "swahili")
	{
		ui->TxtTitle->setText(book_swahili + " " + chapter);
	}
	chapters = book_chapters.toInt();

	sqlite3_free_table(qryResult);
	sqlite3_close(db);
}

void BibleHome::on_actionPrevious_triggered()
{
	if (isReady1 && ui->CmbChapter->currentIndex() > 0)
	{
		ui->CmbChapter->setCurrentIndex(ui->CmbChapter->currentIndex() - 1);
		GotoReading();
	}
}

void BibleHome::on_actionNext_triggered()
{
	if (isReady1 && ui->CmbChapter->currentIndex() < chapters)
	{
		ui->CmbChapter->setCurrentIndex(ui->CmbChapter->currentIndex() + 1);
		GotoReading();
	}
}

void BibleHome::on_actionBold_Text_triggered()
{
	FontBold();
}

void BibleHome::on_actionChange_Font_triggered()
{
	FontChange();
}

void BibleHome::on_actionSmaller_Font_triggered()
{
	FontSmaller();
}

void BibleHome::on_actionBigger_Font_triggered()
{
	FontBigger();
}

void BibleHome::on_actionFont_triggered()
{
	FontChange();
}

void BibleHome::on_actionBold_triggered()
{
	FontBold();
}

void BibleHome::on_actionSmaller_triggered()
{
	FontSmaller();
}

void BibleHome::on_actionBigger_triggered()
{
	FontBigger();
}

void BibleHome::on_actionPreferences_triggered()
{
	BiblePreferences options(this);
	options.exec();
}

void BibleHome::on_actionTutorial_triggered()
{
    BibleTutorial tutorial(this);
	tutorial.exec();
}

void BibleHome::on_actionAbout_triggered()
{
	BibleAbout about(this);
	about.exec();
}

void BibleHome::on_actionManage_Settings_triggered()
{
	BiblePreferences options(this);
	options.exec();
}

void BibleHome::on_actionTheme_triggered()
{
	switch (reading_theme)
	{
		case 15:
			reading_theme = 1;
			AsBase::SetOption("app_theme", QString::number(reading_theme));

		default:
			reading_theme = reading_theme + 1;
			AsBase::SetOption("app_theme", QString::number(reading_theme));
	}
	SetTheme();
}

void BibleHome::on_actionExit_triggered()
{
	this->close();
}

/*
void BibleHome::on_actionDarkMode_triggered()
{
    if (isDarkMode)
    {
        isDarkMode = false;
        AsBase::SetOption("dark_mode", "0");
    }
    else
    {
        isDarkMode = true;
        AsBase::SetOption("dark_mode", "1");
    }
    ui->ChkNewTestament->setChecked(isDarkMode);
    ui->actionDarkMode->setChecked(isDarkMode);
    SetDarkMode();
}

void BibleHome::on_actionSearchAll_triggered()
{
if (searchAll)
{
searchAll = false;
AsBase::SetOption("search_allbooks", "0");
}
else
{
searchAll = true;
AsBase::SetOption("search_allbooks", "1");
}
ui->ChkOldTestament->setChecked(searchAll);
ui->actionSearchAll->setChecked(searchAll);
}

void BibleHome::on_LstResults_activated(const QModelIndex& index)
{
    OpenScriptureReading(index);
}

void BibleHome::on_actionPresent_triggered()
{
    BiblePresent* present = new BiblePresent();
    present->showFullScreen();
}

void BibleHome::on_actionCheck_Updates_triggered()
{

}

void BibleHome::on_actionContribute_triggered()
{

}

void BibleHome::on_actionDonate_triggered()
{

}

void BibleHome::on_actionReset_Settings_triggered()
{
    AsBase::ResetSettings();
    this->close();
}


void BibleHome::on_actionTutorial_triggered()
{
    BibleTutorial* tutorial = new BibleTutorial();
    tutorial->show();
}

void BibleHome::on_actionSearch_triggered()
{
    ui->TxtSearch->setFocus();
}
*/

BibleHome::~BibleHome()
{
    delete ui;
}

