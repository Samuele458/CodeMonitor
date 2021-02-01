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

#include "common/filesutility.h"

//get file extention string. Es: C:/test.txt -> txt
QString FilesUtilities::getFileExtension( QString filename ) {
    int point_index = filename.indexOf( "." );
    if( point_index != 0 ) {
        return filename.mid( point_index + 1,
                             filename.size() - point_index - 1 );
    } else {
        return "";
    }
}

//get programming language name from file extension
QString FilesUtilities::getProgLangName( QString extension ) {
    QSettings prog_langs( QDir::currentPath() + "/programming_languages.ini", QSettings::IniFormat );
    QStringList languages = prog_langs.childGroups();
    for( int i = 0; i < languages.size(); ++i ) {
        prog_langs.beginGroup( languages.at(i) );
        QStringList extensions = prog_langs.value( "files_extensions" ).toString().split( " " );
        if ( extensions.indexOf( extension ) != -1 ) {
            prog_langs.endGroup();
            return languages.at(i);
        }
        prog_langs.endGroup();
    }
    return "";
}

//check if a dir exists or not. If not create it
void FilesUtilities::dirCheck( QString dir ) {

    QDir dir_obj( dir );
    qDebug() << dir;
    if( !dir_obj.exists() ) {

#ifdef __linux__
    dir_obj.mkpath( "." );
#elif _WIN32
    dir_obj.mkdir( "." );
#else
    //OS != WIN, LINUX.
    //Not tested
    dir_obj.mkpath( "." );
#endif

    }
}

//check if file exists or not. if not, create it and fill with default data
void FilesUtilities::fileCheck( QString file, QByteArray default_data ) {
    if( !QFile::exists( file ) ) {
        QFile out_file( file );
        if( out_file.open( QIODevice::WriteOnly | QIODevice::Truncate ) ) {
            out_file.write( default_data );
        }
    }
}

void FilesUtilities::fileCheckFromFile( QString file, QString default_data_filename ) {
    if( !QFile::exists( file ) ) {
        QFile out_file( file );
        if( out_file.open( QIODevice::WriteOnly | QIODevice::Truncate ) ) {
            QFile in_file( default_data_filename );
            if( in_file.open( QIODevice::ReadOnly ) ) {

                out_file.write( in_file.readAll() );

            }
        }
    }
}

