#ifndef APPEDITOR_H
#define APPEDITOR_H

#include "sqlitedb.h"
#include <QDialog>

class RemoteDatabase;

namespace Ui {
class AppEditor;
}

class AppEditor : public QDialog
{
    Q_OBJECT

public:
    explicit AppEditor(QWidget *parent = nullptr, bool newSong = false);
    ~AppEditor();

private:
    Ui::AppEditor*ui;

    DBBrowserDB db;
    RemoteDatabase* m_remoteDb;

private slots:
    void ShowFeedback(bool show);
    void DeleteSong();
    void ReloadSettings();
    bool PopulateSongbooks();
    void LoadSong();
    void SaveChanges();
    void ShowExtraFields();
    void on_actionSave_triggered();
    void on_actionDelete_triggered();
    void on_actionClear_triggered();
    void on_actionExtra_triggered();
    void on_BtnFeedback_clicked();
};

#endif // APPEDITOR_H
