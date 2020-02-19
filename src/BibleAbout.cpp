#include "BibleAbout.h"
#include "ui_BibleAbout.h"
#include "sqlitedb.h"
#include "Application.h"

BibleAbout::BibleAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BibleAbout)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    /*QString sqlite_version, sqlcipher_version;
    DBBrowserDB::getSqliteVersion(sqlite_version, sqlcipher_version);
    if(sqlcipher_version.isNull())
        sqlite_version = tr("SQLite Version ") + sqlite_version;

    ui->label_version->setText(tr("Version ") + qApp->applicationVersion() + "\n" +
                               tr("Built for ") + QSysInfo::buildAbi() + ", running on " + QSysInfo::currentCpuArchitecture() + "\n" +
                               tr("Qt Version ") + QT_VERSION_STR + "\n" +
                               sqlite_version
                               );*/
}

BibleAbout::~BibleAbout()
{
    delete ui;
}
