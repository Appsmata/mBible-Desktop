#ifndef BIBLETUTORIAL_H
#define BIBLETUTORIAL_H

#include <QDialog>

namespace Ui {
class BibleTutorial;
}

class BibleTutorial : public QDialog
{
    Q_OBJECT

public:
    explicit BibleTutorial(QWidget *parent = nullptr);
    ~BibleTutorial();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::BibleTutorial *ui;
};

#endif // BIBLETUTORIAL_H
