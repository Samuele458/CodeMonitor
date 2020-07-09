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

#ifndef FILES_UTILITY_H
#define FILES_UTILITY_H
#include <QString>
#include <QStringList>
#include <QSettings>
#include <QFile>
#include <QDir>

class FilesUtilities {
public:
    FilesUtilities() { };
    ~FilesUtilities() { };

    //get file extention string. Es: C:/test.txt -> txt
    static QString getFileExtension( QString filename );

    //get programming language name from file extension
    static QString getProgLangName( QString extension );

    //check if a dir exists or not. If not create it
    static void dirCheck( QString dir );

    //check if file exists or not. if not, create it and fill with default data
    static void fileCheck( QString file, QByteArray default_data );
    static void fileCheckFromFile( QString file, QString default_data_filename );

};

#endif
