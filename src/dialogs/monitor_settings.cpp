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

#include "dialogs/monitor_settings.h"

MonitorSettingsDialog::MonitorSettingsDialog( MonitorSettings settings_manager_in,
                                              QWidget* parent,
                                              QString settings_filename_str ) :
    GeneralDialog( parent, settings_filename_str )
{

    monitor_settings = settings_manager_in;

    //setup ui
    setup_ui();
    apply_settings();
    apply_slots();


    load();

    saved = false;

}

MonitorSettingsDialog::~MonitorSettingsDialog() {

}

void MonitorSettingsDialog::confirm_button_clicked() {
    this->close();
    save();
    saved = true;
}

void MonitorSettingsDialog::cancel_button_clicked() {
    this->close();
}


//apply current settings (like language, teme, and other general settings
void MonitorSettingsDialog::apply_settings() {

    this->setWindowTitle( tr("Monitor settings" ) );

    DataGroup->setTitle( tr( "Data managment" ) );
    SaveGroup->setTitle( tr( "Save" ) );

    AutosaveCheckbox->setText( tr( "Autosave" ) );
    EveryLabel->setText( tr( "Every" ) );
    MinutesLabel->setText( tr("Minutes" ) );

    WhenClosingLabel->setText( tr( "When closing:" ) );
    AskRadio->setText( tr( "Ask to save monitor" ) );
    AutosaveRadio->setText( tr( "Save monitor" ) );

    DontDuplicateCheckbox->setText( tr( "Do not add duplicate data" ) );

    ConfirmButton->setText( tr( "Save" ) );
    CancelButton->setText( tr( "Cancel" ) );

}

//connect all principal widgets signals to the corresponding slots
void MonitorSettingsDialog::apply_slots() {
    connect( ConfirmButton, SIGNAL(clicked()), this, SLOT(confirm_button_clicked()));
    connect( CancelButton, SIGNAL(clicked()), this, SLOT(cancel_button_clicked()) );
    connect( AutosaveCheckbox, SIGNAL(stateChanged(int)), this, SLOT(time_line_checked(int)) );
}


//configure the User Interface: allocating Widgets, layout, etc.
void MonitorSettingsDialog::setup_ui() {

    MainLayout = new QVBoxLayout;

    SaveGroup = new QGroupBox;
    SaveLayout = new QGridLayout;
    AutosaveCheckbox = new QCheckBox;
    AutosaveLayout = new QHBoxLayout;
    EveryLabel = new QLabel;
    TimeLine = new QLineEdit;
    MinutesLabel = new QLabel;
    WhenClosingLabel = new QLabel;
    AskRadio = new QRadioButton;
    AutosaveRadio = new QRadioButton;


    DataGroup = new QGroupBox;
    DataLayout = new QGridLayout;
    DontDuplicateCheckbox = new QCheckBox;

    ButtonsLayout = new QHBoxLayout;
    ConfirmButton = new QPushButton;
    CancelButton = new QPushButton;


    SaveGroup->setLayout( SaveLayout );

    SaveLayout->addWidget( AutosaveCheckbox, 0, 0, 1, 2 );
    SaveLayout->addLayout( AutosaveLayout, 1, 0 );
    SaveLayout->addWidget( WhenClosingLabel, 3, 0 );
    SaveLayout->addWidget( AskRadio, 4, 0 );
    SaveLayout->addWidget( AutosaveRadio, 5, 0 );

    DataGroup->setLayout( DataLayout );
    DataLayout->addWidget( DontDuplicateCheckbox, 0, 0 );

    ButtonsLayout->addStretch();
    ButtonsLayout->addWidget( ConfirmButton );
    ButtonsLayout->addWidget( CancelButton );

    MainLayout->addWidget( SaveGroup );
    MainLayout->addWidget( DataGroup );
    MainLayout->addLayout( ButtonsLayout );

    AutosaveLayout->addSpacing(30);
    AutosaveLayout->addWidget( EveryLabel );
    AutosaveLayout->addWidget( TimeLine );
    AutosaveLayout->addWidget( MinutesLabel );

    this->setLayout( MainLayout );

    SaveLayout->setRowStretch(1, 400 );

    SaveLayout->setColumnStretch( 1, 400 );

}

//load settings from monitor_settings
void MonitorSettingsDialog::load() {

    //reload monitor_settings from db
    monitor_settings.load();

    if( monitor_settings.getAutosave() ) {
        AutosaveCheckbox->setCheckState( Qt::CheckState::Checked );
    } else {
        AutosaveCheckbox->setCheckState( Qt::CheckState::Unchecked );
    }

    TimeLine->setText( QString::number( monitor_settings.getAutosaveEveryMins() ) );

    AutosaveRadio->setChecked( monitor_settings.getMonitorSaveOnClosing() );
    AskRadio->setChecked( !monitor_settings.getMonitorSaveOnClosing() );

    if( monitor_settings.getNoDuplicate() ) {
        DontDuplicateCheckbox->setCheckState( Qt::CheckState::Checked );
    } else {
        DontDuplicateCheckbox->setCheckState( Qt::CheckState::Unchecked );
    }


}


void MonitorSettingsDialog::save() {

    monitor_settings.setAutosave( AutosaveCheckbox->isChecked() );
    monitor_settings.setNoDuplicate( DontDuplicateCheckbox->isChecked() );
    monitor_settings.setAutosaveEveryMins( TimeLine->text().toInt() );
    monitor_settings.setMonitorSaveOnClosing( AutosaveRadio->isChecked() );

    monitor_settings.save();
}


void MonitorSettingsDialog::time_line_checked( int state ) {
    if( !AutosaveCheckbox->isChecked() ) {
        EveryLabel->setEnabled( false );
        MinutesLabel->setEnabled( false );
        TimeLine->setEnabled( false );
    } else {
        EveryLabel->setEnabled( true );
        MinutesLabel->setEnabled( true );
        TimeLine->setEnabled( true );
    }
}


