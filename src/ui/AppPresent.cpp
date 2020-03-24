#include "ui/AppPresent.h"
#include "ui_AppPresent.h"

#include "AsBase.h"
#include "AsUtils.h"
#include "Application.h"

#include "sqlite.h"
#include "RunSql.h"
#include "sqlitetablemodel.h"

std::vector<QString> view_set, view_fonts;
int mainfont, smallfont, view_font_size, view_fonttype, view_theme, view_chapters;
QString view_language, view_book, view_chapter, view_verse, view_fonty;
bool isViewReady, isBold;
QFont PresentFont;

AppPresent::AppPresent(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AppPresent)
{
    ui->setupUi(this);
	SetUpStuff();
	
	PresentReading();
	for (int c = 1; c < view_chapters; c++) ui->CmbChapterNo->addItem(QString::number(c));
	isViewReady = true;

	SetTheme();
	ui->TxtScripture->setFocus();
}

void AppPresent::SetUpStuff()
{
	view_fonts.push_back("Arial");
	view_fonts.push_back("Calibri");
	view_fonts.push_back("Century Gothic");
	view_fonts.push_back("Comic Sans MS");
	view_fonts.push_back("Corbel");
	view_fonts.push_back("Courier New");
	view_fonts.push_back("Palatino");
	view_fonts.push_back("Linotype");
	view_fonts.push_back("Tahoma");
	view_fonts.push_back("Tempus Sans ITC");
	view_fonts.push_back("Times New Roman");
	view_fonts.push_back("Trebuchet MS");
	view_fonts.push_back("Verdana");

	view_set = AsBase::AppSettings();
	ui->LblApp->setText(qApp->applicationName() + " " + qApp->applicationVersion() + " - " + view_set[1]);
	ReloadSettings();

	if (!AsBase::isTrue(view_set[21].toInt()))
	{
		ui->BtnClose->hide();
	}

	if (view_set[12] == "Arial") view_fonttype = 1;
	else if (view_set[12] == "Calibri") view_fonttype = 2;
	else if (view_set[12] == "Century Gothic") view_fonttype = 3;
	else if (view_set[12] == "Comic Sans MS") view_fonttype = 4;
	else if (view_set[12] == "Corbel") view_fonttype = 5;
	else if (view_set[12] == "Courier New") view_fonttype = 6;
	else if (view_set[12] == "Palatino") view_fonttype = 7;
	else if (view_set[12] == "Linotype") view_fonttype = 8;
	else if (view_set[12] == "Tahoma") view_fonttype = 9;
	else if (view_set[12] == "Tempus Sans ITC") view_fonttype = 10;
	else if (view_set[12] == "Trebuchet MS") view_fonttype = 11;
	else if (view_set[12] == "Verdana") view_fonttype = 12;

	view_theme = view_set[25].toInt();
}

void AppPresent::ReloadSettings()
{
	view_font_size = view_set[14].toInt();

	view_verse = "1";
	view_book = view_set[5];
	view_chapter = view_set[6];
	view_language = view_set[3].toLower();
	ui->TxtReading->setText(view_book + " " + view_chapter);

	PresentFont.setFamily(view_set[15]);
	PresentFont.setPointSize(view_font_size);
	PresentFont.setBold(AsBase::isTrue(view_set[16].toInt()));
	PresentFont.setWeight(50);

	ReloadControls();	
}

void AppPresent::ReloadControls()
{
	ui->TxtReading->setFont(PresentFont);
	ui->TxtScripture->setFont(PresentFont);
}

void AppPresent::SetTheme()
{
	switch (view_theme)
	{
	case 1:
		ui->WidgetCentral->setStyleSheet("* { background-color: #000000; color: #FFFFFF; }");
		ui->statusbar->setStyleSheet("* { background-color: #000000; color: #FFFFFF; }");
		break;

	case 2:
		ui->WidgetCentral->setStyleSheet("* { background-color: #FFFFFF; color: #000000; }");
		ui->statusbar->setStyleSheet("* { background-color: #FFFFFF; color: #000000; }");
		break;

	case 3:
		ui->WidgetCentral->setStyleSheet("* { background-color: #A9A9A9; color: #FFFFFF; }");
		ui->statusbar->setStyleSheet("* { background-color: #A9A9A9; color: #FFFFFF; }");
		break;

	case 4:
		ui->WidgetCentral->setStyleSheet("* { background-color: #FFFFFF; color: #000000; }");
		ui->statusbar->setStyleSheet("* { background-color: #FFFFFF; color: #000000; }");
		break;

	case 5:
		ui->WidgetCentral->setStyleSheet("* { background-color: #0000FF; color: #FFFFFF; }");
		ui->statusbar->setStyleSheet("* { background-color: #0000FF; color: #FFFFFF; }");
		break;

	case 6:
		ui->WidgetCentral->setStyleSheet("* { background-color: #FFFFFF; color: #0000FF; }");
		ui->statusbar->setStyleSheet("* { background-color: #FFFFFF; color: #0000FF; }");
		break;

	case 7:
		ui->WidgetCentral->setStyleSheet("* { background-color: #00FF00; color: #FFFFFF; }");
		ui->statusbar->setStyleSheet("* { background-color: #00FF00; color: #FFFFFF; }");
		break;

	case 8:
		ui->WidgetCentral->setStyleSheet("* { background-color: #FFFFFF; color: #00FF00; }");
		ui->statusbar->setStyleSheet("* { background-color: #FFFFFF; color: #00FF00; }");
		break;

	case 9:
		ui->WidgetCentral->setStyleSheet("* { background-color: #FFA500; color: #FFFFFF; }");
		ui->statusbar->setStyleSheet("* { background-color: #FFA500; color: #FFFFFF; }");
		break;

	case 10:
		ui->WidgetCentral->setStyleSheet("* { background-color: #FFFFFF; color: #FFA500; }");
		ui->statusbar->setStyleSheet("* { background-color: #FFFFFF; color: #FFA500; }");
		break;

	case 11:
		ui->WidgetCentral->setStyleSheet("* { background-color: #FF0000; color: #FFFFFF; }");
		ui->statusbar->setStyleSheet("* { background-color: #FF0000; color: #FFFFFF; }");
		break;

	case 12:
		ui->WidgetCentral->setStyleSheet("* { background-color: #FFFFFF; color: #FF0000; }");
		ui->statusbar->setStyleSheet("* { background-color: #FFFFFF; color: #FF0000; }");
		break;

	case 13:
		ui->WidgetCentral->setStyleSheet("* { background-color: #000000; color: #FFFF00; }");
		ui->statusbar->setStyleSheet("* { background-color: #000000; color: #FFFF00; }");
		break;

	case 14:
		ui->WidgetCentral->setStyleSheet("* { background-color: #FFFF00; color: #000000; }");
		ui->statusbar->setStyleSheet("* { background-color: #FFFF00; color: #000000; }");
		break;

	case 15:
		ui->WidgetCentral->setStyleSheet("* { background-color: #000000; color: #FFFFFF; }");
		ui->statusbar->setStyleSheet("* { background-color: #000000; color: #FFFFFF; }");
		break;

	}
}

void AppPresent::PresentReading()
{
	sqlite3* db;
	char* err_msg = NULL, ** qryResult = NULL;
	int row, col, rc = sqlite3_open_v2(AsUtils::DbNameChar(), &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);

	QByteArray bar2 = AsUtils::VerseReadingSql(view_book, view_chapter, view_language).toLocal8Bit();
	char* sqlQuery2 = bar2.data();

	if (rc == SQLITE_OK)
	{
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

				ui->CmbVerseNo->addItem(QString::number(r));
			}
			ui->TxtScripture->setPlainText(Scripture);

			QString book_chapters = *(qryResult + 1 * col + 3);
			QString book_swahili = *(qryResult + 1 * col + 4);

			if (view_language == "swahili")
			{
				ui->TxtReading->setText(book_swahili + " " + view_chapter);
			}
			view_chapters = book_chapters.toInt();

			sqlite3_free_table(qryResult);
			sqlite3_close(db);
		}
	}
}

AppPresent::~AppPresent()
{
    delete ui;
}

void AppPresent::on_actionClose_triggered()
{
    this->close();
}

void AppPresent::on_BtnClose_clicked()
{
    this->close();
}

void AppPresent::on_actionLeft_triggered()
{
	if ((view_font_size - 2) > 9)
	{
		view_font_size = view_font_size - 2;
		PresentFont.setPointSize(view_font_size);
		AsBase::SetOption("present_font_size", QString::number(view_font_size));
		ReloadControls();
	}
}

void AppPresent::on_actionRight_triggered()
{
	if ((view_font_size + 2) < 99)
	{
		view_font_size = view_font_size + 2;
		PresentFont.setPointSize(view_font_size);
		AsBase::SetOption("present_font_size", QString::number(view_font_size));
		ReloadControls();
	}
}

void AppPresent::on_actionBigger_triggered()
{
	if ((view_font_size + 2) < 99)
	{
		view_font_size = view_font_size + 2;
		PresentFont.setPointSize(view_font_size);
		AsBase::SetOption("present_font_size", QString::number(view_font_size));
		ReloadControls();
	}
}

void AppPresent::on_actionSmaller_triggered()
{
	if ((view_font_size - 2) > 9)
	{
		view_font_size = view_font_size - 2;
		PresentFont.setPointSize(view_font_size);
		AsBase::SetOption("present_font_size", QString::number(view_font_size));
		ReloadControls();
	}
}

void AppPresent::on_actionFont_triggered()
{
	switch (view_fonttype)
	{
		case 12:
			view_fonttype = 1;
			PresentFont.setFamily(view_fonts[view_fonttype]);
			AsBase::SetOption("present_font_type", view_fonts[view_fonttype]);
			ReloadControls();
                        break;

		default:
			view_fonttype = view_fonttype + 1;
			PresentFont.setFamily(view_fonts[view_fonttype]);
			AsBase::SetOption("present_font_type", view_fonts[view_fonttype]);
			ReloadControls();
                        break;
	}
}

void AppPresent::on_actionBold_triggered()
{
	if (isBold) isBold = false;
	else isBold = true;
	PresentFont.setBold(isBold);
	ReloadControls();
}

void AppPresent::on_actionTheme_triggered()
{
	switch (view_theme)
	{
		case 15:
			view_theme = 1;
			AsBase::SetOption("app_theme", QString::number(view_theme));
                        break;

		default:
			view_theme = view_theme + 1;
			AsBase::SetOption("app_theme", QString::number(view_theme));
                        break;
	}
	SetTheme();
}


void AppPresent::on_CmbChapterNo_currentIndexChanged(const QString &arg1)
{   
	if (isViewReady) PresentReading();
}

void AppPresent::on_actionPrevious_triggered()
{
	if (isViewReady && ui->CmbChapterNo->currentIndex() < view_chapters)
	{
		ui->CmbChapterNo->setCurrentIndex(ui->CmbChapterNo->currentIndex() + 1);
		PresentReading();
	}
}

void AppPresent::on_actionNext_triggered()
{
	if (isViewReady && ui->CmbChapterNo->currentIndex() > 0)
	{
		ui->CmbChapterNo->setCurrentIndex(ui->CmbChapterNo->currentIndex() - 1);
		PresentReading();
	}
}
