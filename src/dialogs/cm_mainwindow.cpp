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
    this->resize( 500, 400 );
    this->showMaximized();
    qDebug() << monitor.getCurrentFilespath();
    //setting up gui
    setup_ui();
    apply_settings();
    apply_slots();

    refresh_monitor_table();

    saved = true;

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
    MonitorNowButton = new QPushButton;

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
    ButtonsLayout->addWidget( MonitorNowButton );
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


    //menus
    createActions();
    createMenus();

}

//apply current settings (like language, teme, and other general settings
void CodeMonitorWindow::apply_settings() {
    MonitorNameLabel->setText( tr("Monitor: ") + monitor_name );
    AddFileButton->setText( tr("Add file") );
    AddFolderButton->setText( tr("Add folder") );
    SettingsButton->setText( tr("Settigs") );
    DataGroup->setTitle( tr("Informations" ) );

    MonitorTree->setHeaderLabels( QStringList() << tr("Files") );

    refreshTree();
}

//connect all principal widgets signals to the corresponding slots
void CodeMonitorWindow::apply_slots() {

    connect( MonitorTree, SIGNAL(itemClicked(QTreeWidgetItem*, int )), this, SLOT(monitor_tree_item_clicked( QTreeWidgetItem*, int  )) );
    connect( AddFileButton, SIGNAL(clicked()), this, SLOT(add_file_button_clicked() ) );
    connect( AddFolderButton, SIGNAL(clicked()), this, SLOT(add_folder_button_clicked() ) );
    connect( MonitorNowButton, SIGNAL(clicked()), this, SLOT(monitor_now_button_clicked() ) );
}


void CodeMonitorWindow::refreshTree() {
    MonitorTree->clear();

    QTreeWidgetItem *topLevelItem = NULL;
    foreach (const QString &fileName, monitor.getCurrentFilespath() )
    {
        QStringList splitFileName = fileName.split("/");
        if (MonitorTree->findItems(splitFileName[0], Qt::MatchFixedString).isEmpty())
        {
            topLevelItem = new QTreeWidgetItem;
            topLevelItem->setCheckState( 0, Qt::Unchecked );
            topLevelItem->setFlags( topLevelItem->flags() | Qt::ItemIsTristate | Qt::ItemIsUserCheckable );
            topLevelItem->setText(0, splitFileName[0]);
            MonitorTree->addTopLevelItem(topLevelItem);
        }

        QTreeWidgetItem *parentItem = topLevelItem;

        for (int i = 1; i < splitFileName.size() - 1; ++i)
        {
            bool thisDirectoryExists = false;
            for (int j = 0; j < parentItem->childCount(); ++j)
            {
                if (splitFileName[i] == parentItem->child(j)->text(0))
                {
                    thisDirectoryExists = true;
                    parentItem = parentItem->child(j);
                    break;
                }
            }

            if (!thisDirectoryExists)
            {
                parentItem = new QTreeWidgetItem(parentItem);
                parentItem->setCheckState( 0, Qt::Unchecked );
                parentItem->setFlags( parentItem->flags() | Qt::ItemIsTristate | Qt::ItemIsUserCheckable );
                parentItem->setText(0, splitFileName[i]);
            }
        }

        QTreeWidgetItem *childItem = new QTreeWidgetItem(parentItem);
        childItem->setCheckState( 0, Qt::Unchecked );
        childItem->setFlags( childItem->flags() | Qt::ItemIsUserCheckable );
        childItem->setText(0, splitFileName.last());
        childItem->setToolTip(0, fileName );
    }
}


void CodeMonitorWindow::monitor_tree_item_clicked( QTreeWidgetItem* item, int column ) {
    qDebug() << "REFRESH DEI DATI";
    setFilesToShow();
    refresh_monitor_table();
    qDebug() << filesToShow.size();
}

void CodeMonitorWindow::add_file_button_clicked() {

    //file dialog to choose one or more files
    QFileDialog dialog( this );

    dialog.setNameFilter( tr("All Files (*.*)") );
    dialog.setViewMode( QFileDialog::Detail );
    dialog.setFileMode( QFileDialog::ExistingFiles );

    QStringList fileNames;
    if (dialog.exec())
        fileNames = dialog.selectedFiles();

    if( fileNames.size() > 0 ) {
        FilesDialog* files_dialog = new FilesDialog( fileNames );

        files_dialog->exec();

        if( files_dialog->wasFormConfirmed() ) {

            monitor.addFilespath( files_dialog->getOutputFilenames() );
            refreshTree();
            saved = false;
        }

        delete files_dialog;
    }
}

void CodeMonitorWindow::settings_button_clicked() {

}

void CodeMonitorWindow::add_folder_button_clicked() {

    //file dialog to choose one or more files
    QFileDialog dialog( this );

    dialog.setNameFilter( tr("All Files (*.*)") );
    dialog.setViewMode( QFileDialog::Detail );
    dialog.setFileMode( QFileDialog::DirectoryOnly );

    QStringList dir;
    if (dialog.exec())
        dir = dialog.selectedFiles();

    if( dir.size() > 0 ) {

        QStringList fileNames;
        QDirIterator it(dir.at(0), QStringList() << "*.*", QDir::Files, QDirIterator::Subdirectories);
        while (it.hasNext()) {
            fileNames << it.next();
        }

        FilesDialog* files_dialog = new FilesDialog( fileNames );

        files_dialog->exec();

        if( files_dialog->wasFormConfirmed() ) {
            monitor.addFilespath( files_dialog->getOutputFilenames() );
            refreshTree();
            saved = false;
        }

        delete files_dialog;

    }

}

//set files to be showed in the ui
void CodeMonitorWindow::setFilesToShow() {

    //clearing files list
    filesToShow.clear();

    //searching files in the tree
    for( int i = 0; i < MonitorTree->topLevelItemCount(); ++i ) {
        QTreeWidgetItem* item = MonitorTree->topLevelItem(i);
        checkTreeItemsState( item );
    }

}

//check any single ui
void CodeMonitorWindow::checkTreeItemsState( QTreeWidgetItem* item ) {
    if( item->toolTip(0) == "" ) {
        //current has not a tool tip.
        //tool tip contains filepath if item is a file.
        for( int i = 0; i < item->childCount(); ++i ) {
            checkTreeItemsState( item->child(i) );
        }
    } else {
        //current item is a child, so a file

        //add file only if ite is checked
        if( item->checkState(0) == Qt::Checked )
            //getting filename path from tool tip
            filesToShow.push_back( item->toolTip(0) );

    }
}

void CodeMonitorWindow::monitor_now_button_clicked() {
    monitor.MonitorNow();
    refresh_monitor_table();
    saved = false;
}

void CodeMonitorWindow::refresh_monitor_table() {

    MonitorTable->setRowCount(0);
    MonitorTable->setColumnCount(4);
    MonitorTable->setHorizontalHeaderLabels( QStringList() << tr("Total lines") <<
                                                              tr("Code lines") <<
                                                              tr("Comment lines") <<
                                                              tr("Void lines") );
    MonitorTable->setColumnWidth(0,250);
    MonitorTable->setColumnWidth(1,250);
    MonitorTable->setColumnWidth(2,250);
    MonitorTable->setColumnWidth(3,250);

    MonitorTable->horizontalHeader()->setStretchLastSection( true );

    MonitorTable->verticalHeader()->setVisible(false);
    MonitorTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    MonitorTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    MonitorTable->setSelectionMode(QAbstractItemView::SingleSelection);
    MonitorTable->setShowGrid(false);

    foreach( View current_view, monitor.getAllViews() ) {
        unsigned int code_lines = 0;        //numeber of code lines
        unsigned int comment_lines = 0;     //number of comment lines
        unsigned int total_lines = 0;       //number of total lines
        unsigned int void_lines = 0;

        foreach( QString file, filesToShow ) {
            FileData current_file = current_view.getFileData( file );
            code_lines += current_file.getCodeLines();
            comment_lines += current_file.getCommentLines();
            total_lines += current_file.getTotalLines();
            void_lines += current_file.getVoidLines();
        }
        MonitorTable->insertRow( MonitorTable->rowCount() );
        MonitorTable->setItem( MonitorTable->rowCount() - 1,
                               0,
                               new QTableWidgetItem( QString::number( total_lines ) ) );
        MonitorTable->setItem( MonitorTable->rowCount() - 1,
                               1,
                               new QTableWidgetItem( QString::number( code_lines ) ) );
        MonitorTable->setItem( MonitorTable->rowCount() - 1,
                               2,
                               new QTableWidgetItem( QString::number( comment_lines ) ) );
        MonitorTable->setItem( MonitorTable->rowCount() - 1,
                               3,
                               new QTableWidgetItem( QString::number( void_lines ) ) );
    }

}

void CodeMonitorWindow::closeEvent( QCloseEvent* event )  {
    if( saved == true )
        //db saved
        event->accept();
    else {
        //db not saved yet

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr("Save"), tr("Save %1 monitor before closing?").arg( "\"" + monitor.getMonitorName() + "\""),
                                      QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
        if( reply == QMessageBox::Yes ) {
            //YES button clicked
            save();
            event->accept();
        } else if( reply == QMessageBox::No ) {
            //NO button clicked
            event->accept();
        } else {
            //CANCEL button clicked
            event->ignore();
        }
    }
}

//save data to database
void CodeMonitorWindow::save() {
    saved = true;
    monitor.saveData();
}

//create actions used in menus
void CodeMonitorWindow::createActions() {

    //exit action
    exitAct = new QAction( tr( "&Exit" ), this );
    exitAct->setShortcut( QKeySequence::Quit );
    exitAct->setStatusTip( tr( "Close CodeMonitor" ) );
    connect( exitAct, &QAction::triggered, this, &CodeMonitorWindow::exit_slot );

    //save action
    saveAct = new QAction( tr( "&Save"), this );
    saveAct->setShortcut( QKeySequence::Save );
    saveAct->setStatusTip( tr( "Save monitor" ) );
    connect( saveAct, &QAction::triggered, this, &CodeMonitorWindow::save_slot );

    //add file action
    addFileAct = new QAction( tr( "&Add file"), this );
    addFileAct->setStatusTip( tr( "Add one or more files to monitor" ) );
    connect( addFileAct, &QAction::triggered, this, &CodeMonitorWindow::add_file_slot );

    //add folder action
    addFolderAct = new QAction( tr( "&Add folder"), this );
    addFolderAct->setStatusTip( tr( "Add all files contained in a folder" ) );
    connect( addFolderAct, &QAction::triggered, this, &CodeMonitorWindow::add_folder_slot );

    //remove file action
    removeFileAct = new QAction( tr( "&Remove file"), this );
    removeFileAct->setShortcut( QKeySequence::Delete );
    removeFileAct->setStatusTip( tr( "Remove selected file" ) );
    connect( removeFileAct, &QAction::triggered, this, &CodeMonitorWindow::remove_file_slot );

    //general settings action
    generalSettingsAct = new QAction( tr( "&General settings"), this );
    generalSettingsAct->setStatusTip( tr( "Open general settings dialog" ) );
    connect( generalSettingsAct, &QAction::triggered, this, &CodeMonitorWindow::general_settings_slot );

    //add folder action
    monitorSettingsAct = new QAction( tr( "&Monitor settings"), this );
    monitorSettingsAct->setStatusTip( tr( "Open monitor settings dialog" ) );
    connect( monitorSettingsAct, &QAction::triggered, this, &CodeMonitorWindow::monitor_settings_slot );

    //add folder action
    monitorSettingsAct = new QAction( tr( "&Monitor settings"), this );
    monitorSettingsAct->setStatusTip( tr( "Open monitor settings dialog" ) );
    connect( monitorSettingsAct, &QAction::triggered, this, &CodeMonitorWindow::monitor_settings_slot );

    //add folder action
    aboutAct = new QAction( tr( "&About"), this );
    aboutAct->setStatusTip( tr( "About Code Monitor" ) );
    connect( aboutAct, &QAction::triggered, this, &CodeMonitorWindow::about_slot );


}

//create menus
void CodeMonitorWindow::createMenus() {
    FileMenu = menuBar()->addMenu( tr( "&File" ) );
    FileMenu->addAction( saveAct );
    FileMenu->addAction( exitAct );

    MonitorMenu = menuBar()->addMenu( tr( "&Monitor" ) );
    MonitorMenu->addAction( addFileAct );
    MonitorMenu->addAction( addFolderAct );
    MonitorMenu->addAction( removeFileAct );

    SettingsMenu = menuBar()->addMenu( tr( "&Settings" ) );
    SettingsMenu->addAction( generalSettingsAct );
    SettingsMenu->addAction( monitorSettingsAct );


}

//---- menu slots -----

void CodeMonitorWindow::exit_slot() {
    this->close();
}

void CodeMonitorWindow::save_slot() {
    this->save();
}
void CodeMonitorWindow::add_file_slot() {

}

void CodeMonitorWindow::add_folder_slot() {

}

void CodeMonitorWindow::remove_file_slot() {

}

void CodeMonitorWindow::general_settings_slot() {

}

void CodeMonitorWindow::monitor_settings_slot() {

}

void CodeMonitorWindow::about_slot() {

}


