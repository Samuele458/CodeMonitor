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

#include "dialogs/cm_mainwindow.h"

CodeMonitorWindow::CodeMonitorWindow( QString monitor_name_str,
                   QWidget* parent,
                   QString settings_filename_str ) :
    GeneralWindow( parent, settings_filename_str ),
    monitor_name( monitor_name_str ),
    monitor( monitor_name_str )
{
    qDebug() << monitor.getCurrentFilespath();
    //setting up gui
    setup_ui();
    apply_settings();
    apply_slots();

}

CodeMonitorWindow::~CodeMonitorWindow() {

}

//configure the User Interface: allocating Widgets, layout, etc.
void CodeMonitorWindow::setup_ui() {

    MainWidget = new QWidget;
    MainLayout = new QHBoxLayout;
    CentralSplitter = new QSplitter;
    LeftWidget = new QWidget;
    RightWidget = new QWidget;
    LeftLayout = new QVBoxLayout;
    MonitorNameLabel = new QLabel;
    MonitorTree = new QTreeWidget;
    RightLayout = new QVBoxLayout;
    RightSplitterLayout = new QVBoxLayout;
    RightSplitter = new QSplitter;
    MonitorTable = new QTableWidget;
    DataGroup = new QGroupBox;
    ButtonsLayout = new QHBoxLayout;
    AddFileButton = new QPushButton;
    AddFolderButton = new QPushButton;
    SettingsButton = new QPushButton;

    //---- left side ----
    LeftLayout->addWidget( MonitorNameLabel );
    LeftLayout->addWidget( MonitorTree );

    //---- right side ----
    RightSplitter->addWidget( MonitorTable );
    RightSplitter->addWidget( DataGroup );
    RightSplitter->setOrientation( Qt::Vertical );

    RightSplitterLayout->addWidget(RightSplitter);
    RightLayout->addLayout( RightSplitterLayout );
    ButtonsLayout->addWidget( AddFileButton );
    ButtonsLayout->addWidget( AddFolderButton );
    ButtonsLayout->addWidget( SettingsButton );
    RightLayout->addLayout( ButtonsLayout );


    LeftWidget->setLayout( LeftLayout );
    RightWidget->setLayout( RightLayout );
    CentralSplitter->addWidget( LeftWidget );
    CentralSplitter->addWidget( RightWidget );
    MainLayout->addWidget( CentralSplitter );
    MainWidget->setLayout( MainLayout );
    this->setCentralWidget( MainWidget );

    MainLayout->setMargin(0);
    RightLayout->setMargin(3);
    LeftLayout->setMargin(3);

}

//apply current settings (like language, teme, and other general settings
void CodeMonitorWindow::apply_settings() {
    MonitorNameLabel->setText( tr("Monitor: ") + monitor_name );
    AddFileButton->setText( tr("Add file") );
    AddFolderButton->setText( tr("Add folder") );
    SettingsButton->setText( tr("Settigs") );
    DataGroup->setTitle( tr("Informations" ) );
}

//connect all principal widgets signals to the corresponding slots
void CodeMonitorWindow::apply_slots() {

}


