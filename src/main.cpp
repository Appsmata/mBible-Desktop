#include "Application.h"
#include <QFile>
#include <QSplashScreen>
#include <QThread>

void setStyle(const QString& qssFile)
{
    QFile qss(qssFile);
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();
}

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QPixmap pixmap("res/splash.png");
    QSplashScreen splash(pixmap, Qt::WindowStaysOnTopHint);
    splash.show();

    app.thread()->sleep(3);
    app.processEvents();
    splash.close();

    Application vsb(argc, argv);
    setStyle("res/style.qss");

    // Run application
    return vsb.exec();
}
