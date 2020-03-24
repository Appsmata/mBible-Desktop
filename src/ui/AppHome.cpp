#include "Application.h"
#include "ui/AppHome.h"
#include "ui_AppHome.h"

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
#include "ui/AppAbout.h"
#include "ui/AppPreferences.h"
#include "ui/AppPresent.h"
#include "ui/AppTutorial.h"

bool isReady, isReady1, isDarkMode, isReadingBold, isPresentation;
int home_fontgen, home_fontprev, home_fonttype, chapters, reading_theme;
QString language, book, chapter, verse;
std::vector<QString> histories, home_fonts, present_font, home_sets, list_items, list_titles;
QFont HomeFontReading, HomeFontGeneral, HomeFontPresent;

AppHome::AppHome(QWidget* parent) : QMainWindow(parent), ui(new Ui::AppHome)
{
    ui->setupUi(this);
    ui->SplitterMain->setStretchFactor(1, 3);
	isReady = isReady1 = false;
    this->setWindowTitle(qApp->applicationName() + " v" + qApp->applicationVersion());

	ui->CmbLanguages->addItem("English");
	ui->CmbLanguages->addItem("Swahili");

    if (QFile::exists(AsUtils::DbNameQstr())) HomeInit();
    else
    {
        QDir().mkdir("data");
        db.create(AsUtils::DbNameQstr());
        AsBase::InitialDbOps();
        HomeInit();
    }
}

void AppHome::HomeInit()
{
    home_sets = AsBase::AppSettings();
    ReloadSettings();
    SearchBible("");
	OpenReading();
	for (int c=1; c < chapters + 1; c++) ui->CmbChapter->addItem(QString::number(c));
	isReady = isReady1 = true;

	ui->LstResults->setStyleSheet("* { background-color: #D3D3D3; }");
}

void AppHome::ReloadSettings()
{
    isReadingBold = AsBase::isTrue(home_sets[13].toInt());

	verse = "1";
	book = home_sets[5];
	chapter = home_sets[6];
	language = home_sets[3].toLower();
	ui->TxtTitle->setText(book + " " + chapter);

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

void AppHome::ReloadControls()
{
    ui->TxtSearch->setFont(HomeFontGeneral);
    ui->CmbLanguages->setFont(HomeFontGeneral);
    ui->TxtContent->setFont(HomeFontReading);
}

void AppHome::FontChange()
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

void AppHome::FontSmaller()
{
    if ((home_fontprev - 2) > 9)
    {
        home_fontprev = home_fontprev - 2;
        HomeFontReading.setPointSize(home_fontprev);
        AsBase::SetOption("reading_font_size", QString::number(home_fontprev));
        ReloadControls();
    }
}

void AppHome::FontBigger()
{
    if ((home_fontprev + 2) < 51)
    {
        home_fontprev = home_fontprev + 2;
        HomeFontReading.setPointSize(home_fontprev);
        AsBase::SetOption("reading_font_size", QString::number(home_fontprev));
        ReloadControls();
    }
}

void AppHome::FontBold()
{
    if (isReadingBold) isReadingBold = false;
    else isReadingBold = true;
    HomeFontReading.setBold(isReadingBold);
    ReloadControls();
}

void AppHome::on_TxtSearch_textChanged(const QString& SearchStr)
{
    SearchBible(SearchStr);
}

void AppHome::on_CmbLanguages_currentIndexChanged(const QString &arg1)
{
	AsBase::SetOption("language", arg1);
	language = arg1.toLower();
	if (isReady) GotoReading();
}

void AppHome::on_ChkNewTestament_stateChanged(int arg1)
{
    SearchBible(ui->TxtSearch->text());
}

void AppHome::on_ChkOldTestament_stateChanged(int arg1)
{
    SearchBible(ui->TxtSearch->text());
}

void AppHome::SearchBible(QString SearchStr)
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
    int row, col, rc = sqlite3_open_v2(AsUtils::DbNameChar(), &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);

    QByteArray bar1 = AsUtils::BookSearchSql(SearchStr, SearchOT, SearchNT).toLocal8Bit();
    char* sqlQuery1 = bar1.data();

	//ui->TxtContent->setPlainText(AsUtils::BookSearchSql(SearchStr, SearchOT, SearchNT));
	
	if (rc == SQLITE_OK)
	{
		rc = sqlite3_get_table(db, sqlQuery1, &qryResult, &row, &col, &err_msg);

		if (rc == SQLITE_OK)
		{
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
				QByteArray bar2 = AsUtils::VerseSearchSql(SearchStr, language).toLocal8Bit();

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

			sqlite3_free_table(qryResult);
			sqlite3_close(db);

			ui->LblResult->setText(Results);
			if (bookcount > 0 || versecount > 0)
			{
				ui->LstResults->setCurrentIndex(listModel->index(0, 0));
			}
		}
	}
}

void AppHome::on_LstResults_clicked(const QModelIndex& index)
{
	GetReading(index);
}

void AppHome::on_CmbChapter_currentIndexChanged(const QString &arg1)
{
	if (isReady1) GotoReading();
}

void AppHome::GetReading(const QModelIndex& index)
{
	isReady1 = false;
	int item = index.row();
	QString item_title = list_titles[item];
	AsBase::SetOption("selected_book", item_title);
	AsBase::SetOption("selected_chapter", item_title);

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

	AsBase::SetOption("selected_book", book);
	AsBase::SetOption("selected_chapter", chapter);

	ui->TxtTitle->setText(book + " " + chapter);

	ui->CmbChapter->clear();
	ui->CmbVerse->clear();
	
	OpenReading();
	for (int c = 1; c < chapters + 1; c++) ui->CmbChapter->addItem(QString::number(c));
	isReady1 = true;
}

void AppHome::GotoReading()
{
	chapter = ui->CmbChapter->currentText();
	verse = "1";
	ui->TxtTitle->setText(book + " " + chapter);
	OpenReading();
}

void AppHome::OpenReading()
{
	sqlite3* db;
	char* err_msg = NULL, ** qryResult = NULL;
	int row, col, rc = sqlite3_open_v2(AsUtils::DbNameChar(), &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);

	if (rc == SQLITE_OK)
	{
		QByteArray bar2 = AsUtils::VerseReadingSql(book, chapter, language).toLocal8Bit();
		char* sqlQuery2 = bar2.data();

		//ui->TxtContent->setPlainText(AsUtils::VerseReadingSql(book, chapter, language));
		rc = sqlite3_get_table(db, sqlQuery2, &qryResult, &row, &col, &err_msg);

		QString Scripture = "";
		int rows = row + 1;

		if (rc == SQLITE_OK)
		{
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
	}
}

void AppHome::NextChapter()
{
	if (isReady1 && ui->CmbChapter->currentIndex() > 0)
	{
		ui->CmbChapter->setCurrentIndex(ui->CmbChapter->currentIndex() - 1);
		GotoReading();
	}
}

void AppHome::PreviousChapter()
{
	if (isReady1 && ui->CmbChapter->currentIndex() < chapters)
	{
		ui->CmbChapter->setCurrentIndex(ui->CmbChapter->currentIndex() + 1);
		GotoReading();
	}
}

void AppHome::on_actionPrevious_triggered()
{
	PreviousChapter();
}

void AppHome::on_actionPrevious_2_triggered()
{
	PreviousChapter();
}

void AppHome::on_actionNext_triggered()
{
	NextChapter();	
}

void AppHome::on_actionNext_2_triggered()
{
	NextChapter();
}

void AppHome::on_actionBold_Text_triggered()
{
	FontBold();
}

void AppHome::on_actionChange_Font_triggered()
{
	FontChange();
}

void AppHome::on_actionSmaller_Font_triggered()
{
	FontSmaller();
}

void AppHome::on_actionBigger_Font_triggered()
{
	FontBigger();
}

void AppHome::on_actionFont_triggered()
{
	FontChange();
}

void AppHome::on_actionBold_triggered()
{
	FontBold();
}

void AppHome::on_actionSmaller_triggered()
{
	FontSmaller();
}

void AppHome::on_actionBigger_triggered()
{
	FontBigger();
}

void AppHome::on_actionPreferences_triggered()
{
	AppPreferences options(this);
	options.exec();
}

void AppHome::on_actionTutorial_triggered()
{
	AppTutorial tutorial(this);
	tutorial.exec();
}

void AppHome::on_actionAbout_triggered()
{
	AppAbout about(this);
	about.exec();
}

void AppHome::on_actionManage_Settings_triggered()
{
	AppPreferences options(this);
	options.exec();
}

void AppHome::on_actionPresent_triggered()
{
	AppPresent* present = new AppPresent();
	present->showFullScreen();;
}

void AppHome::on_actionPresent_2_triggered()
{
	AppPresent* present = new AppPresent();
	present->showFullScreen();
}

void AppHome::on_actionFont1_triggered()
{
	FontChange();
}

void AppHome::on_actionExit_triggered()
{
	this->close();
}

AppHome::~AppHome()
{
    delete ui;
}

