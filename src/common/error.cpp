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

#include "common/error.h"

//default constructor
Error::Error( int code, QString message ) {
    this->code = code;
    this->message = message;
}

//copy constructor
Error::Error( const Error& other ) {
    code = other.code;
    message = other.message;
}

//assigment operator
Error& Error::operator=( const Error& other ) {
    code = other.code;
    message = other.message;

    return *this;
}


// GETTER - SETTER methods

int Error::getCode() const {
    return code;
}

QString Error::getMessage() const {
    return message;
}

void Error::setCode( int code ) {
    this->code = code;
}

void Error::setMessage( QString message ) {
    this->message = message;
}
