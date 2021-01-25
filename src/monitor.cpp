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
 *  Description:    Describes a coment type.
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

bool FileData::operator==( const FileData& other ) {
    return ( filename == other.filename &&
             code_lines == other.code_lines &&
             comment_lines == other.comment_lines &&
             total_lines == other.total_lines &&
             void_lines == other.void_lines &&
             size == other.size &&
             chars == other.chars &&
             language_name == other.language_name
            );
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

    //check if file exists or not
    if( QFile::exists( filename ) ) {
        QFile file( filename );

        //opening file
        if( file.open( QIODevice::ReadOnly ) ) {
            ProgrammingLanguage prog_lang( FilesUtilities::getProgLangName( FilesUtilities::getFileExtension( filename ) ) );
            prog_lang.load();
            qDebug() << FilesUtilities::getProgLangName( FilesUtilities::getFileExtension( filename ) );
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
                    } else if(TextSanitizer::check_string(current_line,TextSanitizer::Void_Alphabet) ) {
                        ++void_lines;
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

View::View( QStringList filenames_list,
            QProgressBar* progress )
{
    foreach( QString file, filenames_list ) {
        data.push_back( FileData() );
        data.last().setFilename( file );
    }
    examinesAll( progress );
}

View::View( QStringList filenames_list,
            QStringList data_strings,
            QDateTime date,
            QProgressBar* progress )
{

    //filenames and data array, must have the same length
    if( filenames_list.size() == data_strings.size() ) {
        date_time = date;

        for( int i = 0; i < filenames_list.size(); ++i ) {
            data.push_back( FileData( filenames_list.at(i),
                                      data_strings.at(i) ) );
        }
    }
}

View::~View() {

}

//copy constructor
View::View( const View& other ) {
    data = other.data;
    date_time = other.date_time;
}

//assignent operator
View& View::operator=( const View& other ) {
    data = other.data;
    date_time = other.date_time;
    return *this;
}

bool View::operator==( const View& other ) {
    return data == other.data;
}

void View::examinesAll( QProgressBar* progress ) {
    date_time = QDateTime::currentDateTime();
    for( int i = 0; i < data.size(); ++i ) {
       data[i].Examines();
       if( progress != nullptr )
       progress->setValue( progress->value() + 1 );
    }
}

QStringList View::getFilenames() const {
    QStringList filenames;
    foreach( FileData file, data ) {
        filenames << file.getFilename();
    }
    return filenames;
}

QList<FileData> View::getData() const {
    return data;
}

QDateTime View::getDateTime() const {
    return date_time;
}

QStringList View::getDataStrings() const {
    QStringList data_strings;
    foreach( FileData file, data ) {
        data_strings << file.getDataString();
    }
    return data_strings;}

FileData View::getFileData( QString filename, bool* ok  ) {

    int index = -1;

    for( int i = 0; i < data.size(); ++i ) {
        if( data.at(i).getFilename() == filename ) {
            index = i;
            break;
        }
    }

    if( ok != nullptr ) {
        *ok = index != -1;
    }

    if( index != -1 ) {
        return data.at( index );
    } else {
        FileData file;
        file.setFilename( filename );
        return file;
    }
}


//add file and examines it
void View::addFile( const QString filename ) {
    data.push_back( FileData(filename) );
}

//add file from other FileData object
void View::addFile( const FileData file ) {
    data.push_back( file );
}

//add file from other
void View::addFile( const QString filename, QString data_string ) {
    data.push_back( FileData(filename, data_string) );
}

//remove file
void View::removeFile( const QString filename ) {
    for( int i = 0; i < data.size(); ++i ) {
        if( data.at(i).getFilename() == filename ) {
            data.removeAt( i );
        }
    }
}




/*  Class:          MonitorSettings
 *  Description:    Managment and saving implementation of monitor settings.
 *                  Data is saved in a specific table of database provided to MonitorSettings
 */


MonitorSettings::MonitorSettings() {
    //db not set
    db = nullptr;


    //loading default settings
    monitor_autosave = true;
    monitor_autosave_every_mins = 5;
    monitor_save_on_closing = false;
    monitor_no_duplicate = false;
}

//constructor with db: it auto loads data from db
MonitorSettings::MonitorSettings( QSqlDatabase* db_ptr ) {
    //loading default settings
    monitor_autosave = true;
    monitor_autosave_every_mins = 5;
    monitor_save_on_closing = false;
    monitor_no_duplicate = false;

    db = db_ptr;

    //load settings from db
    load();
}

//constructor with data. it doesn't perform an autosave.
//(you must set a valid db and then sall save() )
MonitorSettings::MonitorSettings(    const bool autosave_val,
                                     const int autosave_every_mins_val,
                                     const bool monitor_save_on_closing_val,
                                     const bool no_duplicate_val )
{
    //db not set
    db = nullptr;

    monitor_autosave = autosave_val;
    monitor_autosave_every_mins = autosave_every_mins_val;
    monitor_save_on_closing = monitor_save_on_closing_val;
    monitor_no_duplicate = no_duplicate_val;
}


//copy constructor
MonitorSettings::MonitorSettings( const MonitorSettings& other ) {
    monitor_autosave = other.monitor_autosave;
    monitor_autosave_every_mins = other.monitor_autosave_every_mins;
    monitor_save_on_closing = other.monitor_save_on_closing;
    monitor_no_duplicate = other.monitor_no_duplicate;

    //copying db (by address)
    db = other.db;
}

//assignment operator
MonitorSettings& MonitorSettings::operator=( const MonitorSettings& other ) {
    monitor_autosave = other.monitor_autosave;
    monitor_autosave_every_mins = other.monitor_autosave_every_mins;
    monitor_save_on_closing = other.monitor_save_on_closing;
    monitor_no_duplicate = other.monitor_no_duplicate;

    //copying db (by address)
    db = other.db;

    return *this;
}



//save-load functions
bool MonitorSettings::load() {

    //check db
    if( db != nullptr ) {

        QSqlQuery query( *db );

        query.exec("SELECT key, value FROM monitor_settings");

        while ( query.next() ) {
            QString current_key;
            QString current_value;

            current_key = query.record().value(0).toString();
            current_value = query.record().value(1).toString();

            if( current_key == "monitor_autosave" )
                monitor_autosave = current_value.toInt();
            else if( current_key == "monitor_autosave_every_mins" )
                monitor_autosave_every_mins = current_value.toInt();
            else if( current_key == "monitor_save_on_closing" )
                monitor_save_on_closing = current_value.toInt();
            else if( current_key == "monitor_no_duplicate" )
                monitor_no_duplicate = current_value.toInt();
        }

        return true;
    } else {
        return false;
    }
}

bool MonitorSettings::save() {
    //check db
    if( db != nullptr ) {
        QSqlQuery query( *db );

        query.exec( "UPDATE monitor_settings SET value = \""+QString::number(monitor_autosave)+"\" WHERE key = \"monitor_autosave\"");
        query.exec( "UPDATE monitor_settings SET value = \""+QString::number(monitor_autosave_every_mins)+"\" WHERE key = \"monitor_autosave_every_mins\"");
        query.exec( "UPDATE monitor_settings SET value = \""+QString::number(monitor_save_on_closing)+"\" WHERE key = \"monitor_save_on_closing\"");
        query.exec( "UPDATE monitor_settings SET value = \""+QString::number(monitor_no_duplicate)+"\" WHERE key = \"monitor_no_duplicate\"");


        return true;
    } else {
        return false;
    }
}


// getter - setter methods
bool MonitorSettings::getAutosave() const {
    return monitor_autosave;
}

int MonitorSettings::getAutosaveEveryMins() const {
    return monitor_autosave_every_mins;
}

bool MonitorSettings::getMonitorSaveOnClosing() const {
    return monitor_save_on_closing;
}

bool MonitorSettings::getNoDuplicate() const {
    return monitor_no_duplicate;
}

void MonitorSettings::setAutosave( const bool autosave_val ) {
    monitor_autosave = autosave_val;
}

void MonitorSettings::setAutosaveEveryMins( const int autosave_every_mins_val ) {
    monitor_autosave_every_mins = autosave_every_mins_val;
}

void MonitorSettings::setMonitorSaveOnClosing( const bool monitor_save_on_closing_val ) {
    monitor_save_on_closing = monitor_save_on_closing_val;
}

void MonitorSettings::setNoDuplicate( const bool no_duplicate_val ) {
    monitor_no_duplicate = no_duplicate_val;
}

QSqlDatabase* MonitorSettings::getDatabase() const {
    return db;
}

void MonitorSettings::setDatabase( QSqlDatabase* db_var ){
    db = db_var;
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

void Monitor::checkFilesFormat() {

    QStringList extensions;
    QStringList unknown_extensions;

    //reading current file extensions
    for( int i = 0; i < current_files.size(); ++i ) {
        QString current_extension;

        current_extension = FilesUtilities::getFileExtension( current_files.at(i) );

        if( extensions.indexOf( current_extension ) == -1 ) {
            extensions.append( current_extension );
        }
    }

    //check if exists some programming language with current extensions or not
    for( int i = 0; i < extensions.size(); ++i ) {
        if( FilesUtilities::getProgLangName( extensions.at(i) ) == "" ) {
            unknown_extensions.append( extensions.at(i) );
        }
    }

    //if there are unknown extensions
    if( unknown_extensions.size() > 0 ) {
        QString error_msg;

        error_msg = "Unknown file formats: <ul><b>";
        for( int i = 0; i < unknown_extensions.size(); ++i ) {
            error_msg += "<li>."+unknown_extensions.at(i) + "</li>";
        }
        error_msg = error_msg.mid( 0, error_msg.size() - 2 );
        error_msg += "</b></ul><br>\nEdit <b>Settings</b> to allow Code Monitor to handle these files.";

        //Error: unknown formats
        throw Error( Error::ERROR_CODE::UNKNOWN_ESTENSIONS, error_msg );
    }
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

View* Monitor::viewAt( int pos ) {
    return &views[pos];
}
QStringList Monitor::getCurrentFilespath() const {
    return current_files;
}

void Monitor::addFilespath( const QStringList files ) {
    foreach( QString file, files ) {
        if( current_files.indexOf( file ) == -1 ) {
            current_files.push_back( file );

            FileData file_data;
            file_data.setFilename( file );
            for( int i = 0; i < views.size(); ++i ) {
                views[i].addFile( file_data );
            }
        }
    }
}

void Monitor::removeFilespath( const QStringList files ) {
    foreach( QString file, files ) {
        if( current_files.indexOf( file ) != -1 ) {
            current_files.removeAt( current_files.indexOf( file ) );

            for( int i = 0; i < views.size(); ++i ) {
                views[i].removeFile( file );
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

        //file columns name
        QStringList columns;

        query.exec( "SELECT ID_file, file_path FROM monitor_files" );


        QString query_text = "SELECT  ";
        while( query.next() ) {
            columns.push_back( "file"+query.record().value(0).toString() );
            current_files.push_back(query.record().value(1).toString());
            query_text += columns.last()+",";
        }
        query_text += "date FROM monitor_data";
        query.exec( query_text );
        while( query.next() ) {
            QStringList files_data_strings;
            int i;
            for( i = 0; i < current_files.size(); ++i ) {
                files_data_strings << query.record().value(i).toString();
            }

            views.push_back( View( current_files,
                                   files_data_strings,
                                   QDateTime::fromString( query.record().value(i).toString(),
                                                          "yyyy-MM-dd-hh-mm-ss-zzz" ) ) );
        }
        //SELECT  FROM monitor_data

        checkFilesFormat();

        return true;
    } else {
        //database isn't open
        return false;
    }

}

//monitor all files
void Monitor::MonitorNow( QProgressBar* progress ) {
    View newView( current_files, progress );
    MonitorSettings settings = getSettings();

    //check if option: getNoDuplicate is enabled
    if( settings.getNoDuplicate() ) {

        //check if current data is duplicated
        if( !(newView == views.at( views.size() - 1 )) ) {
            views.push_back( newView );
        }
    } else {
        views.push_back( newView );
    }

}

int Monitor::size() {
    return views.size();
}

//remove a view from views array
bool Monitor::removeView( int pos ) {

    //check if pos is in range
    if( pos >= 0 && pos < views.size() ) {

        views.removeAt( pos );

        return true;

    } else {

        return false;

    }
}

//save data to database file
bool Monitor::saveData() {


    //check if db is opened
    if( db->isOpen() ) {

        //progress dialog for showing saving progress
        QProgressDialog progress(tr("Saving %1 monitor...").arg( "\""+ name + "\"" ), tr("Cancel"), 0, current_files.size()+views.size(), nullptr);
        progress.setWindowModality(Qt::WindowModal);

        //progress bar counter
        int prog_count = 0;

        //files ids from tables
        QStringList files_id_from_files;

        //query object
        QSqlQuery query( *db );

        //string used to contains complex queries
        QString query_text;

        //clearing old monitor_files table
        query.exec( "DROP TABLE monitor_files");
        query.exec( "CREATE TABLE monitor_files ("
                    "ID_file INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE,"
                    "file_path TEXT NOT NULL UNIQUE"
                    ")" );

        //filling monitor_files table
        foreach( QString filename, current_files ) {
            query.exec( "INSERT INTO monitor_files (file_path) VALUES (\"" + filename + "\")");
            progress.setValue(++prog_count);
        }

        //creating columns name, ex: file1, file2, ..., file45
        query.exec( "SELECT ID_file from monitor_files");
        while( query.next() ) {
            files_id_from_files.push_back( "file"+query.record().value(0).toString() );
        }

        //clearing monitor_data table, and creating a new table with all needed columns (one for each file to save)
        query.exec( "DROP TABLE monitor_data" );
        query_text += "CREATE TABLE monitor_data ("
                      "ID_view INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE,"
                      "date TEXT NOT NULL UNIQUE";
        foreach( QString file, files_id_from_files ) {
            query_text += ", "+file+" TEXT NOT NULL";
        }
        query_text += ")";
        query.exec( query_text );

        //filling monitor_data
        foreach( View current_view, views ) {
            query_text = "INSERT INTO monitor_data (date";
            foreach( QString file, files_id_from_files ) {
                query_text += "," + file;
            }
            query_text += ") VALUES (\""+current_view.getDateTime().toString( "yyyy-MM-dd-hh-mm-ss-zzz")+"\"";

            bool fileIsPresent;

            foreach( QString filename, current_files ) {

                FileData current_file = current_view.getFileData( filename, &fileIsPresent );
                if( fileIsPresent ) {
                    query_text += ",\""+current_file.getDataString()+"\"";
                } else {
                    query_text += ",\""+FileData().getDataString()+"\"";
                }

            }

            query_text += ")";
            query.exec(query_text);
            progress.setValue(++prog_count);
        }
        progress.setValue( views.size() + current_files.size() );

        return true;
    } else {
        QMessageBox::critical( nullptr, tr("Error"), tr("Error: Couldn't save monitor." ) );
        return false;
    }
}

MonitorSettings Monitor::getSettings() const {

    //check if database is opened or not
    if( db->isOpen() ) {
        //database is open


        return MonitorSettings(db);
    } else {
        //database isn't open
        return MonitorSettings();
    }
}








