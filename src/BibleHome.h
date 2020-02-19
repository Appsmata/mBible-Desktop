#ifndef BIBLEHOME_H
#define BIBLEHOME_H

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

class RemoteDatabase;
class QStandardItemModel;

namespace Ui {
    class BibleHome;
}

class BibleHome : public QMainWindow
{
    Q_OBJECT

public:
    explicit BibleHome(QWidget* parent = nullptr);
    ~BibleHome();

    DBBrowserDB& getDb() { return db; }
    RemoteDatabase& getRemote() { return *m_remoteDb; }

private:
    Ui::BibleHome* ui;

    QStandardItemModel* songModel;
    DBBrowserDB db;
    RemoteDatabase* m_remoteDb;

    void init();


public slots:

private slots:
    void HomeInit();
    //void SetDarkMode();
    void ReloadControls();
    void ReloadSettings();
	void SetTheme();

    void FontChange();
    void FontSmaller();
    void FontBigger();
    void FontBold();

    void SearchBible(QString Searchstr);
    //void on_CmbLanguages_currentIndexChanged(int index);
    void on_CmbLanguages_currentIndexChanged(const QString &arg1);
    void on_TxtSearch_textChanged(const QString& searchstr);
    void GotoReading();

    void on_ChkNewTestament_stateChanged(int arg1);
    void on_ChkOldTestament_stateChanged(int arg1);

	void on_LstResults_clicked(const QModelIndex& selected);
    void on_CmbChapter_currentIndexChanged(const QString &arg1);
	void GetReading(const QModelIndex& selected);
	void OpenReading();

    void on_actionPrevious_triggered();
    void on_actionNext_triggered();

	void on_actionBold_Text_triggered();
	void on_actionChange_Font_triggered();
	void on_actionSmaller_Font_triggered();
	void on_actionBigger_Font_triggered();
	void on_actionBold_triggered();
	void on_actionSmaller_triggered();
	void on_actionBigger_triggered();
	void on_actionFont_triggered();

    void on_actionTutorial_triggered();
	void on_actionAbout_triggered();
	void on_actionPreferences_triggered();
	void on_actionManage_Settings_triggered();
	void on_actionExit_triggered();
    void on_actionTheme_triggered();

    //void on_CmbChapter_currentIndexChanged(int index);
    //void on_CmbVerse_currentIndexChanged(int index);

    /*
    void on_ChkOldTestament_triggered();
    void on_ChkNewTestament_triggered();

    void on_LstResults_activated(const QModelIndex& index);

    void on_actionPresent_triggered();
    void on_actionCheck_Updates_triggered();
    void on_actionContribute_triggered();
    void on_actionDonate_triggered()
    void on_actionReset_Settings_triggered();
    void on_actionOnline_triggered();
    void on_actionTutorial_triggered();
    void on_actionSearch_triggered();*/

};

#endif // BIBLEHOME_H