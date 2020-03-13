#ifndef APPPREFERENCES_H
#define APPPREFERENCES_H

#include <QDialog>
#include <QModelIndex>

class QStandardItemModel;

namespace Ui {
class AppPreferences;
}

class AppPreferences : public QDialog
{
    Q_OBJECT

public:
    explicit AppPreferences(QWidget *parent = nullptr);
    ~AppPreferences();

private slots:
    void SelectedTheme(int theme);
    bool GetSettings();
    void ReloadSettings();
    void SetUpStuff();
    void LoadNavigation(QString searchstr);
    void OpenSelectedTab(const QModelIndex& index);

    void ChangeGeneralFont(int newfont);
    void ChangePreviewFont(int newfont);
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

    void on_BtnUpSongPreviewFont_clicked();
    void on_BtnDownSongPreviewFont_clicked();
    void on_SldSongPreviewFont_valueChanged(int value);
    void on_CmbSongPreviewFont_currentIndexChanged(int index);
    void on_BtnSongPreviewFont_clicked();

    void on_BtnUpSongPresentFont_clicked();
    void on_BtnDownSongPresentFont_clicked();
    void on_SldSongPresentFont_valueChanged(int value);
    void on_CmbSongPresentFont_currentIndexChanged(int index);
    void on_BtnSongPresentFont_clicked();

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
    Ui::AppPreferences*ui;
    QStandardItemModel* naviModel;
};

#endif //APPPREFERENCES_H
