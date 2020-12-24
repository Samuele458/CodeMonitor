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
#ifndef ERROR_H
#define ERROR_H
#include <QString>

/*
 * Author:      Samuele Girgenti
 * Date:        24  /  12  /  2020
 * Description: Class to hande errors
 */
class Error {
    private:
        //error code
        int code;

        //error message
        QString message;

    public:
        //default constructor
        Error( int code, QString message );

        //copy constructor
        Error( const Error& other );

        //assigment operator
        Error& operator=( const Error& other );


        //error codes
        enum ERROR_CODE {
            UNKNOWN_ESTENSIONS
        };

        // GETTER - SETTER methods

        int getCode() const;
        QString getMessage() const;

        void setCode( int code );
        void setMessage( QString message );

};

#endif // ERROR_H
