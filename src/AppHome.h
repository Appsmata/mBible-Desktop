#ifndef APPHOME_H
#define APPHOME_H

#include "sqlitedb.h"

#include <memory>
#include <QMainWindow>
#include <QModelIndex>
#include <QListView>
#include <QDialog>
#include <QDialogButtonBox>
#include <QListView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QMessageBox>

class QStandardItemModel;

namespace Ui {
    class AppHome;
}

class AppHome : public QMainWindow
{
    Q_OBJECT

public:
    explicit AppHome(QWidget* parent = nullptr);
    ~AppHome();

    DBBrowserDB& getDb() { return db; }

private:
    Ui::AppHome* ui;

    QStandardItemModel* songModel;
    DBBrowserDB db;

    void init();


public slots:

private slots:
    void HomeInit();
    void ReloadControls();
    void ReloadSettings();

    void FontChange();
    void FontSmaller();
    void FontBigger();
    void FontBold();

    bool PopulateSongbooks();
    void PopulateSonglists(QString Searchstr);

    void on_TxtSearch_textChanged(const QString& searchstr);
    void on_LstResults_clicked(const QModelIndex& selected);
    void OpenSongPreview(const QModelIndex& selected);

    void on_CmbSongbooks_currentIndexChanged(int index);
    void on_LstResults_activated(const QModelIndex& index);
    void on_LstResults_doubleClicked(const QModelIndex& index);

    void on_actionPresent_triggered();
    void on_actionBold_Text_triggered();
    void on_actionChange_Font_triggered();
    void on_actionSmaller_Font_triggered();
    void on_actionBigger_Font_triggered();
    void on_actionCheck_Updates_triggered();
    void on_actionContribute_triggered();
    void on_actionDonate_triggered();
    void on_actionDelete_Song_triggered();
    void on_actionEdit_Song_triggered();
    void on_actionNew_Song_triggered();
    void on_actionManage_Settings_triggered();
    void on_actionReset_Settings_triggered();
    void on_actionAbout_triggered();
    void on_actionExit_triggered();
    void on_actionBold_triggered();
    void on_actionSmaller_triggered();
    void on_actionBigger_triggered();
    void on_actionPreferences_triggered();
    void on_TxtSearch_returnPressed();
    void on_actionEdit_triggered();
    void on_actionNewsong_triggered();
    void on_actionSongbooks_triggered();
    void on_actionOnline_triggered();
    void on_actionTutorial_triggered();
    void on_actionFont_triggered();
    void on_actionSearch_triggered();
    void on_actionSearchAll_triggered();
    void on_ChkSearchCriteria_clicked();
    void on_actionDarkMode_triggered();
    void on_ChkDarkMode_clicked();
};

#endif // APPHOME_H
