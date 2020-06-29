#ifndef TEXTSANITIZER_H
#define TEXTSANITIZER_H

#include <QString>
#include <QChar>
#include <QStringList>
#include <QList>
#include <QtMath>
#include <QDebug>
#include <QDateTime>
#include <QRandomGenerator>
#include <QCoreApplication>


/*
 * Author:      Samuele Girgenti
 * Date:        11  /  06  /  2020
 * Description: Class to sanitize ancd check strings of text
 */

#define NOT_FOUND -1

class TextSanitizer
{
    public:
        //types of alphabets
        enum TYPES {
            DIGIT = 1,
            LETTER = 2,
            EXTRA_SYMBOL = 4,
            EXTRA_LETTER = 8,
            VOID = 16
        };

        //alphabets
        static const QString Digit_Alphabet;
        static const QString Letter_Alphabet;
        static const QString Extra_Symbol_Alphabet;
        static const QString Extra_Letter_Alphabet;
        static const QString Void_Alphabet;
        static const QStringList all_alphabets;
        static const int types_num = 5;

        //default constuctor (not used because all members are static)
        TextSanitizer() { }

        // sanitizers
        static bool check_char( const QChar input, const int type );
        static bool check_char( const QChar input, const QString& alphabet );
        static bool check_string( const QString& input, const int type );
        static bool check_string( const QString& input, const QString& alphabet );

        //alphabetic string crafter
        static QString craft_alphabet( const int type );

        //get alphabet type of input. Returns NOT_FOUND if some element can't be paired with an alphabet
        static int get_alphabet_type( const QChar input );
        static int get_alphabet_type( const QString& input );

        static QString random_string( int length, QString alphabet );
        static QString random_string( int length, int alphabet_type );

};


#endif // TEXTSANITIZER_H
