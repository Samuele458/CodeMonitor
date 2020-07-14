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



#include "dialogs/licensedialog.h"


LicenseDialog::LicenseDialog( QWidget* parent,
                              QString settings_filename_str ) :
    GeneralDialog( parent, settings_filename_str )
{

    //setup ui
    setup_ui();
    apply_settings();
    apply_slots();

}

LicenseDialog::~LicenseDialog() {

}


//------ ui methods ------

//apply current settings (like language, teme, and other general settings
void LicenseDialog::apply_settings() {
    this->setWindowTitle( tr( "License" ) );

    QFile license_file( ":/other/license.dat" );

    license_file.open( QIODevice::ReadOnly );
    LicenseEdit->setText( license_file.readAll() );
    OkButton->setText( tr( "Ok" ) );
    TitleLabel->setText( "GNU General Public License v3.0" );

    QFont title_font = TitleLabel->font();
    title_font.setPointSize( 25 );
    TitleLabel->setFont( title_font );

}

//connect all principal widgets signals to the corresponding slots
void LicenseDialog::apply_slots() {
    connect( OkButton, SIGNAL(clicked()), this, SLOT(ok_button_clicked()));
}

//configure the User Interface: allocating Widgets, layout, etc.
void LicenseDialog::setup_ui() {

    MainLayout = new QVBoxLayout;
    TitleLabel = new QLabel;
    LicenseEdit = new QTextEdit;
    ButtonsLayout = new QHBoxLayout;
    OkButton = new QPushButton;

    ButtonsLayout->addStretch();
    ButtonsLayout->addWidget( OkButton );

    MainLayout->addWidget( TitleLabel );
    MainLayout->addWidget( LicenseEdit );
    MainLayout->addLayout( ButtonsLayout );

    this->setLayout( MainLayout );

    TitleLabel->setAlignment( Qt::AlignCenter );

}

void LicenseDialog::ok_button_clicked() {
    this->close();
}



