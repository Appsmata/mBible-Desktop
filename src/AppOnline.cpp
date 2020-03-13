#include "AppOnline.h"
#include "ui_AppOnline.h"

#include "sqlite.h"
#include "RunSql.h"
#include "sqlitetablemodel.h"

#include "AsItem.h"
#include "AsBase.h"
#include "AsUtils.h"
#include "AsDelegate.h"

#include <QDebug>
#include <QtCore>
#include <QtNetwork>
#include <QJsonDocument>
#include <QTextCodec>
#include <QLibraryInfo>
#include <QMessageBox>
#include <QLocale>
#include <QStandardItemModel>
#include <QObject>

QString networkresult;
//const int iterations = 20;
QVector<int> vector;
std::vector<QString> catids, titles, tags, contents, songnos;
QStringList selecteds, selectedBooks;

AppOnline::AppOnline(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AppOnline)
{
    ui->setupUi(this);
    ui->TxtSearch->hide();

    LoadBooks();
}

void AppOnline::LoadBooks()
{
    showProgress(true);
    qnam = new QNetworkAccessManager();
    QObject::connect(qnam, SIGNAL(finished(QNetworkReply*)), this, SLOT(onBooksResult(QNetworkReply*)));
    request.setUrl(QUrl("http://sing.appsmata.com/as-api/book-select.php"));
    qnam->get(request);
}

void AppOnline::onBooksResult(QNetworkReply* reply)
{
    showProgress(false);
    if (reply->error()) {
        qDebug() << reply->errorString();
        return;
    }
    else
    {
        networkresult = (QString)reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(networkresult.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();
        QJsonArray jsonArray = jsonObject["data"].toArray();
        
        bookModel = new QStandardItemModel();

        int count = 1;
        foreach(const QJsonValue & value, jsonArray) 
        {
            QJsonObject obj = value.toObject();
            QString title = obj["title"].toString();
            QString code = obj["backpath"].toString();
            QString songs = obj["qcount"].toString();

            QStandardItem* bookItem = new QStandardItem;
            AsItem book;

            book.image = "res/check.png";
            book.title = QString::number(count) + ". " + title;
            book.content = songs + " " + code + " songs";
            catids.push_back(obj["categoryid"].toString());
            titles.push_back(title);
            tags.push_back(obj["backpath"].toString());
            contents.push_back(obj["contents"].toString());
            songnos.push_back(songs);

            bookItem->setData(QVariant::fromValue(book), Qt::UserRole + 1);
            bookModel->appendRow(bookItem);
            count++;
        }
        createListView();
    }
}

void AppOnline::showProgress(bool show)
{
    if (show)
    {
        ui->TxtSearch->hide();
        ui->LstBooks->hide();
        ui->LblNothing->hide();
        ui->BtnProceed->hide();
        ui->BtnCancel->hide();
        ui->progressBar->show();
    }
    else
    {
        ui->TxtSearch->show();
        ui->LstBooks->show();
        ui->LblNothing->show();
        ui->BtnProceed->show();
        ui->BtnCancel->show();
        ui->progressBar->hide();
    }
}

void AppOnline::createListView()
{
    AsDelegate* asDelegate = new AsDelegate(this);
    ui->LstBooks->setItemDelegate(asDelegate);
    ui->LstBooks->setModel(bookModel);
    ui->LstBooks->setViewMode(QListView::ListMode);
    ui->LstBooks->setDragEnabled(true);
    ui->LstBooks->setSelectionMode(QAbstractItemView::MultiSelection);
    ui->LstBooks->setSpacing(1);
    ui->LstBooks->setStyleSheet("* { background-color: #D3D3D3; }");
}

void AppOnline::on_LstBooks_clicked(const QModelIndex &index)
{
    QModelIndexList list = ui->LstBooks->selectionModel()->selectedIndexes();

    selecteds.clear();
    selectedBooks.clear();

    foreach(const QModelIndex &index, list)
    {
        int selectint = catids[index.row()].toInt();
        selecteds.push_back(catids[selectint]);
        selectedBooks.push_back(titles[selectint]);
    }
}

void AppOnline::on_BtnProceed_clicked()
{
    QString selectedones;
    if (selectedBooks.size() > 0)
    {
        QMessageBox msgBox;
        msgBox.setText("Done with selecting?");
        for (int i = 0; i < selectedBooks.size(); i++)
        {
            selectedones = selectedones + QString::number(i + 1) + ". " + selectedBooks[i] + ".\n";
        }
        msgBox.setInformativeText(selectedones);
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);

        int ret = msgBox.exec();

        switch (ret) {
        case QMessageBox::Yes:
            LoadSongs();
            break;
        default:
            // should never be reached
            break;
        }
    }
    else
    {
        QMessageBox::warning(this, "Just a Minute ...", tr("Oops! This is so heart breaking. You haven't selected a book, you expect things to be okay. You got to select at least one book. \n\n By the way we can always bring you back here to select afresh. But for now select at least one"));

    }
}

void AppOnline::on_BtnCancel_clicked()
{
    this->close();
}

void AppOnline::LoadSongs()
{
    showProgress(true);
    QString books = selecteds[0];
    int bookid = selecteds[0].toInt();
    AsBase::NewBook(titles[bookid], catids[bookid], tags[bookid], contents[bookid], "1", songnos[bookid]);

    for (int i = 1; i < selecteds.size(); i++) {
        books = books + "," + selecteds[i];
        int bookid = selecteds[1].toInt();
        AsBase::NewBook(titles[bookid], catids[bookid], tags[bookid], contents[bookid], QString::number(i), songnos[bookid]);
    }

    qnam = new QNetworkAccessManager();
    QObject::connect(qnam, SIGNAL(finished(QNetworkReply*)), this, SLOT(onSongsResult(QNetworkReply*)));
    request.setUrl(QUrl("http://sing.appsmata.com/as-api/posts-select.php?books=" + books));
    qnam->get(request);
}

void AppOnline::onSongsResult(QNetworkReply* reply)
{
    showProgress(false);
    if (reply->error()) {
        qDebug() << reply->errorString();
        return;
    }
    else
    {
        networkresult = (QString)reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(networkresult.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();
        QJsonArray jsonArray = jsonObject["data"].toArray();

        bookModel = new QStandardItemModel();

        int count = 1;
        foreach(const QJsonValue & value, jsonArray)
        {
            QJsonObject obj = value.toObject();

            QString Bookid = obj["bookid"].toString();
            QString Categoryid = obj["categoryid"].toString();
            QString Number = obj["number"].toString();
            QString Title = obj["title"].toString();
            QString Alias = obj["alias"].toString();
            QString Content = obj["content"].toString();

            AsBase::NewSong(Bookid, Categoryid, Number, Title, Alias, Content, "", "");
            count++;
        }
        this->close();
    }
}

AppOnline::~AppOnline()
{
    delete qnam;
    delete ui;
}
