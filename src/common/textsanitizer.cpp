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

#include "textsanitizer.h"

/*
 * Author:      Samuele Girgenti
 * Date:        11  /  06  /  2020
 * Description: Class to sanitize ancd check strings of text
 */


//alphabets
const QString TextSanitizer::Digit_Alphabet = "0123456789";
const QString TextSanitizer::Letter_Alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const QString TextSanitizer::Extra_Symbol_Alphabet = "#-@+*/€.,";
const QString TextSanitizer::Extra_Letter_Alphabet = "èùàòì";
const QString TextSanitizer::Void_Alphabet = " \t\r\n";
const QStringList TextSanitizer::all_alphabets = ( QStringList() << TextSanitizer::Digit_Alphabet <<
                                                                    TextSanitizer::Letter_Alphabet <<
                                                                    TextSanitizer::Extra_Symbol_Alphabet <<
                                                                    TextSanitizer::Extra_Letter_Alphabet <<
                                                                    TextSanitizer::Void_Alphabet );


//verify that the input char is contained in the alphabet represented by the bitmask (type)
bool TextSanitizer::check_char( const QChar input, const int type ) {
    int hold_type = type;

    for ( int i = 0; i < types_num; ++i ) {
        if( hold_type % 2 == 1 ) {
            if( !check_char( input, all_alphabets.at(i) )  ) {
                return false;
            }
        }
        hold_type /= 2;
    }
    return true;
}


//verify that the input char is contained in the alphabet
bool TextSanitizer::check_char( const QChar input, const QString& alphabet ) {
    return ( alphabet.indexOf( input ) != NOT_FOUND );
}


bool TextSanitizer::check_string( const QString& input, const int type ) {
    return check_string( input, craft_alphabet( type ) );
}

//verify that all chars in input string are contained in the alphabet
bool TextSanitizer::check_string( const QString& input, const QString& alphabet ) {
    for( int i = 0; i < input.size(); ++i ) {
        //checking char by char
        if( !check_char(input.at(i), alphabet ) ) {
            //incorrect char found
            return false;

        }
    }

    //all chars are corrects
    return true;
}


//returns the correct alphabet by the given type. (it could be a mix between alphabets)
QString TextSanitizer::craft_alphabet( const int type ) {
    QString alphabet_buffer = "";
    int hold_type = type;
    for ( int i = 0; i < types_num; ++i ) {
        if( hold_type % 2 == 1 ) {
            alphabet_buffer += all_alphabets.at(i);
        }

        hold_type /= 2;
    }
    return alphabet_buffer;
}

//get alphabet type of input. Returns NOT_FOUND if some element can't be paired with an alphabet
int TextSanitizer::get_alphabet_type( const QChar input ) {
    for( int i = 0; i < all_alphabets.size(); ++i ) {
        if( all_alphabets.at(i).indexOf(input) != -1 )
            return qPow( 2, i );
    }
    return NOT_FOUND;
}

//get alphabet type of input. Returns NOT_FOUND if some element can't be paired with an alphabet
int TextSanitizer::get_alphabet_type( const QString& input ) {
    int result = 0;
    for( int j = 0; j < input.size(); ++j ) {
        for( int i = 0; i < all_alphabets.size(); ++i ) {
            if( all_alphabets.at(i).indexOf( input.at(j) ) != -1 )
                result = result | (int)qPow( 2, i );
        }
    }

    if( result == 0 ) return NOT_FOUND;
    return result;
}


//generate random string by passing alphabet string
QString TextSanitizer::random_string( int length, QString alphabet ) {
    std::uniform_int_distribution<int> distribution(0, alphabet.size()-1 );
    QString random_str = "";
    for( int i = 0; i < length; ++i ) {
        random_str += alphabet.at( distribution(*QRandomGenerator::global() ) );
    }
    return random_str;
}


//generate random string by passing alphabet type
QString TextSanitizer::random_string( int length, int alphabet_type ) {
    return random_string( length, craft_alphabet( alphabet_type ) );
}


