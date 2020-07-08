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

#include "dialogs/general_settings.h"

GeneralSettingsDialog::GeneralSettingsDialog( QWidget* parent , QString settings_filename_str ) :
    GeneralDialog( parent, settings_filename_str )
{

    //setup ui
    setup_ui();
    apply_settings();
    apply_slots();

    load();

    saved = false;

}

GeneralSettingsDialog::~GeneralSettingsDialog() {

}

//configure the User Interface: allocating Widgets, layout, etc.
void GeneralSettingsDialog::setup_ui() {
    MainLayout = new QVBoxLayout;
    StyleBox = new QGroupBox;
    StyleMainLayout = new QGridLayout;
    fontLabel = new QLabel;
    fontCombo = new QFontComboBox;
    sizeLabel = new QLabel;
    sizeSlider = new QSlider( Qt::Orientation::Horizontal );
    sizeLine = new QLineEdit;

    ProgLangBox = new QGroupBox;
    LangMainLayout = new QVBoxLayout;
    LangLabel = new QLabel;
    LangTable = new QTableWidget;
    LangButtonsLayout = new QHBoxLayout;
    AddLangButton = new QToolButton;
    RemoveLangButton = new QToolButton;
    EditLangButton = new QToolButton;

    GeneralBox = new QGroupBox;
    GeneralMainLayout = new QGridLayout;
    dateFormatLabel = new QLabel;
    dateFormatCombo = new QComboBox;

    ButtonsLayout = new QHBoxLayout;
    ConfirmButton = new QPushButton;
    CancelButton = new QPushButton;




    MainLayout->addWidget( StyleBox );
    StyleBox->setLayout( StyleMainLayout );
    StyleMainLayout->addWidget( fontLabel, 0, 0, 1, 1 );
    StyleMainLayout->addWidget( fontCombo, 0, 1, 1, 2 );
    StyleMainLayout->addWidget( sizeLabel, 1, 0 );
    StyleMainLayout->addWidget( sizeSlider, 1, 1 );
    StyleMainLayout->addWidget( sizeLine, 1, 2 );




    MainLayout->addWidget( ProgLangBox );
    ProgLangBox->setLayout( LangMainLayout );
    LangButtonsLayout->addWidget( AddLangButton );
    LangButtonsLayout->addWidget( RemoveLangButton );
    LangButtonsLayout->addWidget( EditLangButton );
    LangButtonsLayout->addStretch();
    LangMainLayout->addWidget( LangLabel );
    LangMainLayout->addWidget( LangTable );
    LangMainLayout->addLayout( LangButtonsLayout );

    MainLayout->addWidget( GeneralBox );
    GeneralBox->setLayout( GeneralMainLayout );
    GeneralMainLayout->addWidget( dateFormatLabel, 0, 0 );
    GeneralMainLayout->addWidget( dateFormatCombo, 0, 1 );


    MainLayout->addLayout( ButtonsLayout );
    ButtonsLayout->addStretch();
    ButtonsLayout->addWidget( ConfirmButton );
    ButtonsLayout->addWidget( CancelButton );

    this->setLayout( MainLayout );

    //other settings
    sizeLine->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );
    sizeLine->setMaximumWidth( 80 );
    sizeLine->setAlignment( Qt::AlignCenter );

    AddLangButton->setIcon( QIcon( ":/img/icons/more.png") );
    RemoveLangButton->setIcon( QIcon( ":/img/icons/criss-cross.png") );
    EditLangButton->setIcon( QIcon( ":/img/icons/pencil.png") );

    sizeLine->setReadOnly( true );
    dateFormatLabel->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );
    LangLabel->setAlignment( Qt::AlignCenter );


}

//apply current settings (like language, teme, and other general settings
void GeneralSettingsDialog::apply_settings() {

    ConfirmButton->setText( tr( "Save" ) );
    CancelButton->setText( tr( "Cancel" ) );

    StyleBox->setTitle( tr( "Style" ) );
    fontLabel->setText( tr( "Font:" ) );
    sizeLabel->setText( tr( "Font size:" ) );


    GeneralBox->setTitle( tr( "General" ) );
    dateFormatLabel->setText( tr( "date format:" ) );

    ProgLangBox->setTitle( tr( "Programming Languages" ) );
    LangLabel->setText( tr("Programming languages loaded:" ) );


}

//connect all principal widgets signals to the corresponding slots
void GeneralSettingsDialog::apply_slots() {

    connect( ConfirmButton, SIGNAL(clicked()), this, SLOT(confirm_button_clicked()));
    connect( CancelButton, SIGNAL(clicked()), this, SLOT(cancel_button_clicked()));

}

//load settings
void GeneralSettingsDialog::load() {

}

//save settings
void GeneralSettingsDialog::save() {

}

//setup programming language table;
void GeneralSettingsDialog::setup_lang_table() {

}

// ---- slots funxtions ----

void GeneralSettingsDialog::confirm_button_clicked() {
    this->close();
    save();
    saved = true;
}

void GeneralSettingsDialog::cancel_button_clicked() {
    this->close();
}

