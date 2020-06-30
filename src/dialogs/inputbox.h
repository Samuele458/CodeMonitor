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

#ifndef INPUTBOX_H
#define INPUTBOX_H

#include <QString>
#include <QLabel>
#include <QLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>

#include "dialogs/dialogs.h"
#include "common/textsanitizer.h"

class InputBox : public GeneralDialog {
    Q_OBJECT

    public:
        InputBox( QString title_str,
                  QString message_str,
                  QWidget* parent = nullptr,
                  QString settings_filename_str = "config.ini"  );

        ~InputBox();


        //getter - setter methods
        void setTitle( QString title_str );
        QString getTitle() const;
        void setMessage( QString message_str );
        QString getMessage() const;

        QString getInputStr() const;

        void setInputType( int type );
        int getInputType() const;
        void setMaxLen( int len );
        int getMaxLen() const;

        bool wasFormConfirmed() const;

    protected slots:
        void confirm_button_clicked();
        void cancel_button_clicked();
        void line_text_changed( const QString& text_str );

    protected:

        //widgets
        QGridLayout* MainLayout;
        QLabel* EnterMessageLabel;
        QLineEdit* InputLine;
        QPushButton* ConfirmButton;
        QPushButton* CancelButton;

        //data
        QString title;
        QString message;
        QString input;

        int input_type;
        int max_len;

        bool form_confirmed;

        //------ ui methods ------

        //apply current settings (like language, teme, and other general settings
        void apply_settings() override;

        //connect all principal widgets signals to the corresponding slots
        void apply_slots() override;

        //configure the User Interface: allocating Widgets, layout, etc.
        void setup_ui() override;



};

#endif
