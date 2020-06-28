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


ProgrammingLanguage::ProgrammingLanguage( QString name_str,
                                          QString single_line_str,
                                          QString multi_line_start_str,
                                          QString multi_line_end_str,
                                          QStringList extentions_list ) :
    Comment( single_line_str,
             multi_line_start_str,
             multi_line_end_str ),
    name( name_str ),
    extentions( extentions_list )
{

}


ProgrammingLanguage::ProgrammingLanguage( QString name_str,
                                          Comment comment,
                                          QStringList extensions_list ) :
    Comment( comment ),
    name( name_str ),
    extentions( extensions_list )
{

}

ProgrammingLanguage::~ProgrammingLanguage() {

}

//copy constructor
ProgrammingLanguage::ProgrammingLanguage( const ProgrammingLanguage& other ) {
    name = other.name;
    extentions = other.extentions;
}

//assignment operator
ProgrammingLanguage& ProgrammingLanguage::operator=( const ProgrammingLanguage& other ) {
    name = other.name;
    extentions = other.extentions;

    return *this;
}

//getter - setter methods
QString ProgrammingLanguage::getName() const {
    return name;
}

QStringList ProgrammingLanguage::getExtentions() const {
    return extentions;
}

void ProgrammingLanguage::setName( QString name_str ) {
    name = name_str;
}

void ProgrammingLanguage::setExtentions( QStringList extensions_list ) {
    extentions = extensions_list;
}




//----- FILEDATA CLASS -----

FileData::FileData() {
    file_examined = false;
    filename = "";
    is_text_file = false;

    code_lines = 0;
    comment_lines = 0;
    total_lines = 0;
    size = 0;
    chars = 0;
    language_name = "";
}

FileData::FileData( QString filename_str ) :
    filename( filename_str )
{
    Examines();
}

FileData::~FileData() {

}

//copy constructor
FileData::FileData( const FileData& other ) {
    filename = other.filename;
    code_lines = other.code_lines;
    comment_lines = other.comment_lines;
    total_lines = other.total_lines;
    size = other.size;
    chars = other.chars;
    language_name = other.language_name;
    file_examined = other.file_examined;
    is_text_file = other.is_text_file;
}

//assignment operator
FileData& FileData::operator=( const FileData& other ) {
    filename = other.filename;
    code_lines = other.code_lines;
    comment_lines = other.comment_lines;
    total_lines = other.total_lines;
    size = other.size;
    chars = other.chars;
    language_name = other.language_name;
    file_examined = other.file_examined;
    is_text_file = other.is_text_file;

    return *this;
}


//examines file
bool FileData::Examines() {

    code_lines = 0;
    comment_lines = 0;
    total_lines = 0;
    size = 0;
    chars = 0;
    language_name = "";

    qDebug() << "EXAMINING";
    QFile file( filename );
    if( file.open( QIODevice::ReadOnly ) ) {
        while( !file.atEnd() ) {
            qDebug() << file.readLine();
            code_lines++;
        }
        qDebug() << "LINEE TOTALI " << code_lines;

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

//check if file is text file
bool FileData::isTextFile() {
    return is_text_file;
}

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
    return code_lines + comment_lines;
}

unsigned int FileData::getSize() const {
    return size;
}

unsigned int FileData::getChars() const {
    return chars;
}

//----- VIEW CLASS -----
View::View() {

}

View::View( QStringList filenames_list ) {
    filenames = filenames_list;
    examinesAll();
}

View::~View() {

}

//copy constructor
View::View( const View& other ) {
    filenames = other.filenames;
    data = other.data;
}

//assignent operator
View& View::operator=( const View& other ) {
    filenames = other.filenames;
    data = other.data;
    return *this;
}

void View::examinesAll() {
    data.clear();
    //...
}

QStringList View::getFilenames() const {
    return filenames;
}

QList<FileData> View::getData() const {
    return data;
}
