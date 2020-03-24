#ifndef APPONLINE_H
#define APPONLINE_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QModelIndex>

class QStandardItemModel;

namespace Ui {
class AppOnline;
}

class AppOnline : public QDialog
{
    Q_OBJECT

public:
    explicit AppOnline(QWidget *parent = nullptr);
    ~AppOnline();

private slots:
    void onBooksResult(QNetworkReply* reply);
    void onSongsResult(QNetworkReply* reply);
    void createListView();
    void LoadBooks();
    void LoadSongs();
    void showProgress(bool show);

    void on_LstBooks_clicked(const QModelIndex &index);
    void on_BtnProceed_clicked();
    void on_BtnCancel_clicked();

private:
    Ui::AppOnline *ui;
    QNetworkAccessManager* qnam;
    QNetworkRequest request;
    QStandardItemModel* bookModel;
};

#endif //APPONLINE_H
