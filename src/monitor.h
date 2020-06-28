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

#include "common/filesutility.h"

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

class FileData {
    public:
        FileData();
        FileData( QString filename_str );
        ~FileData();

        //copy constructor
        FileData( const FileData& other );

        //assignment operator
        FileData& operator=( const FileData& other );

        bool Examines();          //examin file
        bool wasFileExamined();
        bool isTextFile();

        void setFilename( QString filename_str );
        QString getFilename() const;

        unsigned int getCodeLines() const;
        unsigned int getCommentLines() const;
        unsigned int getTotalLines() const;
        unsigned int getSize() const;
        unsigned int getChars() const;


    protected:
        QString filename;

        unsigned int code_lines;        //numeber of code lines
        unsigned int comment_lines;     //number of comment lines
        unsigned int total_lines;       //number of total lines
        unsigned int size;              //size of file (in byte)
        unsigned int chars;             //number of total chars
        QString language_name;

        bool file_examined;
        bool is_text_file;

};

class View {
    public:
        View();
        View( QStringList filenames_list );
        ~View();

        View( const View& other );
        View& operator=( const View& other );

        void examinesAll();

        QStringList getFilenames() const;
        QList<FileData> getData() const;

    protected:
        QStringList filenames;
        QList<FileData> data;


};

class Monitor {

};

#endif
