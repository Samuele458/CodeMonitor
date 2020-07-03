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

#ifndef MONITOR_H
#define MONITOR_H
#include <QString>
#include <QStringList>
#include <QFile>
#include <QDir>
#include <QList>
#include <QDebug>
#include <QTextStream>
#include <QSettings>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDateTime>
#include <QMessageBox>
#include <QProgressDialog>

#include "common/filesutility.h"
#include "common/textsanitizer.h"


/*  Class:          Comment
 *  Description:    Describes a coment type
 */
class Comment {
    public:
        Comment() { };
        Comment( QString single_line_str,
                 QString multi_line_start_str,
                 QString multi_line_end_str );
        ~Comment() { };

        //copy constructor
        Comment( const Comment& other );

        //assignment operator
        Comment& operator=( const Comment& other );

        //getter - setter methods
        QString getSingleLine() const;
        QString getMultiLineStart() const;
        QString getMultiLineEnd() const;
        void setSingleLine( const QString single_line_str );
        void setMultiLineStart( const QString multi_line_start_str );
        void setMultiLineEnd( const QString multi_line_end_str );

    protected:
        QString single_line;        //initial string of single line comment
        QString multi_line_start;   //initial string of multi line comment
        QString multi_line_end;     //end string of multi line string
};


/*  Class:          ProgrammingLanguage
 *  Description:    Programming Languages informations. It contains comments informations
 */
class ProgrammingLanguage : public Comment {

    public:
        ProgrammingLanguage() { };

        ProgrammingLanguage( QString name_str );

        ~ProgrammingLanguage();

        //copy constructor
        ProgrammingLanguage( const ProgrammingLanguage& other );

        //assignment operator
        ProgrammingLanguage& operator=( const ProgrammingLanguage& other );

        //getter - setter methods
        QString getName() const;
        QStringList getExtensions() const;
        void setName( QString name_str );
        void setExtensions( QStringList extensions_list );

        //load parameters from
        bool load();

    protected:
        QString name;
        QStringList extentions;

};

/*  Class:          FileData
 *  Description:    Manage data for one file
 */
class FileData {
    public:
        FileData();
        FileData( QString filename_str );
        FileData( QString filename_str, QString data_str );
        ~FileData();

        //copy constructor
        FileData( const FileData& other );

        //assignment operator
        FileData& operator=( const FileData& other );

        bool Examines();          //examin file
        bool wasFileExamined();

        //evaluate programming language name
        void evaluateProgLang();

        //getter-setter methods
        void setFilename( QString filename_str );
        QString getFilename() const;

        unsigned int getCodeLines() const;
        unsigned int getCommentLines() const;
        unsigned int getTotalLines() const;
        unsigned int getVoidLines() const;
        unsigned int getSize() const;
        unsigned int getChars() const;
        void setCodeLines( unsigned int value );
        void setCommentLines( unsigned int value );
        void setTotalLines( unsigned int value );
        void setVoidLines( unsigned int value );
        void setSize( unsigned int value );
        void setChars( unsigned int value );


        QString getDataString() const;
        void fillByData( QString data_str);

    protected:
        QString filename;

        unsigned int code_lines;        //numeber of code lines
        unsigned int comment_lines;     //number of comment lines
        unsigned int total_lines;       //number of total lines
        unsigned int void_lines;
        unsigned int size;              //size of file (in byte)
        unsigned int chars;             //number of total chars
        QString language_name;

        bool file_examined;

};

/*  Class:          View
 *  Description:    Single data view of multiple files
 */
class View {
    public:
        View();
        View( QStringList filenames_list );
        View( QStringList filenames_list,
              QStringList data_strings,
              QDateTime date );
        ~View();

        View( const View& other );
        View& operator=( const View& other );

        //examines all files
        void examinesAll();

        //getter - setter methods
        QStringList getFilenames() const;
        QList<FileData> getData() const;
        QDateTime getDateTime() const;
        QStringList getDataStrings() const;
        FileData getFileData( QString filename, bool* ok = nullptr );

        //add file and examines it
        void addFile( const QString filename );

        //add file from other FileData object
        void addFile( const FileData file );

        //add file from other
        void addFile( const QString filename, QString data_string );

    protected:
        QList<FileData> data;
        QDateTime date_time;


};

/*  Class:          Monitor
 *  Description:    Describes a coment type
 */
class Monitor {
    Q_OBJECT
    public:
        Monitor( QString monitor_name_str );
        ~Monitor();

        //copy constructor
        Monitor( const Monitor& other );

        //assignment operator
        Monitor& operator=( const Monitor& other );


        //getter  setter methods
        QString getMonitorName() const;
        void setMonitorName( const QString name_str );

        QList<View> getAllViews() const;

        QStringList getCurrentFilespath() const;
        void addFilespath( const QStringList files );

        //monitor all files
        void MonitorNow();

        //--- other ---
        bool load();

        bool saveData();



    protected:
        QString name;
        QStringList current_files;
        QList<View> views;

        QSqlDatabase* db;



};

#endif
