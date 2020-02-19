#ifndef BIBLEABOUT_H
#define BIBLEABOUT_H

#include <QDialog>

namespace Ui {
class BibleAbout;
}

class BibleAbout : public QDialog
{
    Q_OBJECT

public:
    explicit BibleAbout(QWidget *parent = nullptr);
    ~BibleAbout();

private:
    Ui::BibleAbout *ui;
};

#endif
