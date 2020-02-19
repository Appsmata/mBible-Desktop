#ifndef BIBLEPREFERENCES_H
#define BIBLEPREFERENCES_H

#include <QDialog>
#include <QModelIndex>

class QStandardItemModel;

namespace Ui {
class BiblePreferences;
}

class BiblePreferences : public QDialog
{
    Q_OBJECT

public:
    explicit BiblePreferences(QWidget *parent = nullptr);
    ~BiblePreferences();

private slots:
    void SelectedTheme(int theme);
    bool GetSettings();
    void ReloadSettings();
    void SetUpStuff();
    void LoadNavigation(QString searchstr);
    void OpenSelectedTab(const QModelIndex& index);

    void ChangeGeneralFont(int newfont);
    void ChangeReadingFont(int newfont);
    void ChangePresentFont(int newfont);

    void on_LstNavigation_clicked(const QModelIndex& index);
    void on_LstNavigation_doubleClicked(const QModelIndex& index);
    void on_TxtSearch_textChanged(const QString& arg1);

    void on_BtnTabletMode_clicked();
    void on_BtnSearchCriteria_clicked();
    void on_CmbLanguage_currentIndexChanged(int index);
    void on_TxtYourName_textChanged(const QString& arg1);

    void on_BtnUpGeneralAppFont_clicked();
    void on_BtnDownGeneralAppFont_clicked();
    void on_SldGeneralAppFont_valueChanged(int value);
    void on_CmbGeneralAppFont_currentIndexChanged(int index);
    void on_BtnGeneralAppFont_clicked();

    void on_BtnUpScriptureReadingFont_clicked();
    void on_BtnDownScriptureReadingFont_clicked();
    void on_SldScriptureReadingFont_valueChanged(int value);
    void on_CmbScriptureReadingFont_currentIndexChanged(int index);
    void on_BtnScriptureReadingFont_clicked();

    void on_BtnUpScripturePresentFont_clicked();
    void on_BtnDownScripturePresentFont_clicked();
    void on_SldScripturePresentFont_valueChanged(int value);
    void on_CmbScripturePresentFont_currentIndexChanged(int index);
    void on_BtnScripturePresentFont_clicked();

    void on_BtnTheme1_clicked();
    void on_BtnTheme2_clicked();
    void on_BtnTheme3_clicked();
    void on_BtnTheme4_clicked();
    void on_BtnTheme5_clicked();
    void on_BtnTheme6_clicked();
    void on_BtnTheme7_clicked();
    void on_BtnTheme8_clicked();
    void on_BtnTheme9_clicked();
    void on_BtnTheme10_clicked();
    void on_BtnTheme11_clicked();
    void on_BtnTheme12_clicked();
    void on_BtnTheme13_clicked();
    void on_BtnTheme14_clicked();
    void on_BtnTheme15_clicked();

private:
    Ui::BiblePreferences*ui;
    QStandardItemModel* naviModel;
};

#endif BIBLEPREFERENCES_H
