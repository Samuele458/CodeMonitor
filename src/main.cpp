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

// main function
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    CM_WelcomeDialog w ;

    //setting up stylesheets
    QFile File(":/themes/default_style.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());
    qApp->setStyleSheet( StyleSheet );

    //configuring main font (monofonto.ttf located in resurce file)
    int id = QFontDatabase::addApplicationFont(":/fonts/monofonto.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont monospace(family);
    QApplication::setFont( monospace );

    if( !QFile::exists( QDir::currentPath() + "/programming_languages.ini" ) ) {
        QFile default_file( ":/common/default_prog_lang.dat" );
        if( default_file.open( QIODevice::ReadOnly ) ) {
            QFile prog_langs_file( QDir::currentPath() + "/programming_languages.ini" );
            if( prog_langs_file.open( QIODevice::WriteOnly | QIODevice::Truncate ) ) {
                prog_langs_file.write( default_file.readAll() );
            }
        }
    }

    FileData f("C:\\Users\\Yankoo\\Desktop\\test.cpp");
    //w.show();
    return a.exec();

}
