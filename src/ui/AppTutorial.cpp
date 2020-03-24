#include "ui/AppTutorial.h"
#include "ui_AppTutorial.h"

QString HowsSidebar, HowsTab1, HowsTab2;

AppTutorial::AppTutorial(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AppTutorial)
{
    ui->setupUi(this);
	setStyleSheet("* { background-color: #FFFFFF; }");
	ui->TabPage1->setStyleSheet("* { background-color: #EEEEEE; }");
	ui->LblSidebar->setStyleSheet("* { padding-top: 30px; background: #FFFFFF url(:/images/How.png) center no-repeat; background-size: 100%; }");

	QByteArray hows_Sidebar = HowsSidebar.toLocal8Bit();
	ui->LblSidebar->setText(QApplication::translate("AppTutorial", hows_Sidebar.data(), Q_NULLPTR));

	HowsTab1 = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n";
	HowsTab1.append("<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n");
	HowsTab1.append("p, li { white-space: pre-wrap; }\n</style>\n</head>\n");
	HowsTab1.append("<body style=\" font-family:'Trebuchet MS'; font-size:12pt; font-weight:400; font-style:normal;\">\n");
	HowsTab1.append("<p><b>Preview Mode</b> is the page that shows up immediately after the splash screen. ");
	HowsTab1.append("You might as well as call it the Homepage of the mBible app.");
	HowsTab1.append("<br>Here are some of the Keyboard shortcuts that we have put in place for managing various");
	HowsTab1.append(" actions on this page. Happy are you if you can know them quickly and easen your work!</p>");
	HowsTab1.append("<p>Note: the statement <i>Press CTRL + B</i> simply means you <u>press these 2 keys together,");
	HowsTab1.append(" at the same time.</p><p><ol>");
	HowsTab1.append("<li>Press <b>CTRL + P:</b> Open Presentation Mode</b> if there is a song currently selected.</li>");
	HowsTab1.append("<li>Press <b>CTRL + F:</b> to <b>Activates the Search Box</b> so you can search on the go.</li>");
	HowsTab1.append("<li>Press <b>CTRL + S:</b> to <b>Manage App Settings</b>.</li>");
	HowsTab1.append("<li>Press <b>CTRL + R:</b> to <b>Reset App Settings</b>.</li>");
	HowsTab1.append("</ol></p><p><u>Shortups that work when the Search box is not active</u><ol>");
	HowsTab1.append("<li>Press <b>F:</b> to <b>Change Font Type of the Song Preview</b> Text.</li>");
	HowsTab1.append("<li>Press <b>B:</b> to <b>Make Bold Song Preview</b> Text.</li>");
	HowsTab2.append("<li>Press <b>RIGHT Arrow:</b> to <b>Navigate to the Previous Chapter of the currently selected Book</b>.</li>");
	HowsTab2.append("<li>Press <b>LEFT Arrow:</b> to <b>Navigate to the Next Chapter of the currently selected Book</b>.</li>");
	HowsTab1.append("<li>Press <b>UP Arrow:</b> to <b>Increase Font Size</b> of Song Preview Text.</li>");
	HowsTab1.append("<li>Press <b>DOWN Arrow:</b> to <b>Decrease Font Size</b> of Song Preview Text.</li>");
	HowsTab1.append("</ol></p>");
	HowsTab1.append("</body></html>");

	QByteArray hows_Tab1 = HowsTab1.toLocal8Bit();
	ui->TxtTab1->setHtml(QApplication::translate("AppTutorial", hows_Tab1.data(), Q_NULLPTR));

	HowsTab2 = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n";
	HowsTab2.append("<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n");
	HowsTab2.append("p, li { white-space: pre-wrap; }\n</style>\n</head>\n");
	HowsTab2.append("<body style=\" font-family:'Trebuchet MS'; font-size:12pt; font-weight:400; font-style:normal;\">\n");
	HowsTab2.append("<p><b>Presentation Mode</b> is the page that shows when you press the PRESENT button on the homepage.");
	HowsTab2.append("You are most likely to press it when you wish to project the scripture that is currently selected.");
	HowsTab2.append("<br>Here are some of the Keyboard shortcuts when presenting a scripture!</p>");
	HowsTab2.append("<p><ol>");
	HowsTab2.append("<li>Press <b>RIGHT Arrow:</b> to <b>Navigate to the Previous Chapter of the currently selected Book</b>.</li>");
	HowsTab2.append("<li>Press <b>LEFT Arrow:</b> to <b>Navigate to the Next Chapter of the currently selected Book</b>.</li>");
	HowsTab2.append("<li>Press <b>:</b> to <b>Make Font Bold</b>.</li>");
	HowsTab2.append("<li>Press <b>(<) OR (,):</b> to <b>Decrease Font Size</b>.</li>");
	HowsTab2.append("<li>Press <b>(>) OR (.):</b> to <b>Increase Font Size</b>.</li>");
	HowsTab2.append("<li>Press <b>B:</b> to <b>Make Font Bold</b>.</li>");
	HowsTab2.append("<li>Press <b>F:</b> to <b>Change Font Type</b>; 8 Font Types available!</li>");
	HowsTab2.append("<li>Press <b>T:</b> to <b>Change Presentation Theme</b>; 15 Themes available!</li>");
	HowsTab2.append("<li>Press <b>Esc:</b> to <b>Exit from Presentation Mode</li>");
	HowsTab2.append("</ol></p>");
	HowsTab2.append("</body></html>");

	QByteArray hows_Tab2 = HowsTab2.toLocal8Bit();
	ui->TxtTab2->setHtml(QApplication::translate("AppTutorial", hows_Tab2.data(), Q_NULLPTR));

}

AppTutorial::~AppTutorial()
{
    delete ui;
}
