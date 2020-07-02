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

#include "monitor.h"

/*  Class:          Comment
 *  Description:    Describes a coment type
 */
Comment::Comment( QString single_line_str,
                  QString multi_line_start_str,
                  QString multi_line_end_str )
{
    single_line = single_line_str;
    multi_line_start = multi_line_start_str;
    multi_line_end = multi_line_end_str;
}

//copy constructor
Comment::Comment( const Comment& other ) {
    single_line = other.single_line;
    multi_line_end = other.multi_line_end;
    multi_line_start = other.multi_line_start;
}

//assignment operator
Comment& Comment::operator=( const Comment& other ) {
    single_line = other.single_line;
    multi_line_end = other.multi_line_end;
    multi_line_start = other.multi_line_start;

    return *this;
}


//getter - setter methods
QString Comment::getSingleLine() const {
    return single_line;
}

QString Comment::getMultiLineStart() const {
    return multi_line_start;
}

QString Comment::getMultiLineEnd() const {
    return multi_line_end;
}

void Comment::setSingleLine( const QString single_line_str ) {
    single_line = single_line_str;
}

void Comment::setMultiLineStart( const QString multi_line_start_str ) {
    multi_line_start = multi_line_start_str;
}

void Comment::setMultiLineEnd( const QString multi_line_end_str ) {
    multi_line_end = multi_line_end_str;
}


// ----- PROGRAMMING LANGUAGE CLASS -----
/*  Class:          ProgrammingLanguage
 *  Description:    Programming Languages informations. It contains comments informations
 */

ProgrammingLanguage::ProgrammingLanguage( QString name_str ) :
    Comment(),
    name( name_str )
{

}

ProgrammingLanguage::~ProgrammingLanguage() {

}

//copy constructor
ProgrammingLanguage::ProgrammingLanguage( const ProgrammingLanguage& other ) :
    Comment( other )
{
    name = other.name;
    extentions = other.extentions;
}

//assignment operator
ProgrammingLanguage& ProgrammingLanguage::operator=( const ProgrammingLanguage& other ) {
    Comment::operator=( other );
    name = other.name;
    extentions = other.extentions;

    return *this;
}

//getter - setter methods
QString ProgrammingLanguage::getName() const {
    return name;
}

QStringList ProgrammingLanguage::getExtensions() const {
    return extentions;
}

void ProgrammingLanguage::setName( QString name_str ) {
    name = name_str;
}

void ProgrammingLanguage::setExtensions( QStringList extensions_list ) {
    extentions = extensions_list;
}

//load programming language data from file
bool ProgrammingLanguage::load() {
    QSettings prog_langs( QDir::currentPath() + "/programming_languages.ini", QSettings::IniFormat );
    if( prog_langs.childGroups().indexOf( name ) != -1 ) {
        prog_langs.beginGroup( name );
        single_line = prog_langs.value( "single_line_comment" ).toString();
        multi_line_start = prog_langs.value( "multi_line_comment_start" ).toString();
        multi_line_end = prog_langs.value( "multi_line_comment_end" ).toString();
        extentions = prog_langs.value( "files_extensions" ).toString().split( " " );
        prog_langs.endGroup();
        return true;
    } else {
        //programming language not found
        return false;
    }

}




//----- FILEDATA CLASS -----
/*  Class:          FileData
 *  Description:    Manage data for one file
 */
FileData::FileData() {
    file_examined = false;

    filename = "";

    code_lines = 0;
    comment_lines = 0;
    total_lines = 0;
    void_lines = 0;
    size = 0;
    chars = 0;
    language_name = "";
}

FileData::FileData( QString filename_str ) :
    filename( filename_str )
{
    Examines();
}

FileData::FileData( QString filename_str, QString data_str ) :
    filename( filename_str )
{
    fillByData( data_str );
}

FileData::~FileData() {

}

//copy constructor
FileData::FileData( const FileData& other ) {
    filename = other.filename;
    code_lines = other.code_lines;
    comment_lines = other.comment_lines;
    total_lines = other.total_lines;
    void_lines = other.void_lines;
    size = other.size;
    chars = other.chars;
    language_name = other.language_name;
    file_examined = other.file_examined;
}

//assignment operator
FileData& FileData::operator=( const FileData& other ) {
    filename = other.filename;
    code_lines = other.code_lines;
    comment_lines = other.comment_lines;
    total_lines = other.total_lines;
    void_lines = other.void_lines;
    size = other.size;
    chars = other.chars;
    language_name = other.language_name;
    file_examined = other.file_examined;

    return *this;
}


//examines file
bool FileData::Examines() {

    //resetting data variables.
    code_lines = 0;
    comment_lines = 0;
    total_lines = 0;
    void_lines = 0;
    size = 0;
    chars = 0;
    language_name = "";

    if( QFile::exists( filename ) ) {
        QFile file( filename );
        if( file.open( QIODevice::ReadOnly ) ) {
            ProgrammingLanguage prog_lang( FilesUtilities::getProgLangName( FilesUtilities::getFileExtension( filename ) ) );
            prog_lang.load();

            while( !file.atEnd() ) {
                QString current_line = file.readLine();
                int sl_index = current_line.indexOf( prog_lang.getSingleLine() );
                if( sl_index > 0 ) {
                    if( TextSanitizer::check_string( current_line.mid( 0, sl_index ), TextSanitizer::TYPES::VOID ) ) {
                        ++comment_lines;
                    } else {
                        ++code_lines;

                    }
                } else if( sl_index == 0 ) {
                    ++comment_lines;

                } else  {
                    int ml_index = current_line.indexOf( prog_lang.getMultiLineStart() );
                    if( ml_index >= 0 ) {
                        if( ml_index == 0 ) {
                            ++comment_lines;
                            unsigned int start_lines = total_lines;
                            do {
                                int ml_end_index;
                                if( start_lines == total_lines )
                                    ml_end_index = current_line.indexOf( prog_lang.getMultiLineEnd(), ml_index + prog_lang.getMultiLineStart().size() );
                                else ml_end_index = current_line.indexOf( prog_lang.getMultiLineEnd() );
                                if( ml_end_index != -1 ) {
                                    break;
                                } else {
                                    ++total_lines;
                                    ++comment_lines;
                                    current_line = file.readLine();
                                }
                            } while( !file.atEnd() );
                        } else if( ml_index > 0 ) {

                        }
                    } else {
                        ++code_lines;
                    }
                }
                total_lines++;
            }
        }
        file_examined = true;
    } else {
        file_examined = false;
    }


    return file_examined;
}   //examin file


//check if file was examined
//If it returns false, it means that file couldn't be exmined. Es:
//  -File doesn't exist
//  -File isn't a text file
bool FileData::wasFileExamined() {
    return file_examined;
}

//evaluate programming language name
void FileData::evaluateProgLang() {
    ProgrammingLanguage prog_lang( FilesUtilities::getProgLangName( FilesUtilities::getFileExtension( filename ) ) );
    prog_lang.load();
    language_name = prog_lang.getName();
}


//    getter  -  setter    methods

void FileData::setFilename( QString filename_str ) {
    filename = filename_str;
}

QString FileData::getFilename() const {
    return filename;
}

unsigned int FileData::getCodeLines() const {
    return code_lines;
}

unsigned int FileData::getCommentLines() const {
    return comment_lines;
}

unsigned int FileData::getTotalLines() const {
    return total_lines;
}

unsigned int FileData::getVoidLines() const {
    return void_lines;
}


unsigned int FileData::getSize() const {
    return size;
}

unsigned int FileData::getChars() const {
    return chars;
}

void FileData::setCodeLines( unsigned int value ) {
    code_lines = value;
}

void FileData::setCommentLines( unsigned int value ) {
    comment_lines = value;
}

void FileData::setTotalLines( unsigned int value ) {
    total_lines = value;
}

void FileData::setVoidLines( unsigned int value ) {
    void_lines = value;
}

void FileData::setSize( unsigned int value ) {
    size = value;
}

void FileData::setChars( unsigned int value ) {
    chars = value;
}

//return all Filedata data in a string fromatted
QString FileData::getDataString() const {
    return QString::number( code_lines ) + "-" +
           QString::number( comment_lines ) + "-" +
           QString::number( total_lines ) + "-" +
           QString::number( void_lines ) + "-" +
           QString::number( size ) + "-" +
           QString::number( chars );
}


void FileData::fillByData( QString data_str) {
    QStringList values = data_str.split("-");
    code_lines = values.at(0).toUInt();
    comment_lines = values.at(1).toUInt();
    total_lines = values.at(2).toUInt();
    void_lines = values.at(3).toUInt();
    size = values.at(4).toUInt();
    chars = values.at(5).toUInt();

}



//----- VIEW CLASS -----
/*  Class:          View
 *  Description:    Single data view of multiple files
 */
View::View() {

}

View::View( QStringList filenames_list ) {
    foreach( QString file, filenames_list ) {
        data.push_back( QFile)
    }
    examinesAll();
}

View::View( QStringList filenames_list,
            QStringList data_strings,
            QDateTime date )
{
    date_time = date;

}

View::~View() {

}

//copy constructor
View::View( const View& other ) {
    filenames = other.filenames;
    data = other.data;
    data_strings = other.data_strings;
    date_time = other.date_time;
}

//assignent operator
View& View::operator=( const View& other ) {
    filenames = other.filenames;
    data = other.data;
    data_strings = other.data_strings;
    date_time = other.date_time;
    return *this;
}

void View::examinesAll() {
    qDebug() << "ESAMIANDO UNA VIEW ---";
    data.clear();
    data_strings.clear();
    date_time = QDateTime::currentDateTime();
    foreach( QString filename, filenames ) {
        FileData current_file( filename );
        if( !current_file.Examines() ) {
            qDebug() << "Error: " << filename << "mm";
        }
        data.push_back( current_file );
        data_strings.push_back( current_file.getDataString() );
    }
    qDebug() << "DATA STRING: " << data_strings;
    //...
}

QStringList View::getFilenames() const {
    return filenames;
}

QList<FileData> View::getData() const {
    return data;
}

QDateTime View::getDateTime() const {
    return date_time;
}

QStringList View::getDataStrings() const {
    return data_strings;
}

FileData View::getFileData( QString filename, bool* ok  ) {
    if( filenames.indexOf( filename ) != -1 ) {
        if( ok != nullptr )
            *ok = true;
        return data.at( filenames.indexOf( filename ) );
    } else {
        if( ok != nullptr )
            *ok = false;
        return FileData();
    }
}


void View::addFile( const QString filename ) {
    data.push_back( FileData() );
    data_strings.push_back( data.last().getDataString() );
}




/*  Class:          Monitor
 *  Description:    Describes a coment type
 */

Monitor::Monitor( QString monitor_name_str ) {
    name = monitor_name_str;
    db = new QSqlDatabase;
    *db = QSqlDatabase::database( "main" );
    db->setDatabaseName( QDir::currentPath() + "/data/monitors/" + name + ".db" );
    db->open();
    load();
}

Monitor::~Monitor() {

}

//copy constructor
Monitor::Monitor( const Monitor& other ) {
    name = other.name;
    current_files = other.current_files;
    views = other.views;
}

//assignment operator
Monitor& Monitor::operator=( const Monitor& other ) {
    name = other.name;
    current_files = other.current_files;
    views = other.views;

    return *this;
}

//getter  setter methods
QString Monitor::getMonitorName() const {
    return name;
}

void Monitor::setMonitorName( const QString name_str ) {
    name = name_str;
}

QList<View> Monitor::getAllViews() const {
    return views;
}

QStringList Monitor::getCurrentFilespath() const {
    return current_files;
}

void Monitor::addFilespath( const QStringList files ) {
    foreach( QString file, files ) {
        if( current_files.indexOf( file ) == -1 ) {
            current_files.push_back( file );
            if( db->isOpen() ) {
                QSqlQuery query( *db );

                query.exec( "INSERT INTO monitor_files (file_path) "
                            "VALUES (\"" + file + "\") "  );
            }
        }
    }
}

//load data from db
bool Monitor::load() {

    //check if db was correctly opened
    if( db->isOpen() ) {
        //database is open
        QSqlQuery query( *db );

        query.exec( "SELECT file_path FROM monitor_files" );
        while( query.next() ) {
            current_files.push_back(query.record().value(0).toString());
        }

        return true;
    } else {
        //database isn't open
        return false;
    }

}

//monitor all files
void Monitor::MonitorNow() {
    qDebug() << QDateTime::currentDateTime().toString( "yyyy-MM-dd-hh-mm-ss-zzz");
    View newView( current_files );
    views.push_back( newView );
    qDebug() << newView.getDataStrings();
}

//save data to database file
bool Monitor::saveData() {


    //check if db is opened
    if( db->isOpen() ) {

        //files ids from tables
        QStringList files_id_from_files;


        QSqlQuery query( *db );


        query.exec( "SELECT ID_file from monitor_files");
        while( query.next() ) {
            files_id_from_files.push_back( "file"+query.record().value(0).toString() );
        }

        QString query_text;

        query_text += "CREATE TABLE monitor_data ("
                      "ID_view INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE,"
                      "date TEXT NOT NULL UNIQUE";
        foreach( QString file, files_id_from_files ) {
            query_text += ", "+file+" TEXT NOT NULL";
        }
        query_text += ")";
        query.exec( "DROP TABLE monitor_data" );
        query.exec( query_text );

        foreach( View current_view, views ) {
            query_text = "INSERT INTO monitor_data (date";
            foreach( QString file, files_id_from_files ) {
                query_text += "," + file;
            }
            query_text += ") VALUES (\""+current_view.getDateTime().toString( "yyyy-MM-dd-hh-mm-ss-zzz")+"\"";
            foreach( QString data, current_view.getDataStrings() ) {
                query_text += ",\""+data+"\"";
            }
            query_text += ")";
            qDebug() << query_text << current_view.getDataStrings().size();
            qDebug() << query.exec(query_text);
        }

        return true;
    } else {
        return false;
    }
}








