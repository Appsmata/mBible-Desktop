#include "BibleTutorial.h"
#include "ui_BibleTutorial.h"

BibleTutorial::BibleTutorial(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BibleTutorial)
{
	ui->setupUi(this);
	this->setFixedSize(this->width(), this->height());
	this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

BibleTutorial::~BibleTutorial()
{
    delete ui;
}

void BibleTutorial::on_buttonBox_accepted()
{
    close();
}
