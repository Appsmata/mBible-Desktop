#include "AsBase.h"
#include "AsUtils.h"
#include "BiblePresent.h"
#include "Application.h"
#include "ui_BiblePresent.h"

#include "sqlite.h"
#include "RunSql.h"
#include "sqlitetablemodel.h"

std::vector<QString> songverses1, songverses2, labels, view_set, view_fonts;
int this_book, this_song, slides, slideno, slideindex, mainfont, smallfont, view_font_size, view_fonttype, view_theme;
QString setsong, bookid, songid, number, title, alias, content, key, author, songbook, chorus, slide, view_fonty;
bool haschorus, isBold;
QFont PresentFont;
QIcon iconDownWhite, iconDownBlack, iconUpWhite, iconUpBlack;

BiblePresent::BiblePresent(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BiblePresent)
{
    ui->setupUi(this);
	SetUpStuff();
	
	this_song = view_set[23].toInt();
	PresentSong(view_set[23]);
	SetTheme();
}

void BiblePresent::SetUpStuff()
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

	iconDownWhite.addFile(QString::fromUtf8(":/Down_White.png"), QSize(), QIcon::Normal, QIcon::Off);
	iconDownBlack.addFile(QString::fromUtf8(":/Down_Black.png"), QSize(), QIcon::Normal, QIcon::Off);

	iconUpWhite.addFile(QString::fromUtf8(":/Up_White.png"), QSize(), QIcon::Normal, QIcon::Off);
	iconUpBlack.addFile(QString::fromUtf8(":/Up_Black.png"), QSize(), QIcon::Normal, QIcon::Off);

	view_set = AsBase::AppSettings();
	ui->LblApp->setText(qApp->applicationName() + " " + qApp->applicationVersion() + " - " + view_set[1]);
	ReloadSettings();

	if (!AsBase::isTrue(view_set[21].toInt()))
	{
		ui->BtnClose->hide();
	}
	ui->BtnDown->hide();
	ui->BtnUp->hide();

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

void BiblePresent::SetTheme()
{
	switch (view_theme)
	{
		case 1:
			ui->WidgetCentral->setStyleSheet("* { background-color: #000000; color: #FFFFFF; }");
			ui->statusbar->setStyleSheet("* { background-color: #000000; color: #FFFFFF; }");
			ui->BtnDown->setIcon(iconDownWhite);
			ui->BtnUp->setIcon(iconUpWhite);
			break;

		case 2:
			ui->WidgetCentral->setStyleSheet("* { background-color: #FFFFFF; color: #000000; }");
			ui->statusbar->setStyleSheet("* { background-color: #FFFFFF; color: #000000; }");
			ui->BtnDown->setIcon(iconDownBlack);
			ui->BtnUp->setIcon(iconUpBlack);
			break;

		case 3:
			ui->WidgetCentral->setStyleSheet("* { background-color: #A9A9A9; color: #FFFFFF; }");
			ui->statusbar->setStyleSheet("* { background-color: #A9A9A9; color: #FFFFFF; }");
			ui->BtnDown->setIcon(iconDownWhite);
			ui->BtnUp->setIcon(iconUpWhite);
			break;

		case 4:
			ui->WidgetCentral->setStyleSheet("* { background-color: #FFFFFF; color: #000000; }");
			ui->statusbar->setStyleSheet("* { background-color: #FFFFFF; color: #000000; }");
			ui->BtnDown->setIcon(iconDownBlack);
			ui->BtnUp->setIcon(iconUpBlack);
			break;

		case 5:
			ui->WidgetCentral->setStyleSheet("* { background-color: #0000FF; color: #FFFFFF; }");
			ui->statusbar->setStyleSheet("* { background-color: #0000FF; color: #FFFFFF; }");
			ui->BtnDown->setIcon(iconDownWhite);
			ui->BtnUp->setIcon(iconUpWhite);
			break;

		case 6:
			ui->WidgetCentral->setStyleSheet("* { background-color: #FFFFFF; color: #0000FF; }");
			ui->statusbar->setStyleSheet("* { background-color: #FFFFFF; color: #0000FF; }");
			ui->BtnDown->setIcon(iconDownBlack);
			ui->BtnUp->setIcon(iconUpBlack);
			break;

		case 7:
			ui->WidgetCentral->setStyleSheet("* { background-color: #00FF00; color: #FFFFFF; }");
			ui->statusbar->setStyleSheet("* { background-color: #00FF00; color: #FFFFFF; }");
			ui->BtnDown->setIcon(iconDownWhite);
			ui->BtnUp->setIcon(iconUpWhite);
			break;

		case 8:
			ui->WidgetCentral->setStyleSheet("* { background-color: #FFFFFF; color: #00FF00; }");
			ui->statusbar->setStyleSheet("* { background-color: #FFFFFF; color: #00FF00; }");
			ui->BtnDown->setIcon(iconDownBlack);
			ui->BtnUp->setIcon(iconUpBlack);
			break;

		case 9:
			ui->WidgetCentral->setStyleSheet("* { background-color: #FFA500; color: #FFFFFF; }");
			ui->statusbar->setStyleSheet("* { background-color: #FFA500; color: #FFFFFF; }");
			ui->BtnDown->setIcon(iconDownWhite);
			ui->BtnUp->setIcon(iconUpWhite);
			break;

		case 10:
			ui->WidgetCentral->setStyleSheet("* { background-color: #FFFFFF; color: #FFA500; }");
			ui->statusbar->setStyleSheet("* { background-color: #FFFFFF; color: #FFA500; }");
			ui->BtnDown->setIcon(iconDownBlack);
			ui->BtnUp->setIcon(iconUpBlack);
			break;

		case 11:
			ui->WidgetCentral->setStyleSheet("* { background-color: #FF0000; color: #FFFFFF; }");
			ui->statusbar->setStyleSheet("* { background-color: #FF0000; color: #FFFFFF; }");
			ui->BtnDown->setIcon(iconDownWhite);
			ui->BtnUp->setIcon(iconUpWhite);
			break;

		case 12:
			ui->WidgetCentral->setStyleSheet("* { background-color: #FFFFFF; color: #FF0000; }");
			ui->statusbar->setStyleSheet("* { background-color: #FFFFFF; color: #FF0000; }");
			ui->BtnDown->setIcon(iconDownBlack);
			ui->BtnUp->setIcon(iconUpBlack);
			break;

		case 13:
			ui->WidgetCentral->setStyleSheet("* { background-color: #000000; color: #FFFF00; }");
			ui->statusbar->setStyleSheet("* { background-color: #000000; color: #FFFF00; }");
			ui->BtnDown->setIcon(iconDownWhite);
			ui->BtnUp->setIcon(iconUpWhite);
			break;

		case 14:
			ui->WidgetCentral->setStyleSheet("* { background-color: #FFFF00; color: #000000; }");
			ui->statusbar->setStyleSheet("* { background-color: #FFFF00; color: #000000; }");
			ui->BtnDown->setIcon(iconDownBlack);
			ui->BtnUp->setIcon(iconUpBlack);
			break;

		case 15:
			ui->WidgetCentral->setStyleSheet("* { background-color: #000000; color: #FFFFFF; }");
			ui->statusbar->setStyleSheet("* { background-color: #000000; color: #FFFFFF; }");
			ui->BtnDown->setIcon(iconDownWhite);
			ui->BtnUp->setIcon(iconUpWhite);
			break;

	}
}

void BiblePresent::ReloadSettings()
{
	view_font_size = view_set[14].toInt();

	PresentFont.setFamily(view_set[15]);
	PresentFont.setPointSize(view_font_size);
	PresentFont.setBold(AsBase::isTrue(view_set[16].toInt()));
	PresentFont.setWeight(50);

	ReloadControls();	
}

void BiblePresent::ReloadControls()
{
	//ui->LblKey->setFont(PresentFont);
	ui->LblTitle->setFont(PresentFont);
	//ui->LblSongInfo->setFont(PresentFont);
	//ui->LblVerse->setFont(PresentFont);
	ui->LblContent->setFont(PresentFont);
}

void BiblePresent::PresentSong(QString setsongid)
{
	slides = 0;
	if (songverses1.size() > 0) songverses1.clear();
	if (songverses2.size() > 0) songverses2.clear();

	sqlite3* songsDb;
	char* err_msg = NULL, ** qryResult = NULL;
	int row, col, rc = sqlite3_open_v2(AsUtils::APP_DB(), &songsDb, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
	
	QByteArray bar = AsUtils::SONG_SINGLE_SQL(setsongid).toLocal8Bit();
	char* sqlQuery = bar.data();
	rc = sqlite3_get_table(songsDb, sqlQuery, &qryResult, &row, &col, &err_msg);

	if (rc == SQLITE_OK)
	{
		number = *(qryResult + 1 * col + 2);
		title = number + ". " + *(qryResult + 1 * col + 4);
		alias = *(qryResult + 1 * col + 3);
		content = *(qryResult + 1 * col + 6);
		key = *(qryResult + 1 * col + 7);
		author = *(qryResult + 1 * col + 8);
		songbook = number + "# " + *(qryResult + 1 * col + 12);

		sqlite3_free_table(qryResult);
		sqlite3_close(songsDb);

		ContentPrepare();
	}
}

void BiblePresent::ContentPrepare()
{
	if (content.contains("CHORUS")) haschorus = true;
	else haschorus = false;

	QStringList tokens = content.split("\\n\\n");

	if (tokens.length() > 1)
	{
		for (int i = 0; i < tokens.length(); i++)
		{
			QString token = tokens[i];
			if (haschorus)
			{
				if (token.contains("CHORUS")) chorus = token.replace("CHORUS\\n", "");
				else songverses1.push_back(token);
			}
			else songverses2.push_back(token);
		}
	}
	
	if (haschorus)
	{
		int k = 1;
		for (std::vector<QString>::iterator i = songverses1.begin(); i != songverses1.end(); ++i) 
		{
			songverses2.push_back(*i);
			songverses2.push_back(chorus);
			slides = slides + 2;

			QString label = "VERSE " + QString::number(k);
			label.append(" / " + QString::number(songverses1.size()));
			labels.push_back(label);
			labels.push_back("CHORUS ");
			k++;
		}
	}
	else slides = songverses2.size();
	slideindex = 0;
	SetPresentation();
}

void BiblePresent::SetPresentation()
{
	slideno = slideindex + 1;
	slide = songverses2[slideindex];
	ui->LblTitle->setText(AsBase::ReplaceView(title));
	ui->LblContent->setText(AsBase::ReplaceView(slide));
	ui->LblKey->setText(key);
	ui->LblAuthor->setText(author);
	ui->LblSongInfo->setText(songbook);
	ui->LblVerse->setText(labels[slideindex]);

	if (slideindex == 0)
	{
		ui->BtnDown->show();
		ui->LblBottom->show();
		ui->BtnUp->hide();
	}

	else if (slideindex == (slides - 1))
	{
		ui->BtnDown->hide();
		ui->LblBottom->show();
		ui->BtnUp->show();
	}

	else
	{
		ui->BtnDown->show();
		ui->LblBottom->hide();
		ui->BtnUp->show();
	}
}

BiblePresent::~BiblePresent()
{
    delete ui;
}

void BiblePresent::on_actionClose_triggered()
{
    this->close();
}

void BiblePresent::on_BtnClose_clicked()
{
    this->close();
}

void BiblePresent::on_actionLeft_triggered()
{
	if ((view_font_size - 2) > 9)
	{
		view_font_size = view_font_size - 2;
		PresentFont.setPointSize(view_font_size);
		AsBase::SetOption("present_font_size", QString::number(view_font_size));
		ReloadControls();
	}
}

void BiblePresent::on_actionRight_triggered()
{
	if ((view_font_size + 2) < 99)
	{
		view_font_size = view_font_size + 2;
		PresentFont.setPointSize(view_font_size);
		AsBase::SetOption("present_font_size", QString::number(view_font_size));
		ReloadControls();
	}
}

void BiblePresent::on_actionBigger_triggered()
{
	if ((view_font_size + 2) < 99)
	{
		view_font_size = view_font_size + 2;
		PresentFont.setPointSize(view_font_size);
		AsBase::SetOption("present_font_size", QString::number(view_font_size));
		ReloadControls();
	}
}

void BiblePresent::on_actionSmaller_triggered()
{
	if ((view_font_size - 2) > 9)
	{
		view_font_size = view_font_size - 2;
		PresentFont.setPointSize(view_font_size);
		AsBase::SetOption("present_font_size", QString::number(view_font_size));
		ReloadControls();
	}
}

void BiblePresent::on_actionFont_triggered()
{
	switch (view_fonttype)
	{
		case 12:
			view_fonttype = 1;
			PresentFont.setFamily(view_fonts[view_fonttype]);
			AsBase::SetOption("present_font_type", view_fonts[view_fonttype]);
			ReloadControls();

		default:
			view_fonttype = view_fonttype + 1;
			PresentFont.setFamily(view_fonts[view_fonttype]);
			AsBase::SetOption("present_font_type", view_fonts[view_fonttype]);
			ReloadControls();
	}
}

void BiblePresent::on_actionBold_triggered()
{
	if (isBold) isBold = false;
	else isBold = true;
	PresentFont.setBold(isBold);
	ReloadControls();
}

void BiblePresent::on_actionTheme_triggered()
{
	switch (view_theme)
	{
		case 15:
			view_theme = 1;
			AsBase::SetOption("app_theme", QString::number(view_theme));

		default:
			view_theme = view_theme + 1;
			AsBase::SetOption("app_theme", QString::number(view_theme));
	}
	SetTheme();
}

void BiblePresent::on_actionChorus_triggered()
{

}

void BiblePresent::on_actionUp_triggered()
{
	if (slideindex != 0)
	{
		slideindex = slideindex - 1;
		SetPresentation();
	}
}

void BiblePresent::on_actionDown_triggered()
{
	if (slideindex != (slides - 1))
	{
		slideindex = slideindex + 1;
		SetPresentation();
	}
}

void BiblePresent::on_BtnUp_clicked()
{
	if (slideindex != 0)
	{
		slideindex = slideindex - 1;
		SetPresentation();
	}
}

void BiblePresent::on_BtnDown_clicked()
{
	if (slideindex != (slides - 1))
	{
		slideindex = slideindex + 1;
		SetPresentation();
	}
}

