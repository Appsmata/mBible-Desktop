#include "AsBase.h"
#include "AsUtils.h"
#include "Application.h"
#include "BiblePreferences.h"
#include "ui_BiblePreferences.h"
#include "sqlite.h"
#include "RunSql.h"
#include "sqlitetablemodel.h"
#include <QStandardItemModel>
#include <QObject>

#include "AsItem.h"
#include "AsDelegate.h"

char* pref_db = "Data/mBible.db";
int fontgeneral, fontpreview, fontpresent;
std::vector<QString> pref_sets, navigations, languages, pref_fonts;
QFont PrefFontGeneral, PrefFontReading, PrefFontPresent;

BiblePreferences::BiblePreferences(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::BiblePreferences)
{
    ui->setupUi(this);
	GetSettings();
	ReloadSettings();
	SetUpStuff();
}

bool BiblePreferences::GetSettings()
{
	bool retval = false;
	sqlite3* songsDb;
	char* err_msg = NULL, ** qryResult = NULL;
	int row, col, rc = sqlite3_open_v2(pref_db, &songsDb, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);

	char* sqlQuery = "SELECT content FROM settings ORDER BY settingid";

	if (rc == SQLITE_OK)
	{
		rc = sqlite3_get_table(songsDb, sqlQuery, &qryResult, &row, &col, &err_msg);

		for (int i = 1; i < row + 1; i++)
		{
			pref_sets.push_back(*(qryResult + i * col + 0));
		}
		sqlite3_free_table(qryResult);
		sqlite3_close(songsDb);
		retval = true;
	}

	return retval;
}

void BiblePreferences::ReloadSettings()
{
	fontgeneral = pref_sets[8].toInt();
	fontpreview = pref_sets[11].toInt();
	fontpresent = pref_sets[14].toInt();

	ui->BtnTabletMode->setChecked(AsBase::isTrue(pref_sets[21].toInt()));
	ui->BtnSearchCriteria->setChecked(AsBase::isTrue(pref_sets[24].toInt()));
	ui->BtnGeneralAppFont->setChecked(AsBase::isTrue(pref_sets[10].toInt()));
	ui->BtnScriptureReadingFont->setChecked(AsBase::isTrue(pref_sets[13].toInt()));
	ui->BtnScripturePresentFont->setChecked(AsBase::isTrue(pref_sets[16].toInt()));

	ui->CmbLanguage->setCurrentIndex(AsBase::setCmbValue(languages, pref_sets[3]));
	ui->CmbGeneralAppFont->setCurrentIndex(AsBase::setCmbValue(pref_fonts, pref_sets[9]));
	ui->CmbScriptureReadingFont->setCurrentIndex(AsBase::setCmbValue(pref_fonts, pref_sets[12]));
	ui->CmbScripturePresentFont->setCurrentIndex(AsBase::setCmbValue(pref_fonts, pref_sets[15]));

	ui->TxtYourName->setText(pref_sets[1]);

	PrefFontGeneral.setFamily(pref_sets[9]);
	PrefFontGeneral.setPointSize(fontgeneral);
	PrefFontGeneral.setBold(AsBase::isTrue(pref_sets[10].toInt()));
	PrefFontGeneral.setWeight(50);

	PrefFontReading.setFamily(pref_sets[12]);
	PrefFontReading.setPointSize(fontpreview);
	PrefFontReading.setBold(AsBase::isTrue(pref_sets[13].toInt()));
	PrefFontReading.setWeight(50);

	PrefFontPresent.setFamily(pref_sets[15]);
	PrefFontPresent.setPointSize(fontpresent);
	PrefFontPresent.setBold(AsBase::isTrue(pref_sets[16].toInt()));
	PrefFontPresent.setWeight(50);

	ui->GrpGeneralAppFont->setTitle(" App General Font " + pref_sets[8] + " ");
	ui->GrpScriptureReadingFont->setTitle(" Scripture Reading Font " + pref_sets[11] + " ");
	ui->GrpScripturePresentFont->setTitle(" Scripture Presentation Font " + pref_sets[14] + " ");

	ui->SldGeneralAppFont->setValue(fontgeneral);
	ui->SldScriptureReadingFont->setValue(fontpreview);
	ui->SldScripturePresentFont->setValue(fontpresent);

	SelectedTheme(pref_sets[25].toInt());
}

void BiblePreferences::SetUpStuff()
{
	LoadNavigation("");
	languages.clear();
	ui->CmbLanguage->clear();

	languages.push_back("English");
	languages.push_back("Swahili");

	for (int l = 0; l < languages.size(); l++)
	{
		ui->CmbLanguage->addItem(languages[l]);
	}

	pref_fonts.clear();
	ui->CmbGeneralAppFont->clear();
	ui->CmbScriptureReadingFont->clear();
	ui->CmbScripturePresentFont->clear();

	pref_fonts.push_back("Arial");
	pref_fonts.push_back("Calibri");
	pref_fonts.push_back("Century Gothic");
	pref_fonts.push_back("Comic Sans MS");
	pref_fonts.push_back("Corbel");
	pref_fonts.push_back("Courier New");
	pref_fonts.push_back("Palatino");
	pref_fonts.push_back("Linotype");
	pref_fonts.push_back("Tahoma");
	pref_fonts.push_back("Tempus Sans ITC");
	pref_fonts.push_back("Times New Roman");
	pref_fonts.push_back("Trebuchet MS");
	pref_fonts.push_back("Verdana");

	for (int f = 0; f < pref_fonts.size(); f++)
	{
		ui->CmbGeneralAppFont->addItem(pref_fonts[f]);
		ui->CmbScriptureReadingFont->addItem(pref_fonts[f]);
		ui->CmbScripturePresentFont->addItem(pref_fonts[f]);
	}
}

void BiblePreferences::SelectedTheme(int theme)
{
	switch (theme)
	{
		case 1:
			ui->BtnTheme1->setChecked(true);
			ui->BtnTheme2->setChecked(false);
			ui->BtnTheme3->setChecked(false);
			ui->BtnTheme4->setChecked(false);
			ui->BtnTheme5->setChecked(false);
			ui->BtnTheme6->setChecked(false);
			ui->BtnTheme7->setChecked(false);
			ui->BtnTheme8->setChecked(false);
			ui->BtnTheme9->setChecked(false);
			ui->BtnTheme10->setChecked(false);
			ui->BtnTheme11->setChecked(false);
			ui->BtnTheme12->setChecked(false);
			ui->BtnTheme13->setChecked(false);
			ui->BtnTheme14->setChecked(false);
			ui->BtnTheme15->setChecked(false);
			break;

		case 2:
			ui->BtnTheme1->setChecked(false);
			ui->BtnTheme2->setChecked(true);
			ui->BtnTheme3->setChecked(false);
			ui->BtnTheme4->setChecked(false);
			ui->BtnTheme5->setChecked(false);
			ui->BtnTheme6->setChecked(false);
			ui->BtnTheme7->setChecked(false);
			ui->BtnTheme8->setChecked(false);
			ui->BtnTheme9->setChecked(false);
			ui->BtnTheme10->setChecked(false);
			ui->BtnTheme11->setChecked(false);
			ui->BtnTheme12->setChecked(false);
			ui->BtnTheme13->setChecked(false);
			ui->BtnTheme14->setChecked(false);
			ui->BtnTheme15->setChecked(false);
			break;

		case 3:
			ui->BtnTheme1->setChecked(false);
			ui->BtnTheme2->setChecked(false);
			ui->BtnTheme3->setChecked(true);
			ui->BtnTheme4->setChecked(false);
			ui->BtnTheme5->setChecked(false);
			ui->BtnTheme6->setChecked(false);
			ui->BtnTheme7->setChecked(false);
			ui->BtnTheme8->setChecked(false);
			ui->BtnTheme9->setChecked(false);
			ui->BtnTheme10->setChecked(false);
			ui->BtnTheme11->setChecked(false);
			ui->BtnTheme12->setChecked(false);
			ui->BtnTheme13->setChecked(false);
			ui->BtnTheme14->setChecked(false);
			ui->BtnTheme15->setChecked(false);
			break;

		case 4:
			ui->BtnTheme1->setChecked(false);
			ui->BtnTheme2->setChecked(false);
			ui->BtnTheme3->setChecked(false);
			ui->BtnTheme4->setChecked(true);
			ui->BtnTheme5->setChecked(false);
			ui->BtnTheme6->setChecked(false);
			ui->BtnTheme7->setChecked(false);
			ui->BtnTheme8->setChecked(false);
			ui->BtnTheme9->setChecked(false);
			ui->BtnTheme10->setChecked(false);
			ui->BtnTheme11->setChecked(false);
			ui->BtnTheme12->setChecked(false);
			ui->BtnTheme13->setChecked(false);
			ui->BtnTheme14->setChecked(false);
			ui->BtnTheme15->setChecked(false);
			break;

		case 5:
			ui->BtnTheme1->setChecked(false);
			ui->BtnTheme2->setChecked(false);
			ui->BtnTheme3->setChecked(false);
			ui->BtnTheme4->setChecked(false);
			ui->BtnTheme5->setChecked(true);
			ui->BtnTheme6->setChecked(false);
			ui->BtnTheme7->setChecked(false);
			ui->BtnTheme8->setChecked(false);
			ui->BtnTheme9->setChecked(false);
			ui->BtnTheme10->setChecked(false);
			ui->BtnTheme11->setChecked(false);
			ui->BtnTheme12->setChecked(false);
			ui->BtnTheme13->setChecked(false);
			ui->BtnTheme14->setChecked(false);
			ui->BtnTheme15->setChecked(false);
			break;

		case 6:
			ui->BtnTheme1->setChecked(false);
			ui->BtnTheme2->setChecked(false);
			ui->BtnTheme3->setChecked(false);
			ui->BtnTheme4->setChecked(false);
			ui->BtnTheme5->setChecked(false);
			ui->BtnTheme6->setChecked(true);
			ui->BtnTheme7->setChecked(false);
			ui->BtnTheme8->setChecked(false);
			ui->BtnTheme9->setChecked(false);
			ui->BtnTheme10->setChecked(false);
			ui->BtnTheme11->setChecked(false);
			ui->BtnTheme12->setChecked(false);
			ui->BtnTheme13->setChecked(false);
			ui->BtnTheme14->setChecked(false);
			ui->BtnTheme15->setChecked(false);
			break;

		case 7:
			ui->BtnTheme1->setChecked(false);
			ui->BtnTheme2->setChecked(false);
			ui->BtnTheme3->setChecked(false);
			ui->BtnTheme4->setChecked(false);
			ui->BtnTheme5->setChecked(false);
			ui->BtnTheme6->setChecked(false);
			ui->BtnTheme7->setChecked(true);
			ui->BtnTheme8->setChecked(false);
			ui->BtnTheme9->setChecked(false);
			ui->BtnTheme10->setChecked(false);
			ui->BtnTheme11->setChecked(false);
			ui->BtnTheme12->setChecked(false);
			ui->BtnTheme13->setChecked(false);
			ui->BtnTheme14->setChecked(false);
			ui->BtnTheme15->setChecked(false);
			break;

		case 8:
			ui->BtnTheme1->setChecked(false);
			ui->BtnTheme2->setChecked(false);
			ui->BtnTheme3->setChecked(false);
			ui->BtnTheme4->setChecked(false);
			ui->BtnTheme5->setChecked(false);
			ui->BtnTheme6->setChecked(false);
			ui->BtnTheme7->setChecked(false);
			ui->BtnTheme8->setChecked(true);
			ui->BtnTheme9->setChecked(false);
			ui->BtnTheme10->setChecked(false);
			ui->BtnTheme11->setChecked(false);
			ui->BtnTheme12->setChecked(false);
			ui->BtnTheme13->setChecked(false);
			ui->BtnTheme14->setChecked(false);
			ui->BtnTheme15->setChecked(false);
			break;

		case 9:
			ui->BtnTheme1->setChecked(false);
			ui->BtnTheme2->setChecked(false);
			ui->BtnTheme3->setChecked(false);
			ui->BtnTheme4->setChecked(false);
			ui->BtnTheme5->setChecked(false);
			ui->BtnTheme6->setChecked(false);
			ui->BtnTheme7->setChecked(false);
			ui->BtnTheme8->setChecked(false);
			ui->BtnTheme9->setChecked(true);
			ui->BtnTheme10->setChecked(false);
			ui->BtnTheme11->setChecked(false);
			ui->BtnTheme12->setChecked(false);
			ui->BtnTheme13->setChecked(false);
			ui->BtnTheme14->setChecked(false);
			ui->BtnTheme15->setChecked(false);
			break;

		case 10:
			ui->BtnTheme1->setChecked(false);
			ui->BtnTheme2->setChecked(false);
			ui->BtnTheme3->setChecked(false);
			ui->BtnTheme4->setChecked(false);
			ui->BtnTheme5->setChecked(false);
			ui->BtnTheme6->setChecked(false);
			ui->BtnTheme7->setChecked(false);
			ui->BtnTheme8->setChecked(false);
			ui->BtnTheme9->setChecked(false);
			ui->BtnTheme10->setChecked(true);
			ui->BtnTheme11->setChecked(false);
			ui->BtnTheme12->setChecked(false);
			ui->BtnTheme13->setChecked(false);
			ui->BtnTheme14->setChecked(false);
			ui->BtnTheme15->setChecked(false);
			break;

		case 11:
			ui->BtnTheme1->setChecked(false);
			ui->BtnTheme2->setChecked(false);
			ui->BtnTheme3->setChecked(false);
			ui->BtnTheme4->setChecked(false);
			ui->BtnTheme5->setChecked(false);
			ui->BtnTheme6->setChecked(false);
			ui->BtnTheme7->setChecked(false);
			ui->BtnTheme8->setChecked(false);
			ui->BtnTheme9->setChecked(false);
			ui->BtnTheme10->setChecked(false);
			ui->BtnTheme11->setChecked(true);
			ui->BtnTheme12->setChecked(false);
			ui->BtnTheme13->setChecked(false);
			ui->BtnTheme14->setChecked(false);
			ui->BtnTheme15->setChecked(false);
			break;

		case 12:
			ui->BtnTheme1->setChecked(false);
			ui->BtnTheme2->setChecked(false);
			ui->BtnTheme3->setChecked(false);
			ui->BtnTheme4->setChecked(false);
			ui->BtnTheme5->setChecked(false);
			ui->BtnTheme6->setChecked(false);
			ui->BtnTheme7->setChecked(false);
			ui->BtnTheme8->setChecked(false);
			ui->BtnTheme9->setChecked(false);
			ui->BtnTheme10->setChecked(false);
			ui->BtnTheme11->setChecked(false);
			ui->BtnTheme12->setChecked(true);
			ui->BtnTheme13->setChecked(false);
			ui->BtnTheme14->setChecked(false);
			ui->BtnTheme15->setChecked(false);
			break;

		case 13:
			ui->BtnTheme1->setChecked(false);
			ui->BtnTheme2->setChecked(false);
			ui->BtnTheme3->setChecked(false);
			ui->BtnTheme4->setChecked(false);
			ui->BtnTheme5->setChecked(false);
			ui->BtnTheme6->setChecked(false);
			ui->BtnTheme7->setChecked(false);
			ui->BtnTheme8->setChecked(false);
			ui->BtnTheme9->setChecked(false);
			ui->BtnTheme10->setChecked(false);
			ui->BtnTheme11->setChecked(false);
			ui->BtnTheme12->setChecked(false);
			ui->BtnTheme13->setChecked(true);
			ui->BtnTheme14->setChecked(false);
			ui->BtnTheme15->setChecked(false);
			break;

		case 14:
			ui->BtnTheme1->setChecked(false);
			ui->BtnTheme2->setChecked(false);
			ui->BtnTheme3->setChecked(false);
			ui->BtnTheme4->setChecked(false);
			ui->BtnTheme5->setChecked(false);
			ui->BtnTheme6->setChecked(false);
			ui->BtnTheme7->setChecked(false);
			ui->BtnTheme8->setChecked(false);
			ui->BtnTheme9->setChecked(false);
			ui->BtnTheme10->setChecked(false);
			ui->BtnTheme11->setChecked(false);
			ui->BtnTheme12->setChecked(false);
			ui->BtnTheme13->setChecked(false);
			ui->BtnTheme14->setChecked(true);
			ui->BtnTheme15->setChecked(false);
			break;

		case 15:
			ui->BtnTheme1->setChecked(false);
			ui->BtnTheme2->setChecked(false);
			ui->BtnTheme3->setChecked(false);
			ui->BtnTheme4->setChecked(false);
			ui->BtnTheme5->setChecked(false);
			ui->BtnTheme6->setChecked(false);
			ui->BtnTheme7->setChecked(false);
			ui->BtnTheme8->setChecked(false);
			ui->BtnTheme9->setChecked(false);
			ui->BtnTheme10->setChecked(false);
			ui->BtnTheme11->setChecked(false);
			ui->BtnTheme12->setChecked(false);
			ui->BtnTheme13->setChecked(false);
			ui->BtnTheme14->setChecked(false);
			ui->BtnTheme15->setChecked(true);
			break;
	}
}

void BiblePreferences::LoadNavigation(QString searchstr)
{
	QStringList strList;

	QStandardItemModel* naviModel = new QStandardItemModel();

	if (navigations.size() > 0) navigations.clear();

	sqlite3* db;
	char* err_msg = NULL, ** qryResult = NULL;
	int row, col, rc = sqlite3_open_v2(pref_db, &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);

	QByteArray bar = AsUtils::SETTINGS_NAVI_SELECT_SQL(searchstr).toLocal8Bit();
	char* sqlQuery = bar.data();

	rc = sqlite3_get_table(db, sqlQuery, &qryResult, &row, &col, &err_msg);

	for (int i = 1; i < row + 1; i++)
	{
		navigations.push_back(*(qryResult + i * col + 0));

		QStandardItem* naviItem = new QStandardItem;
		AsItem navigation;
		navigation.image = "res/settings.png";
		navigation.title = *(qryResult + i * col + 2);
		navigation.content = *(qryResult + i * col + 3);

		naviItem->setData(QVariant::fromValue(navigation), Qt::UserRole + 1);
		naviModel->appendRow(naviItem);
	}

	AsDelegate* asDelegate = new AsDelegate(this);
	ui->LstNavigation->setItemDelegate(asDelegate);
	ui->LstNavigation->setModel(naviModel);
	ui->LstNavigation->setSpacing(1);
	ui->LstNavigation->setStyleSheet("* { background-color: #D3D3D3; }");

	sqlite3_free_table(qryResult);
	sqlite3_close(db);

	ui->LstNavigation->setCurrentIndex(naviModel->index(0, 0));
}

void BiblePreferences::OpenSelectedTab(const QModelIndex& index)
{
	int setTab = navigations[index.row()].toInt();
	switch (setTab)
	{
	case 1:
		ui->TabPage1->show();
		ui->TabPage2->hide();
		ui->TabPage3->hide();
		break;

	case 2:
		ui->TabPage1->hide();
		ui->TabPage2->show();
		ui->TabPage3->hide();
		break;

	case 3:
		ui->TabPage1->hide();
		ui->TabPage2->hide();
		ui->TabPage3->show();
		break;
	}
}

void BiblePreferences::ChangeGeneralFont(int newfont)
{
	PrefFontGeneral.setPointSize(newfont);
	ui->TxtSampleText->setFont(PrefFontGeneral);
	AsBase::SetOption("general_font_size", QString::number(newfont));
	ui->GrpGeneralAppFont->setTitle(" App General Font " + QString::number(newfont) + " ");
}

void BiblePreferences::ChangeReadingFont(int newfont)
{
	PrefFontReading.setPointSize(newfont);
	ui->TxtSampleText->setFont(PrefFontReading);
	AsBase::SetOption("preview_font_size", QString::number(newfont));
	ui->GrpScriptureReadingFont->setTitle(" Scripture Reading Font " + QString::number(newfont) + " ");
}

void BiblePreferences::ChangePresentFont(int newfont)
{
	PrefFontPresent.setPointSize(newfont);
	ui->TxtSampleText->setFont(PrefFontPresent);
	AsBase::SetOption("present_font_size", QString::number(newfont));
	ui->GrpScripturePresentFont->setTitle(" Scripture Presentation Font " + QString::number(newfont) + " ");
}

void BiblePreferences::on_TxtSearch_textChanged(const QString& searchstr)
{
	LoadNavigation(searchstr);
}

void BiblePreferences::on_LstNavigation_clicked(const QModelIndex& index)
{
	OpenSelectedTab(index);
}

void BiblePreferences::on_LstNavigation_doubleClicked(const QModelIndex& index)
{
	OpenSelectedTab(index);
}

void BiblePreferences::on_BtnTabletMode_clicked()
{
	AsBase::SetOption("tablet_mode", AsBase::booltoInt(ui->BtnTabletMode->isChecked()));
}

void BiblePreferences::on_BtnSearchCriteria_clicked()
{
	AsBase::SetOption("search_allbooks", AsBase::booltoInt(ui->BtnSearchCriteria->isChecked()));
}

void BiblePreferences::on_CmbLanguage_currentIndexChanged(int index)
{
	AsBase::SetOption("language", languages[index]);
}

void BiblePreferences::on_TxtYourName_textChanged(const QString& newname)
{
	AsBase::SetOption("app_user", newname);
}

void BiblePreferences::on_BtnDownGeneralAppFont_clicked()
{
	if ((fontgeneral - 2) > 9)
	{
		fontgeneral = fontgeneral - 2;
		ChangeGeneralFont(fontgeneral);
	}
}

void BiblePreferences::on_BtnUpGeneralAppFont_clicked()
{
	if ((fontgeneral + 2) < 51)
	{
		fontgeneral = fontgeneral + 2;
		ChangeGeneralFont(fontgeneral);
	}
}

void BiblePreferences::on_SldGeneralAppFont_valueChanged(int value)
{
	ChangeGeneralFont(value);
}

void BiblePreferences::on_CmbGeneralAppFont_currentIndexChanged(int index)
{
	QString newfont = pref_fonts[index];
	PrefFontGeneral.setFamily(newfont);
	ui->TxtSampleText->setFont(PrefFontGeneral);
	AsBase::SetOption("general_font_type", newfont);
}

void BiblePreferences::on_BtnGeneralAppFont_clicked()
{
	PrefFontGeneral.setBold(ui->BtnGeneralAppFont->isChecked());
	ui->TxtSampleText->setFont(PrefFontGeneral);
	AsBase::SetOption("general_font_bold", AsBase::booltoInt(ui->BtnGeneralAppFont->isChecked()));
}

void BiblePreferences::on_BtnDownScriptureReadingFont_clicked()
{
	if ((fontpreview - 2) > 9)
	{
		fontpreview = fontpreview - 2;
		//ChangeReadingFont(fontpreview);
	}
}

void BiblePreferences::on_BtnUpScriptureReadingFont_clicked()
{
	if ((fontpreview + 2) < 51)
	{
		fontpreview = fontpreview + 2;
		ChangeReadingFont(fontpreview);
	}
}

void BiblePreferences::on_SldScriptureReadingFont_valueChanged(int value)
{
	ChangeReadingFont(value);
}

void BiblePreferences::on_CmbScriptureReadingFont_currentIndexChanged(int index)
{
	QString newfont = pref_fonts[index];
	PrefFontReading.setFamily(newfont);
	ui->TxtSampleText->setFont(PrefFontReading);
	AsBase::SetOption("preview_font_type", newfont);
}

void BiblePreferences::on_BtnScriptureReadingFont_clicked()
{
	PrefFontReading.setBold(ui->BtnScriptureReadingFont->isChecked());
	ui->TxtSampleText->setFont(PrefFontReading);
	AsBase::SetOption("preview_font_bold", AsBase::booltoInt(ui->BtnScriptureReadingFont->isChecked()));
}

void BiblePreferences::on_BtnDownScripturePresentFont_clicked()
{
	if ((fontpresent - 2) > 9)
	{
		fontpresent = fontpresent - 2;
		ChangePresentFont(fontpresent);
	}
}

void BiblePreferences::on_BtnUpScripturePresentFont_clicked()
{
	if ((fontpresent + 2) < 99)
	{
		fontpresent = fontpresent + 2;
		ChangePresentFont(fontpresent);
	}
}

void BiblePreferences::on_SldScripturePresentFont_valueChanged(int value)
{
	ChangePresentFont(value);
}

void BiblePreferences::on_CmbScripturePresentFont_currentIndexChanged(int index)
{
	QString newfont = pref_fonts[index];
	PrefFontPresent.setFamily(newfont);
	ui->TxtSampleText->setFont(PrefFontPresent);
	AsBase::SetOption("present_font_type", newfont);
}

void BiblePreferences::on_BtnScripturePresentFont_clicked()
{
	PrefFontPresent.setBold(ui->BtnScripturePresentFont->isChecked());
	ui->TxtSampleText->setFont(PrefFontPresent);
	AsBase::SetOption("present_font_bold", AsBase::booltoInt(ui->BtnScripturePresentFont->isChecked()));
}

void BiblePreferences::on_BtnTheme1_clicked()
{
	AsBase::SetOption("app_theme", "1");
	SelectedTheme(1);
}

void BiblePreferences::on_BtnTheme2_clicked()
{
	AsBase::SetOption("app_theme", "2");
	SelectedTheme(2);
}

void BiblePreferences::on_BtnTheme3_clicked()
{
	AsBase::SetOption("app_theme", "3");
	SelectedTheme(3);
}

void BiblePreferences::on_BtnTheme4_clicked()
{
	AsBase::SetOption("app_theme", "4");
	SelectedTheme(4);
}

void BiblePreferences::on_BtnTheme5_clicked()
{
	AsBase::SetOption("app_theme", "5");
	SelectedTheme(5);
}

void BiblePreferences::on_BtnTheme6_clicked()
{
	AsBase::SetOption("app_theme", "6");
	SelectedTheme(6);
}

void BiblePreferences::on_BtnTheme7_clicked()
{
	AsBase::SetOption("app_theme", "7");
	SelectedTheme(7);
}

void BiblePreferences::on_BtnTheme8_clicked()
{
	AsBase::SetOption("app_theme", "8");
	SelectedTheme(8);
}

void BiblePreferences::on_BtnTheme9_clicked()
{
	AsBase::SetOption("app_theme", "9");
	SelectedTheme(9);
}

void BiblePreferences::on_BtnTheme10_clicked()
{
	AsBase::SetOption("app_theme", "10");
	SelectedTheme(10);
}

void BiblePreferences::on_BtnTheme11_clicked()
{
	AsBase::SetOption("app_theme", "11");
	SelectedTheme(11);
}

void BiblePreferences::on_BtnTheme12_clicked()
{
	AsBase::SetOption("app_theme", "12");
	SelectedTheme(12);
}

void BiblePreferences::on_BtnTheme13_clicked()
{
	AsBase::SetOption("app_theme", "13");
	SelectedTheme(13);
}

void BiblePreferences::on_BtnTheme14_clicked()
{
	AsBase::SetOption("app_theme", "14");
	SelectedTheme(14);
}

void BiblePreferences::on_BtnTheme15_clicked()
{
	AsBase::SetOption("app_theme", "15");
	SelectedTheme(15);
}

BiblePreferences::~BiblePreferences()
{
	delete ui;
}