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

#include "dialogs/languagedialog.h"


LanguageDialog::LanguageDialog( QString intro_label_text, QWidget* parent, QString settings_filename_str ) :
    GeneralDialog( parent, settings_filename_str ),
    intro_label_txt( intro_label_text )
{


    //setup ui
    setup_ui();
    apply_settings();
    apply_slots();


}

LanguageDialog::LanguageDialog( QString intro_label_text, ProgrammingLanguage prog_lang, QWidget* parent, QString settings_filename_str ) :
    GeneralDialog( parent, settings_filename_str ),
    intro_label_txt( intro_label_text )
{
    //sistemare prog langs in ui
}

LanguageDialog::~LanguageDialog() {

}

ProgrammingLanguage LanguageDialog::getLanguage() const {
    return new_programming_langauge;
}


//------ ui methods ------

//configure the User Interface: allocating Widgets, layout, etc.
void LanguageDialog::setup_ui() {

    MainLayout = new QVBoxLayout;
    IntroLabel = new QLabel;
    LangBox = new QGroupBox;
    LangLayout = new QGridLayout;
    LangNameLabel = new QLabel;
    LangNameEdit = new QLineEdit;
    LangSlcLabel = new QLabel;
    LangSlcLine = new QLineEdit;
    LangMlcStartLabel = new QLabel;
    LangMlcStartLine = new QLineEdit;
    LangMlcEndLabel = new QLabel;
    LangMlcEndLine = new QLineEdit;
    ExtensionsLabel = new QLabel;
    ExtensionsList = new QListWidget;
    AddExtButton = new QToolButton;
    RemoveExtButton = new QToolButton;
    ButtonsLayout = new QHBoxLayout;
    ConfirmButton = new QPushButton;
    CancelButton = new QPushButton;




    MainLayout->addWidget( IntroLabel );
    MainLayout->addStretch();
    MainLayout->addLayout( LangLayout );
    MainLayout->addLayout( ButtonsLayout );

    LangLayout->addWidget(LangNameLabel, 0, 0, 1, 3 );
    LangLayout->addWidget(LangNameEdit, 0, 3, 1, 3 );
    LangLayout->addWidget(LangSlcLabel, 1, 0, 1, 3 );
    LangLayout->addWidget(LangSlcLine, 1, 3, 1, 3 );
    LangLayout->addWidget(LangMlcStartLabel, 2, 0, 1, 3);
    LangLayout->addWidget(LangMlcStartLine, 2, 3, 1, 3);
    LangLayout->addWidget(LangMlcEndLabel, 3, 0, 1, 3);
    LangLayout->addWidget(LangMlcEndLine, 3, 3, 1, 3);
    LangLayout->addWidget(ExtensionsLabel, 4, 0, 1, 6 );
    LangLayout->addWidget(AddExtButton, 5, 0 );
    LangLayout->addWidget(RemoveExtButton, 6, 0 );
    LangLayout->addWidget(ExtensionsList, 5, 1, 5, 5 );


    ButtonsLayout->addStretch();
    ButtonsLayout->addWidget( ConfirmButton );
    ButtonsLayout->addWidget( CancelButton );

    AddExtButton->setIcon( QIcon(":/img/icons/more.png"));
    RemoveExtButton->setIcon( QIcon(":/img/icons/criss-cross.png"));

    LangSlcLine->setAlignment( Qt::AlignCenter );
    LangMlcEndLine->setAlignment( Qt::AlignCenter );
    LangMlcStartLine->setAlignment( Qt::AlignCenter );
    LangNameEdit->setAlignment( Qt::AlignCenter );

    this->setLayout( MainLayout );


}

//apply current settings (like language, teme, and other general settings
void LanguageDialog::apply_settings() {

    this->setWindowTitle( tr("Programming Languages Editor") );

    IntroLabel->setText( intro_label_txt );
    LangNameLabel->setText( tr("Language name:") );
    LangSlcLabel->setText( tr("Single line comment:" ) );
    LangMlcStartLabel->setText( tr("Multi line comment start:") );
    LangMlcEndLabel->setText( tr("Multi line comment end:") );
    ExtensionsLabel->setText( tr("Extensions:") );
    ConfirmButton->setText( tr("Save") );
    CancelButton->setText( tr("Cancel") );



}

//connect all principal widgets signals to the corresponding slots
void LanguageDialog::apply_slots() {

}








