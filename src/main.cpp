/*	Code Monitor V1.0 - Keep trace of your code!
 *  Copyright (C) 2020 Samuele Girgenti
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 	     --  CONTACTS --
 *  Email:      samuele.girgenti458@gmail.com
 *  Github:     https://github.com/Samuele458
 */

#include <QApplication>
#include <QFile>
#include <QDir>
#include <QFont>
#include <QFontDatabase>

#include "dialogs/cm_welcomedialog.h"
#include "monitor.h"
#include "common/textsanitizer.h"
#include "common/filesutility.h"


// main function
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CM_WelcomeDialog w;

    //setting up stylesheets
    //QFile File(":/themes/default_style.qss");
    //File.open(QFile::ReadOnly);
    //QString StyleSheet = QLatin1String(File.readAll());
    //qApp->setStyleSheet( StyleSheet );





    //check if programming languages file exists or not
    FilesUtilities::fileCheckFromFile(QDir::currentPath() + "/programming_languages.ini",
                                      ":/common/default_prog_lang.dat" );

    //check if default file exists or not
    FilesUtilities::fileCheckFromFile(QDir::currentPath() + "/config.ini",
                                      ":/common/default_config.dat" );


    ManagerFromFile settings( "config.ini" );

    QFont font( settings.getValue( "font_family" ) );
    font.setPointSize( settings.getValue( "font_size" ).toInt() );
    QApplication::setFont( font );


    w.show();
    return a.exec();

}
