#include "AppAbout.h"
#include "ui_AppAbout.h"
#include "sqlitedb.h"
#include "Application.h"

QString AboutSidebar, AboutTab1, AboutTab2, AboutTab3, AboutTab4;

AppAbout::AppAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AppAbout)
{
    ui->setupUi(this);
	setStyleSheet("* { background-color: #FFFFFF; }");
	ui->TabPage1->setStyleSheet("* { background-color: #EEEEEE; }");
	ui->TabPage2->setStyleSheet("* { background-color: #EEEEEE; }");
	ui->TabPage3->setStyleSheet("* { background-color: #EEEEEE; }");
	ui->TabPage4->setStyleSheet("* { background-color: #EEEEEE; }");
	ui->LblSidebar->setStyleSheet("* { padding-top: 30px; background: #FFFFFF url(:/images/Sidebar.png) center no-repeat; background-size: 100%; }");

	AboutSidebar = "<html><head/><body>";
	AboutSidebar.append("<p style=\" font-size:20pt; font-weight:600; color:#ffffff;\"><center>");
	AboutSidebar.append("About<br/><br/><br/><br/><br/><br/><br/>");
	AboutSidebar.append("<img src=\":/images/version.png\"/></p></body></html>");

	QByteArray about_Sidebar = AboutSidebar.toLocal8Bit();
	ui->LblSidebar->setText(QApplication::translate("AppAbout", about_Sidebar.data(), Q_NULLPTR));

	AboutTab1 = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n";
	AboutTab1.append("<html><head><meta name=\"qrichtext\" content=\"1\" />");
	AboutTab1.append("<style type=\"text/css\">");
	AboutTab1.append("li { white-space: pre-wrap; }");
	AboutTab1.append("table { margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; }");
	AboutTab1.append(".para{ white-space: pre-wrap; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; }");
	AboutTab1.append("</style></head><body style=\" font-family:'Trebuchet MS','Trebuchet MS','Trebuchet MS'; font-size:12pt; font-weight:400; font-style:normal;\">");
	AboutTab1.append("<h3>GIVING YOU THE FREEDOM TO SING ANYWHERE ANYTIME</h3>");
	AboutTab1.append("<p class=\"para\">Based on Qt 5.9.9 (MSVC 2015, 64 bit)<br/>");
	AboutTab1.append("Built on March 5 2020 23:24:44<br/>");
	AboutTab1.append("Copyright &copy; 2016 - 2020 Appsmata Solutions</p><hr/>");
	AboutTab1.append("<p class=\"para\"><h2>What is mBible?</h2>");
	AboutTab1.append("... it's an application that gives users access to songs sung in church services among other places ");
	AboutTab1.append("where praise and worship is carried out. Major songbooks include Songs of Worship, Nyimbo za Injili, ");
	AboutTab1.append("Believers Songs, Redemption Songs and Tenzi za Rohoni. Other songbooks in various local dialects have ");
	AboutTab1.append("been added over time and more are under way to be added.<br/></p>");
	AboutTab1.append("<p class=\"para\"><h2>What it is not ...</h2>");
	AboutTab1.append("... this is not a media player or tutor utility if you don't know how to sing a particular song. Be sure");
	AboutTab1.append(" you know to sing most or all of the songs in it, otherwise feel free to customize the songs you want it have for you.</p>");
	AboutTab1.append("</body></html>");

	QByteArray about_Tab1 = AboutTab1.toLocal8Bit();
	ui->TxtTab1->setHtml(QApplication::translate("AppAbout", about_Tab1.data(), Q_NULLPTR));

	AboutTab2 = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n";
	AboutTab2.append("<html><head><meta name=\"qrichtext\" content=\"1\" />");
	AboutTab2.append("<style type=\"text/css\">");
	AboutTab2.append("li { white-space: pre-wrap; }");
	AboutTab2.append("table { margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; }");
	AboutTab2.append(".para{ white-space: pre-wrap; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; }");
	AboutTab2.append("</style></head><body style=\" font-family:'Trebuchet MS','Trebuchet MS','Trebuchet MS'; font-size:12pt; font-weight:400; font-style:normal;\">");
	AboutTab2.append("<p class=\"para\">mBible was first developed in September 2014 as android application by Jack Siro then an ICT student at KTTC. ");
	AboutTab2.append("Having learnt basics of android app development from one of his friends, Geoffrey Omenda, he felt he could try to digitize ");
	AboutTab2.append("the Songs of Worship and Nyimbo za Injili into an app for himself just like the Bible was an app on his phone.</p>");
	AboutTab2.append("<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br/></p>");
	AboutTab2.append("<p class=\"para\">While at home in December the same year his father who came to his room to check on him and ask ");
	AboutTab2.append("some little computer questions' noticed an unfamiliar app on his phone. On learning and interacting ");
	AboutTab2.append("with it he asked to have it on his phone. The happy father went ahead to share the app ");
	AboutTab2.append("Jack's elder brothers. Later while at the End of Year Meetings at Mbale, Kenya he endosed it there ");
	AboutTab2.append("during one of his sermons. The app by then had only 100 Songs of Worship as well as 100 Nyimbo za Injili songs.</p>");
	AboutTab2.append("<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br/></p>");
	AboutTab2.append("<p class=\"para\">Due to pressure to have all the songs in the app he invited George Gitau then BBIT student ");
	AboutTab2.append("at JKUAT to type the songs for him. By the mid of 2015 all the songs in the tow major songbooks were ");
	AboutTab2.append("in digital format. However because of insufficient funds he could not afford to host the app on playstore. ");
	AboutTab2.append("But God who was ever on his side connected him with Kevin Ngalonde, a Brother-in-Christ from Zimbabwe who owned ");
	AboutTab2.append("ZimApps a small startup. Kevin generously hosted the app for him until when he would be able to ");
	AboutTab2.append("have his own Playstore account. During that same time he met James Waheire of Banana Believers Church ");
	AboutTab2.append("who sponsored the digitizing of Nyimbo cia Kuinira Ngai, the Kikuyu songbook.</p>");
	AboutTab2.append("<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br/></p>");
	AboutTab2.append("<p class=\"para\">In August 2015 while at attachment he made a new update made users of the app pay Ksh 200 to use the ");
	AboutTab2.append("app without which the app would cease to work five days after installation. Mode of payment was though ");
	AboutTab2.append("mobile money to his personal mobile money account. He would then send a short code to the user to ");
	AboutTab2.append("activate the app. This then became a major income earner for him while still a student and he was ");
	AboutTab2.append("able to expand his territory to Windows Phone in 2016. In mid 2016 when he managed to have his own ");
	AboutTab2.append("Playstore account that he now hosts the app from.</p>");
	AboutTab2.append("<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br/></p>");
	AboutTab2.append("<p class=\"para\">Towards the begining of 2017 as a freelancer he was already working on a desktop version of the ");
	AboutTab2.append("app using .net framework (c#). Since the PC version was on sell at Kshs 1500 not many were able to ");
	AboutTab2.append("purchase it and so it didnt become a major project for him. With constant improvements the Android ");
	AboutTab2.append("app seen many improvements which are now being ported to the PC version. Both apps are free thanks ");
	AboutTab2.append("to various donations give to the project. As of late 2019 to the present moment the two apps have ");
	AboutTab2.append("newer facelists and more features added to them, and who knows courtesy of the QT framework (c++) ");
	AboutTab2.append("it will be able to be fully cross platform app on Android, Web, Windows, Linux, MacOS and iOS!</p>");
	AboutTab2.append("</body></html>");

	QByteArray about_Tab2 = AboutTab2.toLocal8Bit();
	ui->TxtTab2->setHtml(QApplication::translate("AppAbout", about_Tab2.data(), Q_NULLPTR));

	AboutTab3 = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n";
	AboutTab3.append("<html><head><meta name=\"qrichtext\" content=\"1\" />");
	AboutTab3.append("<style type=\"text/css\">");
	AboutTab3.append("li { white-space: pre-wrap; }");
	AboutTab3.append("table { margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; }");
	AboutTab3.append(".para{ white-space: pre-wrap; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; }");
	AboutTab3.append("</style></head><body style=\" font-family:'Trebuchet MS','Trebuchet MS','Trebuchet MS'; font-size:12pt; font-weight:400; font-style:normal;\">");
	AboutTab3.append("<p class=\"para\"><h4>Digitizing the Songbooks</h4><ul>");
	AboutTab3.append("<li>Songs of worship and Nyimbo za Injili - George Gitau & his friend(s).</li>");
	AboutTab3.append("<li>Nyimbo cia Kuinira Ngai (Kikuyu Songbook) - Jack Siro & James Waheire.</li>");
	AboutTab3.append("<li>Mbathi sya Kumutaia Ngai (Kamba Songbook) - Jack Siro & Simon Muthama</li>");
	AboutTab3.append("<li>Tsinyimbo Tsya Nyasaye (Luhya Songbook) - Davis & Paul Kijusa</li>");
	AboutTab3.append("<li>Bemba Hymns (Malawi Songbook) - Mutaizye Simutami</li>");
	AboutTab3.append("</ul></p>");
	AboutTab3.append("<p class=\"para\"><h4>Programming</h4><ul>");
	AboutTab3.append("<li>Jack Siro.</li>");
	AboutTab3.append("<li><a href=\"https://sqlitebrowser.org\">DB Browser Developers</a> esp for the PC version.</li>");
	AboutTab3.append("</ul></p>");
	AboutTab3.append("<p class=\"para\"><h4>Encouragements & Donations</h4>");
	AboutTab3.append("Quite a number of people have helped get this project where it is currently from its infant stages. ");
	AboutTab3.append("First of all Jack Siro the lead developer. His father played an important as depicted in the History. ");
	AboutTab3.append("Others like James Waheire who sponsored the Kikuyu songbook, Simon Muthama who sponsored the Kamba songbook");
	AboutTab3.append(" are some important people who helped to broaden the scope of this app just like Mutaizye Simutami all ");
	AboutTab3.append("the way Malawi with the Bemba songbook.</p>");
	AboutTab3.append("<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br/></p>");
	AboutTab3.append("<p>Keving Ngalonde all the way from Zimbabwe sponsored hosting of this app on his playstore account when ");
	AboutTab3.append("we had none. Ever since we lauched our paybill we have been getting people dropping a coin there ");
	AboutTab3.append("Plus those who dropped a coin on our Paybill.</p>");
	AboutTab3.append("</body></html>");

	QByteArray about_Tab3 = AboutTab3.toLocal8Bit();
	ui->TxtTab3->setHtml(QApplication::translate("AppAbout", about_Tab3.data(), Q_NULLPTR));
	
	AboutTab4 = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n";
	AboutTab4.append("<html><head><meta name=\"qrichtext\" content=\"1\" />");
	AboutTab4.append("<style type=\"text/css\">");
	AboutTab4.append("li { white-space: pre-wrap; }");
	AboutTab4.append("table { margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; }");
	AboutTab4.append(".para{ white-space: pre-wrap; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; }");
	AboutTab4.append("</style></head><body style=\" font-family:'Trebuchet MS','Trebuchet MS','Trebuchet MS'; font-size:12pt; font-weight:400; font-style:normal;\">");
	AboutTab4.append("<p class=\"para\">This program is a free software; you can redistribute it and or modify it under the terms of the GNU General Public ");
	AboutTab4.append("License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later ");
	AboutTab4.append("version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the ");
	AboutTab4.append("implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. Please see the GNU General Public License for more details.</p>");
	AboutTab4.append("<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br/></p>");
	AboutTab4.append("<p class=\"para\">It is bi-licensed under the Mozilla Public License Version 2, as well as the GNU General Public License Version 3 or later. ");
	AboutTab4.append("You can modify or redistribute it under the conditions of these licenses. </p>");
	AboutTab4.append("<p class=\"para\">See <a href=\"http://www.gnu.org/licenses/gpl.html/\" http://www.gnu.org/licenses/gpl.html</span></a> and <a href=\"http://www.mozilla.org/MPL/2.0/index.tx\">https://www.mozilla.org/MPL/2.0/index.txt</a> for details. </p>");
	AboutTab4.append("<p class=\"para\">This software uses the GPL/LGPL Qt Toolkit from <a href=\"http://qt-project.org/\">http://qt-project.org/</a> </p>");
	AboutTab4.append("<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br/></p>");
	AboutTab4.append("<p class=\"para\">See <a href=\"http://qt-project.org/doc/qt-5/licensing.html\">http://qt-project.org/doc/qt-5/licensing.html</a> for licensing terms and information.</p>");
	AboutTab4.append("<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br/></p>");
	AboutTab4.append("<p class=\"para\">For more information on this program please visit our website at: ");
	AboutTab4.append("<a href=\"http://Appsmata.com/mBible\">http://Appsmata.com/mBible</a>.</p>");
	AboutTab4.append("</body></html>");
	QByteArray about_Tab4 = AboutTab4.toLocal8Bit();
	ui->TxtTab4->setHtml(QApplication::translate("AppAbout", about_Tab4.data(), Q_NULLPTR));

}

AppAbout::~AppAbout()
{
    delete ui;
}
