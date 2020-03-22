#include "Application.h"
#include "AsBase.h"
#include "AsUtils.h"

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
	AsBase::WriteLogs("Events", "App Started, MainWindow opened", "", "");

	QApplication app(argc, argv);
    QPixmap pixmap("res/splash.png");
    QSplashScreen splash(pixmap, Qt::WindowStaysOnTopHint);
    splash.show();

    app.thread()->sleep(3);
    app.processEvents();
    splash.close();

    Application vsb(argc, argv);
    return vsb.exec();
}
