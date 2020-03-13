#ifndef APPPRESENT_H
#define APPPRESENT_H

#include "sqlitedb.h"
#include <QMainWindow>

class RemoteDatabase;
namespace Ui {
class AppPresent;
}

class AppPresent : public QMainWindow
{
    Q_OBJECT

public:
    explicit AppPresent(QWidget* parent = nullptr);
    ~AppPresent();

private:
    Ui::AppPresent* ui;

    DBBrowserDB db;
    RemoteDatabase* m_remoteDb;

private slots:
    void SetUpStuff();
    void ReloadSettings();
    void ReloadControls();
    void PresentSong(QString setsong);
    void ContentPrepare();
    void SetPresentation();
    void SetTheme();

    void on_actionClose_triggered();
    void on_BtnClose_clicked();
    void on_actionLeft_triggered();
    void on_actionRight_triggered();
    void on_actionBigger_triggered();
    void on_actionSmaller_triggered();
    void on_actionFont_triggered();
    void on_actionBold_triggered();
    void on_actionTheme_triggered();
    void on_actionChorus_triggered();
    void on_actionUp_triggered();
    void on_actionDown_triggered();
    void on_BtnDown_clicked();
    void on_BtnUp_clicked();

};

#endif // APPPRESENT_H
