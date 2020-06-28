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

#include "dialogs/cm_welcomedialog.h"

CM_WelcomeDialog::CM_WelcomeDialog( QWidget* parent, QString settings_filename_str ) :
    GeneralWindow( parent, settings_filename_str )
{
    //setting up dialog, and settings
    this->setup_ui();
    this->apply_settings();
    this->apply_slots();

}

CM_WelcomeDialog::~CM_WelcomeDialog() {

}

//apply current settings (like language, teme, and other general settings
void CM_WelcomeDialog::apply_settings() {
    ExitButton->setText( tr( "Exit" ) );
    SettingsButton->setText( tr( "Settings" ) );
    NewMonitorButton->setText( tr( "New Monitor" ) );
    DeleteMonitorButton->setText( tr( "Delete Monitor" ) );
    EditMonitorButton->setText( tr( "Edit Monitor" ) );
    OpenMonitorButton->setText( tr( "Open Monitor" ) );

}

//connect all principal widgets signals to the corresponding slots
void CM_WelcomeDialog::apply_slots() {

}

//configure the User Interface: allocating Widgets, layout, etc.
void CM_WelcomeDialog::setup_ui() {
    MainLayout = new QHBoxLayout;
    ButtonsLayout = new QGridLayout;
    MonitorWidget = new QListWidget;
    SettingsButton = new QPushButton;
    ExitButton = new QPushButton;
    NewMonitorButton = new QPushButton;
    OpenMonitorButton = new QPushButton;
    EditMonitorButton = new QPushButton;
    DeleteMonitorButton = new QPushButton;
    MainWidget = new QWidget;

    ButtonsLayout->addWidget( NewMonitorButton, 0, 0, 1, 2 );
    ButtonsLayout->addWidget( OpenMonitorButton, 1, 0, 1, 2 );
    ButtonsLayout->addWidget( EditMonitorButton, 2, 0, 1, 2 );
    ButtonsLayout->addWidget( DeleteMonitorButton, 3, 0, 1, 2 );
    ButtonsLayout->addWidget( SettingsButton, 4, 0 );
    ButtonsLayout->addWidget( ExitButton, 4, 1 );

    MainLayout->addWidget(MonitorWidget);
    MainLayout->addLayout(ButtonsLayout);
    MainLayout->setMargin(3);

    MainWidget->setLayout( MainLayout );

    this->setCentralWidget( MainWidget );

    //----- Other settings -----
    NewMonitorButton->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum );
    OpenMonitorButton->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum );
    EditMonitorButton->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum );
    DeleteMonitorButton->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum );
    SettingsButton->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum );
    ExitButton->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum );
}

// ---- slots ----

//settings button clicked
void CM_WelcomeDialog::SettingsButtonClicked() {

}

//exit button clicked
void CM_WelcomeDialog::ExitButtonClicked() {
    this->close();
}

//New monitor button clicked: create new monitor
void CM_WelcomeDialog::NewMonitorButtonClicked() {

}

//Open Monitor Button clicked: Open selected monitor
void CM_WelcomeDialog::OpenMonitorButtonClicked() {

}


void CM_WelcomeDialog::EditMonitorButtonClicked() {

}

void CM_WelcomeDialog::DeleteMonitorButtonCLicked() {

}
