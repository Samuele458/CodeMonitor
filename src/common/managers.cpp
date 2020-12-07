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

#include "managers.h"


//default constructor
ManagerFromFile::ManagerFromFile() : Manager<QString, QString>() {
    filename = "";
    load();
}

//main constructor (by passing filename)
ManagerFromFile::ManagerFromFile( QString filename_str ) : Manager<QString, QString>() {
    filename = filename_str;
    load();
}

//copy constructor
ManagerFromFile::ManagerFromFile( const ManagerFromFile& other ) : Manager<QString, QString>(other) {
    filename = other.filename;
}

//assignment operator
ManagerFromFile& ManagerFromFile::operator=( const ManagerFromFile& other ) {
    Manager<QString,QString>::operator=( other );
    filename = other.filename;
    return *this;
}

//filename string setter method
void ManagerFromFile::setFilename( QString filename_str ) {
    filename = filename_str;
}

//filename string getter method
QString ManagerFromFile::getFilename() const {
    return filename;
}

//load data from file
bool ManagerFromFile::load() {
    QStringList keys_array;

    if( filename != "" && QFile::exists( filename ) ) {
        QSettings settings( filename, QSettings::IniFormat );
        settings.beginGroup( "set_1" );

        //getting new values
        keys_array = settings.allKeys();


        //clearing old values
        keys.clear();
        values.clear();

        //setting new values
        for( int i = 0; i < keys_array.size(); ++i ) {
            keys.push_back( keys_array.at(i) );
            values.push_back( settings.value( keys.at(i) ).toString() );
        }
        settings.endGroup();
        return true;
    }

    //error with filename
    return false;
}

//save data to file
bool ManagerFromFile::save() {
    if( filename != "" ) {
        QSettings settings( filename, QSettings::IniFormat );
        settings.beginGroup( "set_1" );

        //saving values
        for( int i = 0; i < keys.size(); ++i ) {
            settings.setValue( keys.at(i), values.at(i) );
        }

        settings.endGroup();

        return true;
    }

    //error with filename
    return false;
}



/*
// ------ class LanguageManager ------

const QStringList LanguageManager::languages_filenames = QStringList() << "translations/italian.ini"
                                                                       << "translations/english.ini";

//copy constructor
LanguageManager::LanguageManager( const LanguageManager& other ) : ManagerFromFile( other ) {
    language = other.language;
}

//assignment operator
LanguageManager& LanguageManager::operator=( const LanguageManager& other ) {
    ManagerFromFile::operator=( other );
    language = other.language;
    return *this;
}

//setter
void LanguageManager::setLanguageId( int language_id ) {
    language = language_id;
}

//getter
int LanguageManager::getLanguageId() const {
    return language;
}

//conversion from filename string to language id.
//It returns -1 if filename_str is not found
int LanguageManager::lang_filename_to_id( QString filename_str ) {
    return languages_filenames.indexOf( filename_str );
}

//conversion from language id to filename string.
//It returns "" if id_value is not found
QString LanguageManager::id_to_lang_filename( int id_value ) {
    if( id_value >= 0 && id_value < languages_filenames.size() ) {
        return languages_filenames.at(id_value);
    }
    return "";
}

*/






