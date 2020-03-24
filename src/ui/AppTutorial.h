#ifndef APPTUTORIAL_H
#define APPTUTORIAL_H

#include <QDialog>

namespace Ui {
class AppTutorial;
}

class AppTutorial : public QDialog
{
    Q_OBJECT

public:
    explicit AppTutorial(QWidget *parent = nullptr);
    ~AppTutorial();

private:
    Ui::AppTutorial *ui;
};

#endif // APPTUTORIAL_H
