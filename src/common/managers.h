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

#ifndef MANAGER_H
#define MANAGER_H
#include <QString>
#include <QMap>
#include <QStringList>
#include <QList>
#include <QPair>
#include <QMapIterator>
#include <QFile>
#include <QDir>
#include <QSettings>
#include <QDebug>


/*
 * Class name:          Manager<T1,T2>
 * Description:         Class created to handle a map. It is reused
 *                      to build LanguageManager and configManager
 *
 */
template <class T1, class T2>
class Manager
{
    public:
        Manager() { };                                                  //default constructor
        Manager( QList<T1> keys_param, QList<T2> values_param );        //main constructor
        ~Manager() { };                                                 //destructor

        Manager( const Manager& other );
        Manager& operator=( const Manager& other );

        T2 getValue( T1 key_param, bool* found = nullptr ) const;
        T1 getKey( T2 value_param, bool* found = nullptr  ) const;
        QPair<T1,T2> getPairByKey(T1 key_param, bool* found = nullptr ) const;

        bool setValue( T1 key_param, T2 value_param );

        bool push_back( T1 key_param, T2 value_param );

        QMap<T1,T2> getMap() const;
        void setMap( QMap<T1,T2> map_param );

        QList<T1> getKeys() const;
        QList<T1> getValues() const;


        //only for debug purpouse
        void debug_dump();
    protected:
        QList<T1> keys;
        QList<T2> values;

};


//---- implementations ----
template <class T1, class T2>
Manager<T1,T2>::Manager( QList<T1> keys_param, QList<T2> values_param ) {
    //checking vectors length, it must be the same for both
    if( keys_param.size() == values_param.size() ) {
        //same length
        keys = keys_param;
        values = values_param;
    }
}


//copy constructor
template <class T1, class T2>
Manager<T1,T2>::Manager( const Manager& other ) {
    keys = other.keys;
    values = other.values;
}


//assignment operator
template <class T1, class T2>
Manager<T1,T2>& Manager<T1,T2>::operator=( const Manager& other ) {
    keys = other.keys;
    values = other.values;
    return *this;
}


//get value by passing key. If key is not found, *found parameter is false.
template <class T1, class T2>
T2 Manager<T1,T2>::getValue( T1 key_param, bool* found ) const {
    int index;
    index = keys.indexOf( key_param );
    if( index == -1 ) {
        if( found != nullptr )
            *found = false;
        return T1();
    } else {
        if( found != nullptr )
            *found = true;
        return values.at(index);
    }
}

//get key by passing value. If value is not found, *found parameter is false.
//is multiple key have the same value, is returned the key with the less index
template <class T1, class T2>
T1 Manager<T1,T2>::getKey( T2 value_param, bool* found ) const {
    int index;
    index = values.indexOf( value_param );
    if ( index == -1 ) {
        //not found
        if( found != nullptr )
        *found = false;
        return T2();
    } else {
        //found
        if( found != nullptr )
            *found = true;
        return keys.at(index);
    }
}


//return a pair (key and value) by passing a key.
//If key is not found, *found is false.
template <class T1, class T2>
QPair<T1,T2> Manager<T1,T2>::getPairByKey(T1 key_param, bool* found ) const {
    int index;
    QPair<T1,T2> pair;

    index = keys.indexOf( key_param );
    if( index == -1 ) {
        //NOT found
        if( found != nullptr )
            *found = false;
        pair.first = T1();
        pair.second = T2();
    } else {
        //found
        if( found != nullptr )
            *found = true;
        pair.first = keys.at(index);
        pair.second = values.at(index);
    }
    return pair;
}

//set a value to a key
template <class T1, class T2>
bool Manager<T1,T2>::setValue( T1 key_param, T2 value_param ) {
    int index;
    index = keys.indexOf( key_param );
    if( index != -1 ) {
        values[index] = value_param;
        return true;
    } else {
        return false;
    }
}


//return a QList with all keys
template <class T1, class T2>
QList<T1> Manager<T1,T2>::getKeys() const {
    return keys;
}


//return a QList with all values
template <class T1, class T2>
QList<T1> Manager<T1,T2>::getValues() const {
    return values;
}

//return a QMap with all values
template <class T1, class T2>
QMap<T1,T2> Manager<T1,T2>::getMap() const {
    QMap<T1,T2> map;

    for( int i = 0; i < keys.size(); ++i ) {
        map[keys.at(i)] = values.at(i);
    }

    return map;
}

//set values and keys by passing a QMap
template <class T1, class T2>
void Manager<T1,T2>::setMap( QMap<T1,T2> map_param ) {
    QMapIterator<QString, int> i(map_param);

    //clearing keys and values
    keys.clear();
    values.clear();

    while (i.hasNext()) {
        i.next();
        keys.push_back( i.key() );
        values.push_back( i.value() );
    }
}

//push back a key and a value.
//If key already exists, it returns false;
template <class T1, class T2>
bool Manager<T1,T2>::push_back( T1 key_param, T2 value_param ) {
    if( keys.indexOf( key_param ) == -1 ) {
        keys.push_back( key_param );
        values.push_back( value_param );
        return true;
    }
    return false;
}

//screen dump of all data in the Manager. only for debug purpouse
template <class T1, class T2>
void Manager<T1,T2>::debug_dump() {
    qDebug() << "KEYS SIZE: " << keys.size();
    qDebug() << "VALUES SIZE: " << values.size();
    qDebug() << "__-- ELEMENTS --__";
    for( int i = 0; i < keys.size(); i++ ) {
        qDebug() << "KEY: " << keys.at(i) << "  VALUE:" << values.at(i);
    }
    qDebug() << "--______________--";
}


/*
 * Class name:          ManagerFromFile
 * Description:         Class created to handle a map from a file. It is reused
 *                      to build LanguageManager and configManager
 *
 */
class ManagerFromFile : public Manager<QString,QString> {
    public:
        ManagerFromFile();                          //default constructor
        ManagerFromFile( QString filename_str = "config.ini" );    //main constructor from filename

        ManagerFromFile( const ManagerFromFile& other );
        ManagerFromFile& operator=( const ManagerFromFile& other );

        void setFilename( QString filename_str );
        QString getFilename() const;

        //reading - writing from/to file
        bool load();
        bool save();
    protected:
        QString filename;
};



/*
 * Class name:          Manager<T1,T2>
 * Description:         Class created to handle a map. It is reused
 *                      to build LanguageManager and configManager
 *

class LanguageManager : public ManagerFromFile {
    public:

        //enum for identify all translation strings
        enum TRL : int {
            NEW_ACCOUNT_BUTTON = 0,
            SETTINGS_BUTTON,
            ACCOUNT_NAME_LINE_LABEL,
            ACCOUNT_PASSWORD_LINE_LABEL,
            ACCOUNT_NAME_LINE_TOOLTIP,
            ACCOUNT_PASSWORD_LINE_TOOLTIP,
            LOGIN_BUTTON,
            PASSWORD_LINE_PLACEHOLDER,
            SELECT_ACCOUNT,
            SETTINGS,
            ACCOUNTS_FOLDER,
            BACKUP_FOLDER,
            COPY_FILES_FROM,
            SAVE,
            CANCEL,
            SELECT_FOLDER,
            TEXT,
            TEXT_SIZE,
            TEXT_FONT,
            DEFAULT_FOLDER,
            NEW_ACCOUNT,
            ACCOUNT_NAME,
            PASSWORD,
            REPEAT_PASSWORD,
            ENCRYPTED_ACCOUNT,
            INFO,
            CREATE,
            CRYPTO_INFORMATIONS,
            INFO_CRYPTO_MESSAGE,
            INVALID_ACCOUNT_NAME,
            INVALID_PASSWORD,
            PASSWORDS_DONT_MATCH,
            TRANSLATIONS_STRINGS_NUM
        };


        //languages translated
        enum LANG : int {
            ITALIAN = 0,
            ENGLISH,
            LANGUAGES_NUM
        };


        //default constructor
        LanguageManager() : LanguageManager( LanguageManager::ITALIAN ) {};

        //main constructor
        LanguageManager( int language_id ) : ManagerFromFile( id_to_lang_filename(language_id) ) {
            language = language_id;
        };

        //copy constructor
        LanguageManager( const LanguageManager& other );

        //assignment operator
        LanguageManager& operator=( const LanguageManager& other );

        //getter-setter
        void setLanguageId( int language_id );
        int getLanguageId() const;


        //conversion between filename strings and langauge ids
        static int lang_filename_to_id( QString filename_str );
        static QString id_to_lang_filename( int id_value );

        //all langauges
        static const QStringList languages_filenames;

    protected:
        int language;

};

*/

#endif // MANAGER_H









