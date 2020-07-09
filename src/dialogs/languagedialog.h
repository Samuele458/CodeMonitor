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


#ifndef LANGUAGEDIALOG_H
#define LANGUAGEDIALOG_H

#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QToolButton>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QListWidget>
#include <QIcon>
#include <QMessageBox>

#include "dialogs/dialogs.h"
#include "dialogs/inputbox.h"
#include "monitor.h"


class LanguageDialog : public GeneralDialog {
    Q_OBJECT

    public:
        LanguageDialog( QString intro_label_text, QWidget* parent = nullptr, QString settings_filename_str = "config.ini" );
        LanguageDialog( QString intro_label_text, ProgrammingLanguage prog_lang, QWidget* parent = nullptr, QString settings_filename_str = "config.ini" );
        ~LanguageDialog();

        ProgrammingLanguage getLanguage() const;

        bool wasFormConfirmed() const;

    protected slots:
        void confirm_button_clicked();
        void cancel_button_clicked();
        void add_lang_button_clicked();
        void remove_lang_button_clicked();

    protected:

        //------ ui methods ------

        //apply current settings (like language, teme, and other general settings
        void apply_settings() override;

        //connect all principal widgets signals to the corresponding slots
        void apply_slots() override;

        //configure the User Interface: allocating Widgets, layout, etc.
        void setup_ui() override;


        //---widgets----
        QVBoxLayout* MainLayout;
        QLabel* IntroLabel;
        QGroupBox* LangBox;
        QGridLayout* LangLayout;

        QLabel* LangNameLabel;
        QLineEdit* LangNameEdit;

        QLabel* LangSlcLabel;
        QLineEdit* LangSlcLine;

        QLabel* LangMlcStartLabel;
        QLineEdit* LangMlcStartLine;

        QLabel* LangMlcEndLabel;
        QLineEdit* LangMlcEndLine;

        QLabel* ExtensionsLabel;
        QListWidget* ExtensionsList;
        QToolButton* AddExtButton;
        QToolButton* RemoveExtButton;

        QHBoxLayout* ButtonsLayout;
        QPushButton* ConfirmButton;
        QPushButton* CancelButton;

        //----------


        QString intro_label_txt;

        ProgrammingLanguage new_programming_langauge;

        bool form_confirmed;


};

#endif
