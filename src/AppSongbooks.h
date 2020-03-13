#ifndef APPSONGBOOKS_H
#define APPSONGBOOKS_H

#include <QDialog>
#include <QModelIndex>

class QStandardItemModel;

namespace Ui {
class AppSongbooks;
}

class AppSongbooks : public QDialog
{
    Q_OBJECT

public:
    explicit AppSongbooks(QWidget *parent = nullptr);
    ~AppSongbooks();

private slots:
    void LoadBook();
    void GetUpdates();
    void LoadBooklist(QString searchstr);
    void SaveChanges();
    void DeleteBook();

    void on_LstBooks_clicked(const QModelIndex &index);
    void on_TxtSearch_textChanged(const QString &arg1);

    void on_actionNew_triggered();
    void on_actionSave_triggered();
    void on_actionDelete_triggered();
    void on_actionRefresh_triggered();
    void on_actionUpdate_triggered();

private:
    Ui::AppSongbooks*ui;
    QStandardItemModel* bookModel;
};

#endif //APPSONGBOOKS_H
