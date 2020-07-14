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

#include "dialogs/aboutdialog.h"



AboutDialog::AboutDialog( QWidget* parent,
                          QString settings_filename_str  ) :
    GeneralDialog( parent, settings_filename_str )
{

    //setup ui
    setup_ui();
    apply_settings();
    apply_slots();


}


AboutDialog::~AboutDialog() {

}



//configure the User Interface: allocating Widgets, layout, etc.
void AboutDialog::setup_ui() {

    //creating widgets
    MainLayout = new QVBoxLayout;

    InfoLayout = new QGridLayout;
    VersionLeftLabel = new QLabel;
    VersionRightLabel = new QLabel;
    DateLeftLabel = new QLabel;
    DateRightLabel = new QLabel;
    LicenseLeftLabel = new QLabel;
    LicenseRightLabel = new QLabel;
    AuthorLeftLabel = new QLabel;
    AuthorRightLabel = new QLabel;
    EmailLeftLabel = new QLabel;
    EmailRightLabel = new QLabel;
    GithubLeftLabel = new QLabel;
    GithubRightLabel = new QLabel;

    ButtonsLayout = new QHBoxLayout;
    OfficialPageButton = new QPushButton;
    LicenseButton = new QPushButton;
    OkButton = new QPushButton;


    ButtonsLayout->addWidget( OfficialPageButton );
    ButtonsLayout->addWidget( LicenseButton );
    ButtonsLayout->addStretch();
    ButtonsLayout->addWidget( OkButton );

    InfoLayout->addWidget( VersionLeftLabel, 0, 0 );
    InfoLayout->addWidget( VersionRightLabel, 0, 1 );
    InfoLayout->addWidget( DateLeftLabel, 1, 0 );
    InfoLayout->addWidget( DateRightLabel, 1, 1 );
    InfoLayout->addWidget( LicenseLeftLabel, 2, 0 );
    InfoLayout->addWidget( LicenseRightLabel, 2, 1 );
    InfoLayout->addWidget( AuthorLeftLabel, 3, 0 );
    InfoLayout->addWidget( AuthorRightLabel, 3, 1 );
    InfoLayout->addWidget( EmailLeftLabel, 4, 0 );
    InfoLayout->addWidget( EmailRightLabel, 4, 1 );
    InfoLayout->addWidget( GithubLeftLabel, 5, 0 );
    InfoLayout->addWidget( GithubRightLabel, 5, 1 );


    MainLayout->addLayout( InfoLayout );
    MainLayout->addLayout( ButtonsLayout );

    this->setLayout( MainLayout );

}


//apply current settings (like language, teme, and other general settings
void AboutDialog::apply_settings() {

    OkButton->setText( tr( "Ok" ) );
    OfficialPageButton->setText( tr( "Official Page" ) );
    LicenseButton->setText( tr( "License" ) );

    VersionLeftLabel->setText( tr( "Version:" ) );
    DateLeftLabel->setText( tr( "Release date:" ) );
    LicenseLeftLabel->setText( tr( "License:" ) );
    AuthorLeftLabel->setText( tr( "Author:" ) );
    EmailLeftLabel->setText( tr( "Email:" ) );
    GithubLeftLabel->setText( tr( "Github:" ) );

    VersionRightLabel->setText( "VERSION" );
    DateRightLabel->setText( "DATE" );

    LicenseRightLabel->setText( "GNU General Public License v3.0");
    AuthorRightLabel->setText( "Samuele Girgenti" );

    EmailRightLabel->setText("<a href=\"samuele.girgenti458@gmail.com\">samuele.girgenti458@gmail.com</a>");
    EmailRightLabel->setTextFormat(Qt::RichText);
    EmailRightLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    EmailRightLabel->setOpenExternalLinks(true);

    GithubRightLabel->setText("<a href=\"http://github.com/Samuele458/\">github.com/Samuele458</a>");
    GithubRightLabel->setTextFormat(Qt::RichText);
    GithubRightLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    GithubRightLabel->setOpenExternalLinks(true);

}



//  --  slots  --

//connect all principal widgets signals to the corresponding slots
void AboutDialog::apply_slots() {

    connect( OkButton, SIGNAL(clicked()), this, SLOT( ok_button_clicked()) );
    connect( OfficialPageButton, SIGNAL(clicked()), this, SLOT( official_page_button_clicked()) );
    connect( LicenseButton, SIGNAL(clicked()), this, SLOT( license_button_clicked()) );


}


void AboutDialog::ok_button_clicked() {
    this->close();
}


void AboutDialog::official_page_button_clicked() {
    QDesktopServices::openUrl ( QUrl( "https://github.com/Samuele458/CodeMonitor" ) );
}

void AboutDialog::license_button_clicked() {
    LicenseDialog* license_dialog = new LicenseDialog( this );

    license_dialog->exec();

    delete license_dialog;
}


