#include "ui/AppAbout.h"
#include "ui_AppAbout.h"
#include "sqlitedb.h"
#include "Application.h"

QString AboutSidebar, AboutTab1, AboutTab2, AboutTab3;

AppAbout::AppAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AppAbout)
{
    ui->setupUi(this);
	setStyleSheet("* { background-color: #FFFFFF; }");
	ui->TabPage1->setStyleSheet("* { background-color: #EEEEEE; }");
	ui->TabPage2->setStyleSheet("* { background-color: #EEEEEE; }");
	ui->TabPage3->setStyleSheet("* { background-color: #EEEEEE; }");
	ui->LblSidebar->setStyleSheet("* { padding-top: 30px; background: #FFFFFF url(:/images/About.png) center no-repeat; background-size: 100%; }");

	QByteArray about_Sidebar = AboutSidebar.toLocal8Bit();
	ui->LblSidebar->setText(QApplication::translate("AppAbout", about_Sidebar.data(), Q_NULLPTR));

	AboutTab1 = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n";
	AboutTab1.append("<html><head><meta name=\"qrichtext\" content=\"1\" />");
	AboutTab1.append("<style type=\"text/css\">");
	AboutTab1.append("li { white-space: pre-wrap; }");
	AboutTab1.append("table { margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; }");
	AboutTab1.append(".para{ white-space: pre-wrap; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; }");
	AboutTab1.append("</style></head><body style=\" font-family:'Trebuchet MS','Trebuchet MS','Trebuchet MS'; font-size:12pt; font-weight:400; font-style:normal;\">");
	AboutTab1.append("<h3>SIMPLE BIBLE READING ANYWHERE ANYTIME</h3>");
	AboutTab1.append("<p class=\"para\">Based on Qt 5.9.9 (MSVC 2015, 64 bit)<br/>");
	AboutTab1.append("Built on March 21 2020 15:28:35<br/>");
	AboutTab1.append("Copyright &copy; 2016 - 2020 Appsmata Solutions</p><hr/>");
	AboutTab1.append("<p class=\"para\"><h2>What is mBible?</h2>");
	AboutTab1.append("... it's an application that gives users access to the Holy Bible on the laptops and desktops. Major langueges are English and Kiswahili.<br/></p>");
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
	AboutTab2.append("<p class=\"para\"><h4>Programming</h4><ul>");
	AboutTab2.append("<li>Jack Siro.</li>");
	AboutTab2.append("<li><a href=\"https://sqlitebrowser.org\">DB Browser Developers</a> esp for the PC version.</li>");
	AboutTab2.append("</ul></p>");
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
	AboutTab3.append("<p class=\"para\">This program is a free software; you can redistribute it and or modify it under the terms of the GNU General Public ");
	AboutTab3.append("License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later ");
	AboutTab3.append("version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the ");
	AboutTab3.append("implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. Please see the GNU General Public License for more details.</p>");
	AboutTab3.append("<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br/></p>");
	AboutTab3.append("<p class=\"para\">It is bi-licensed under the Mozilla Public License Version 2, as well as the GNU General Public License Version 3 or later. ");
	AboutTab3.append("You can modify or redistribute it under the conditions of these licenses. </p>");
	AboutTab3.append("<p class=\"para\">See <a href=\"http://www.gnu.org/licenses/gpl.html/\" http://www.gnu.org/licenses/gpl.html</span></a> and <a href=\"http://www.mozilla.org/MPL/2.0/index.tx\">https://www.mozilla.org/MPL/2.0/index.txt</a> for details. </p>");
	AboutTab3.append("<p class=\"para\">This software uses the GPL/LGPL Qt Toolkit from <a href=\"http://qt-project.org/\">http://qt-project.org/</a> </p>");
	AboutTab3.append("<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br/></p>");
	AboutTab3.append("<p class=\"para\">See <a href=\"http://qt-project.org/doc/qt-5/licensing.html\">http://qt-project.org/doc/qt-5/licensing.html</a> for licensing terms and information.</p>");
	AboutTab3.append("<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br/></p>");
	AboutTab3.append("<p class=\"para\">For more information on this program please visit our website at: ");
	AboutTab3.append("<a href=\"http://Appsmata.com/mBible\">http://Appsmata.com/mBible</a>.</p>");
	AboutTab3.append("</body></html>");
	QByteArray about_Tab3 = AboutTab3.toLocal8Bit();
	ui->TxtTab3->setHtml(QApplication::translate("AppAbout", about_Tab3.data(), Q_NULLPTR));

}

AppAbout::~AppAbout()
{
    delete ui;
}
