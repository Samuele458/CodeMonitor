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
    if( !QDir( QDir::currentPath() + "/data" ).exists() ) {
        QDir local( QDir::currentPath() );
        local.mkdir("data" );
    }

    if( !QDir( QDir::currentPath() + "/data/monitors" ).exists() ) {
        QDir local( QDir::currentPath() + "/data" );
        local.mkdir("monitors" );
    }

    //setting up database
    db = new QSqlDatabase;
    db->addDatabase( "QSQLITE", "main" );
    monitors_db = new QSqlDatabase;
    *monitors_db = QSqlDatabase::database( "main" );
    monitors_db->setDatabaseName( QDir::currentPath() + "/data/monitors.db" );


    if( !QFile::exists( QDir::currentPath() + "/data/monitors.db" ) ) {
        //creating new database
        qDebug() << monitors_db->open();
        QSqlQuery query( *monitors_db );
        qDebug() << query.exec( "CREATE TABLE monitors ("
                    "ID_monitor INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE,"
                    "monitor_name TEXT NOT NULL UNIQUE,"
                    "monitor_files_table TEXT NOT NULL UNIQUE,"
                    "monitor_data_table TEXT NOT NULL UNIQUE "
                    ")" );

    } else {
       monitors_db->open();
    }

    //setting up dialog, and settings
    this->setup_ui();
    this->apply_settings();
    this->apply_slots();




}

CM_WelcomeDialog::~CM_WelcomeDialog() {

}

//get all monitors entries
QStringList CM_WelcomeDialog::monitorsList() const {
    QStringList list;

    QSqlQuery query( *monitors_db );
    qDebug() << query.exec( "SELECT monitor_name FROM monitors" );
    while( query.next() ) {
        list.push_back( query.record().value(0).toString() );
    }

    return list;
}

//apply current settings (like language, teme, and other general settings
void CM_WelcomeDialog::apply_settings() {
    ExitButton->setText( tr( "Exit" ) );
    SettingsButton->setText( tr( "Settings" ) );
    NewMonitorButton->setText( tr( "New Monitor" ) );
    DeleteMonitorButton->setText( tr( "Delete Monitor" ) );
    EditMonitorButton->setText( tr( "Edit Monitor" ) );
    OpenMonitorButton->setText( tr( "Open Monitor" ) );
    MonitorLabel->setText( tr("Monitors") );

    MonitorLabel->setAlignment( Qt::AlignCenter );

    //refresh monitor list
    refresh_monitor_widget();


}

//connect all principal widgets signals to the corresponding slots
void CM_WelcomeDialog::apply_slots() {
    //connecting signals to slots
    connect( ExitButton, SIGNAL(clicked()), this, SLOT(ExitButtonClicked()) );
    connect( SettingsButton, SIGNAL(clicked()), this, SLOT(SettingsButtonClicked()) );
    connect( NewMonitorButton, SIGNAL(clicked()), this, SLOT(NewMonitorButtonClicked()) );
    connect( EditMonitorButton, SIGNAL(clicked()), this, SLOT(EditMonitorButtonClicked()) );
    connect( OpenMonitorButton, SIGNAL(clicked()), this, SLOT(OpenMonitorButtonClicked()) );
    connect( DeleteMonitorButton, SIGNAL(clicked()), this, SLOT(DeleteMonitorButtonCLicked()) );
}

//configure the User Interface: allocating Widgets, layout, etc.
void CM_WelcomeDialog::setup_ui() {
    MainLayout = new QHBoxLayout;
    ButtonsLayout = new QGridLayout;
    MonitorWidget = new QListWidget;
    MonitorLabel = new QLabel;
    MonitorLayout = new QVBoxLayout;
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

    MonitorLayout->addWidget( MonitorLabel );
    MonitorLayout->addWidget( MonitorWidget );

    MainLayout->addLayout(MonitorLayout);
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


void CM_WelcomeDialog::refresh_monitor_widget() {
    //Setting up monitor list
    QSqlQuery query( *monitors_db );
    query.exec( "SELECT monitor_name FROM monitors" );
    MonitorWidget->clear();
    while( query.next() ) {
        MonitorWidget->addItem( query.record().value(0).toString() );
    }
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
    //creating new monitor
    InputBox* box = new InputBox( tr("New monitor"),
                                  tr("Enter monitor name:") );
    box->exec();


    //checking if form is accepted
    if( box->wasFormConfirmed() ) {
        //form confirmed
        if( monitorsList().indexOf( box->getInputStr() ) == -1 ) {


            QString monitor_name = box->getInputStr();

            if( QFile::exists( QDir::currentPath() + "/data/monitors/" + monitor_name + ".db" ) ) {
                QFile::remove( QDir::currentPath() + "/data/monitors/" + monitor_name + ".db" );
            }


            QSqlDatabase local_db = QSqlDatabase::database( "main" );
            local_db.setDatabaseName( QDir::currentPath() + "/data/monitors/" + monitor_name + ".db" );

            if( local_db.open() ) {
                //database created

                QSqlQuery query( local_db );
                query.exec( "CREATE TABLE monitor_"+monitor_name+"_data ("
                            "ID_view INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE,"
                            "date TEXT NOT NULL UNIQUE"
                            ")");

                query.exec( "CREATE TABLE monitor_"+monitor_name+"_files ("
                            "ID_file INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE,"
                            "file_path TEXT NOT NULL UNIQUE"
                            ")" );


                local_db.close();
                local_db.setDatabaseName( QDir::currentPath() + "/data/monitors.db" );
                local_db.open();

                query.exec( "INSERT INTO monitors (monitor_name, monitor_files_table, monitor_data_table) "
                            "VALUES (\""+monitor_name+"\",\"monitor_"+monitor_name+"_files\",\"monitor_"+monitor_name+"_data\")" );


            } else {
               QMessageBox::critical( this, tr("Error"), tr("Error: couldn't create new monitor") );
            }
        } else {
            QMessageBox::warning( this,
                                  tr("Error"),
                                  tr("Monitor already exists!"));
        }
    }

    //refreshing monitors list
    refresh_monitor_widget();

    delete box;

}

//Open Monitor Button clicked: Open selected monitor
void CM_WelcomeDialog::OpenMonitorButtonClicked() {
    if( MonitorWidget->selectedItems().size() != 0 ) {

    } else {
        QMessageBox::warning( this, tr("Error"), tr("No monitor selected!") );
    }
}

//Edit monitor button clicked
void CM_WelcomeDialog::EditMonitorButtonClicked() {
    if( MonitorWidget->selectedItems().size() != 0 ) {

    } else {
        QMessageBox::warning( this, tr("Error"), tr("No monitor selected!") );
    }
}

//delete monitor button clicked
void CM_WelcomeDialog::DeleteMonitorButtonCLicked() {
    if( MonitorWidget->selectedItems().size() != 0 ) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr("Delete monitor"), tr("Are you sure to remove the selected monitor?"),
                                      QMessageBox::Yes|QMessageBox::No);
        if ( reply == QMessageBox::Yes ) {
            //Box accepted
            QString monitor_name = MonitorWidget->selectedItems().at(0)->text();
            QFile::remove( QDir::currentPath() + "/data/monitors/" + monitor_name + ".db" );
            QSqlQuery query( *monitors_db );
            query.exec( "DELETE FROM monitors "
                        "WHERE monitor_name = \"" + monitor_name + "\" " );
        }
    } else {
        QMessageBox::warning( this, tr("Error"), tr("No monitor selected!") );
    }
    refresh_monitor_widget();
}
