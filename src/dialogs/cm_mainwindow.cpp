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

    //nullptr ---> there is not a curent view
    view = nullptr;

    //setting up gui
    setup_ui();
    apply_settings();
    apply_slots();


    //if tree is not empty, set all items checked
    if( MonitorTree->topLevelItem(0) != nullptr ) {
        MonitorTree->topLevelItem(0)->setCheckState( 0, Qt::Checked );
    }

    refresh_monitor_table();

    saved = true;

    autosave_timer = new QTimer(this);
    if( monitor.getSettings().getAutosave() ) {
        connect(autosave_timer,SIGNAL(timeout()), this, SLOT(autosave_slot()));
        autosave_timer->start(monitor.getSettings().getAutosaveEveryMins()*60*1000);
    }

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
    MainToolbar = new QToolBar;
    MonitorNameLabel = new QLabel;
    MonitorTree = new QTreeWidget;
    RightLayout = new QVBoxLayout;
    RightSplitterLayout = new QVBoxLayout;
    RightSplitter = new QSplitter;

    MonitorWidget = new QWidget;
    MonitorLayout = new QVBoxLayout;
    MonitorToolbar = new QToolBar;
    MonitorTable = new QTableWidget;

    ViewWidget = new QWidget;
    ViewLayout = new QVBoxLayout;
    InformationLabel = new QLabel;
    ViewTable = new QTableWidget;

    ButtonsLayout = new QHBoxLayout;
    AddFileButton = new QPushButton;
    AddFolderButton = new QPushButton(this);
    SettingsButton = new QPushButton;
    MonitorNowButton = new QPushButton;
    MonitorProgressBar = new QProgressBar;

    //---- left side ----
    LeftLayout->addWidget( MainToolbar );
    LeftLayout->addWidget( MonitorNameLabel );
    LeftLayout->addWidget( MonitorTree );

    //---- right side ----

    ViewLayout->addWidget( InformationLabel );
    ViewLayout->addWidget( ViewTable );
    ViewWidget->setLayout( ViewLayout );

    MonitorLayout->addWidget( MonitorToolbar );
    MonitorLayout->addWidget( MonitorTable);
    MonitorWidget->setLayout(MonitorLayout);

    RightSplitter->addWidget( MonitorWidget );
    RightSplitter->addWidget( ViewWidget );
    RightSplitter->setOrientation( Qt::Vertical );

    RightSplitterLayout->addWidget(RightSplitter);
    RightLayout->addLayout( RightSplitterLayout );
    ButtonsLayout->addWidget( AddFileButton );
    ButtonsLayout->addWidget( AddFolderButton );
    ButtonsLayout->addWidget( MonitorNowButton );
    MonitorNowButton->setObjectName( "green-button" );
    ButtonsLayout->addWidget( MonitorProgressBar );

    ButtonsLayout->addStretch();

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
    ViewLayout->setMargin(0);

    MonitorTree->header()->setStretchLastSection( false );
    MonitorTree->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

    AddFileButton->setIcon( QIcon( ":/img/icons/more.png" ) );
    AddFolderButton->setIcon( QIcon( ":/img/icons/more.png" ) );
    SettingsButton->setIcon( QIcon( ":/img/icons/settings.png" ) );


    MonitorTable->setContextMenuPolicy( Qt::ContextMenuPolicy::CustomContextMenu );
    MonitorTree->setContextMenuPolicy( Qt::ContextMenuPolicy::CustomContextMenu );


    //menus
    createActions();
    createMenus();

    MainToolbar->setIconSize(QSize(30,30));
    MainToolbar->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonIconOnly);

    MainToolbar->addAction(addFileAct);
    MainToolbar->addAction(addFolderAct);
    MainToolbar->addAction(removeFileAct);
    MainToolbar->addAction(generalSettingsAct);

    MonitorToolbar->setIconSize(QSize(30,30));
    MonitorToolbar->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonIconOnly);

    MonitorToolbar->addAction(monitorNowAct);
    MonitorToolbar->addAction(monitorSettingsAct);

}

//apply current settings (like language, teme, and other general settings
void CodeMonitorWindow::apply_settings() {
    MonitorNameLabel->setText( tr("Monitor: ") + monitor_name );
    AddFileButton->setText( tr("Add file") );
    AddFolderButton->setText( tr("Add folder") );
    MonitorNowButton->setText( tr("Monitor Now") );
    SettingsButton->setText( tr("Settings") );
    InformationLabel->setText( tr("Monitor:") + "   -     " );

    MonitorTree->setHeaderLabels( QStringList() << tr("Files") );

    refreshTree();

    setup_monitor_table();
    setup_view_table();
}

//connect all principal widgets signals to the corresponding slots
void CodeMonitorWindow::apply_slots() {

    connect( MonitorTree, SIGNAL(itemChanged(QTreeWidgetItem*, int )), this, SLOT(monitor_tree_item_clicked( QTreeWidgetItem*, int  )) );
    connect( AddFileButton, SIGNAL(clicked()), this, SLOT(add_file_button_clicked() ) );
    connect( AddFolderButton, SIGNAL(clicked()), this, SLOT(add_folder_button_clicked() ) );
    connect( SettingsButton, SIGNAL(clicked()), this, SLOT(settings_button_clicked() ) );
    connect( MonitorNowButton, SIGNAL(clicked()), this, SLOT(monitor_now_button_clicked() ) );
    connect( MonitorTable, SIGNAL( cellClicked( int, int ) ), this, SLOT( monitor_table_cell_clicked( int, int ) ) );
    connect( MonitorTable, SIGNAL(customContextMenuRequested(const QPoint& )), this, SLOT(monitor_table_context_menu( const QPoint& )));
    connect( MonitorTree, SIGNAL(customContextMenuRequested(const QPoint& )), this, SLOT(monitor_tree_context_menu( const QPoint& )));

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
            topLevelItem->setIcon( 0, QIcon( ":/img/icons/hdd.png" ) );
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
                parentItem->setIcon( 0, QIcon( ":/img/icons/folder.png" ) );

            }
        }

        QTreeWidgetItem *childItem = new QTreeWidgetItem(parentItem);
        childItem->setCheckState( 0, Qt::Unchecked );
        childItem->setFlags( childItem->flags() | Qt::ItemIsUserCheckable );
        childItem->setText(0, splitFileName.last());
        childItem->setToolTip(0, fileName );
    }
    MonitorTree->expandAll();

}


void CodeMonitorWindow::monitor_tree_item_clicked( QTreeWidgetItem* item, int column ) {
    setFilesToShow();
    refresh_monitor_table();
    refresh_view_table();
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

    GeneralSettingsDialog* settings_dialog = new GeneralSettingsDialog( monitor.getCurrentFilespath() ,this );
    settings_dialog->exec();

    delete settings_dialog;
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

void CodeMonitorWindow::monitor_table_cell_clicked( int row, int column ) {
    view = monitor.viewAt( row );
    refresh_view_table();
}

void CodeMonitorWindow::monitor_table_context_menu( const QPoint& pos ) {
    QModelIndex index = MonitorTable->indexAt( pos );

    if( index.row() != -1 ) {

        QMenu* menu = new QMenu( this );
        menu->addAction( deleteViewAct );

        menu->popup( MonitorTable->viewport()->mapToGlobal( pos ) );

    }
}

void CodeMonitorWindow::monitor_tree_context_menu( const QPoint& pos ) {
    QTreeWidgetItem* item = MonitorTree->itemAt( pos );

    if( item != nullptr ) {

        if( item->toolTip( 0 ) != "" ) {
            QMenu* menu = new QMenu( this );
            menu->addAction( deleteFileAct );

            menu->popup( MonitorTree->viewport()->mapToGlobal( pos ) );
        }

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

void CodeMonitorWindow::monitor_now_button_clicked( ) {

    //reset progress bar
    MonitorProgressBar->setValue( 0 );
    MonitorProgressBar->setRange(0,monitor.getCurrentFilespath().size() - 1);

    //analyze files
    monitor.MonitorNow( MonitorProgressBar );

    refresh_monitor_table();
    saved = false;

    MonitorTable->selectRow( MonitorTable->rowCount() - 1 );

    view = monitor.viewAt( MonitorTable->rowCount() - 1);
    refresh_view_table();
}

void CodeMonitorWindow::refresh_monitor_table() {

    //clearing all data
    MonitorTable->setRowCount( 0 );

    QFont default_font = QApplication::font();
    default_font.setBold( true );

    foreach( View current_view, monitor.getAllViews() ) {

        unsigned int total_lines = 0;       //number of total lines
        unsigned int size = 0;


        foreach( QString file, filesToShow ) {
            FileData current_file = current_view.getFileData( file );
            total_lines += current_file.getTotalLines();
            size += current_file.getSize();
        }

        //size from bytes to KB
        size /= 1024;

        MonitorTable->insertRow( MonitorTable->rowCount() );

        MonitorTable->setItem( MonitorTable->rowCount() - 1,
                               0,
                               new QTableWidgetItem( current_view.getDateTime().toString( "dd/MM/yyyy - hh:mm:ss.zzz" ) ) );

        MonitorTable->setItem( MonitorTable->rowCount() - 1,
                               1,
                               new QTableWidgetItem( QString::number( total_lines ) ) );

        MonitorTable->setItem( MonitorTable->rowCount() - 1,
                               2,
                               new QTableWidgetItem( QString::number( size ) ) );

        MonitorTable->item( MonitorTable->rowCount() - 1, 0 )->setTextAlignment(Qt::AlignCenter);
        MonitorTable->item( MonitorTable->rowCount() - 1, 0 )->setFont( default_font );

    }

}

void CodeMonitorWindow::closeEvent( QCloseEvent* event )  {
    if( saved == true ) {
        //db saved
        event->accept();

    } else if( monitor.getSettings().getMonitorSaveOnClosing() ) { //db not saved yet
        save();

    } else {
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
    addFileAct->setIcon(QIcon(":/img/icons/add_file.png"));
    connect( addFileAct, &QAction::triggered, this, &CodeMonitorWindow::add_file_slot );

    //add folder action
    addFolderAct = new QAction( tr( "&Add folder"), this );
    addFolderAct->setStatusTip( tr( "Add all files contained in a folder" ) );
    addFolderAct->setIcon(QIcon(":/img/icons/add_folder.png"));
    connect( addFolderAct, &QAction::triggered, this, &CodeMonitorWindow::add_folder_slot );

    //remove file action
    removeFileAct = new QAction( tr( "&Remove file"), this );
    removeFileAct->setShortcut( QKeySequence::Delete );
    removeFileAct->setStatusTip( tr( "Remove selected file" ) );
    removeFileAct->setIcon(QIcon(":/img/icons/criss-cross.png"));
    connect( removeFileAct, &QAction::triggered, this, &CodeMonitorWindow::remove_file_slot );

    //general settings action
    generalSettingsAct = new QAction( tr( "&General settings"), this );
    generalSettingsAct->setStatusTip( tr( "Open general settings dialog" ) );
    generalSettingsAct->setIcon(QIcon(":/img/icons/settings.png"));

    connect( generalSettingsAct, &QAction::triggered, this, &CodeMonitorWindow::general_settings_slot );

    //monitor settings action
    monitorSettingsAct = new QAction( tr( "&Monitor settings"), this );
    monitorSettingsAct->setStatusTip( tr( "Open monitor settings dialog" ) );
    monitorSettingsAct->setIcon(QIcon(":/img/icons/monitor_settings.png"));
    connect( monitorSettingsAct, &QAction::triggered, this, &CodeMonitorWindow::monitor_settings_slot );

    //about action
    aboutAct = new QAction( tr( "&About"), this );
    aboutAct->setStatusTip( tr( "About Code Monitor" ) );
    connect( aboutAct, &QAction::triggered, this, &CodeMonitorWindow::about_slot );

    //license action
    licenseAct = new QAction( tr( "&License"), this );
    licenseAct->setStatusTip( tr( "See program License" ) );
    connect( licenseAct, &QAction::triggered, this, &CodeMonitorWindow::license_slot );

    //--- table monitor context menu actions ---

    //delete view action
    deleteViewAct = new QAction( QIcon( ":img/icons/criss-cross.png"),
                                 tr( "Delete" ) );
    deleteViewAct->setIcon(QIcon(":/img/icons/criss-cross.png"));
    connect( deleteViewAct, &QAction::triggered, this, &CodeMonitorWindow::delete_view_slot );


    //--- table monitor context menu actions ---

    //delete file action
    deleteFileAct = new QAction( QIcon( ":img/icons/criss-cross.png"),
                                 tr( "Remove file" ) );
    deleteFileAct->setIcon(QIcon(":/img/icons/criss-cross.png"));
    connect( deleteFileAct, &QAction::triggered, this, &CodeMonitorWindow::delete_file_slot );


    //monitor now action
    monitorNowAct = new QAction( tr("$Monitor Now"), this );
    monitorNowAct->setIcon( QIcon(":/img/icons/monitor_now.png"));
    connect( monitorNowAct, &QAction::triggered, this, &CodeMonitorWindow::monitor_now_button_clicked );
}

//create menus
void CodeMonitorWindow::createMenus() {
    FileMenu = menuBar()->addMenu( tr( "&File" ) );
    FileMenu->addAction( saveAct );
    FileMenu->addSeparator();
    FileMenu->addAction( exitAct );

    MonitorMenu = menuBar()->addMenu( tr( "&Monitor" ) );
    MonitorMenu->addAction( addFileAct );
    MonitorMenu->addAction( addFolderAct );
    MonitorMenu->addSeparator();
    MonitorMenu->addAction( removeFileAct );

    SettingsMenu = menuBar()->addMenu( tr( "&Settings" ) );
    SettingsMenu->addAction( generalSettingsAct );
    SettingsMenu->addAction( monitorSettingsAct );

    HelpMenu = menuBar()->addMenu( tr( "&Help" ) );
    HelpMenu->addAction( aboutAct );
    HelpMenu->addAction( licenseAct );


}


void CodeMonitorWindow::refresh_view_table() {

    //clearing old dataa from table
    ViewTable->setRowCount( 0 );

    QFont default_font = QApplication::font();
    default_font.setBold( true );

    if( view != nullptr ) {

        InformationLabel->setText( tr("Monitor:") + "   " + view->getDateTime().toString("dd/MM/yyyy - hh:mm:ss.zzz") );

        QStringList filenames = view->getFilenames();
        QList<FileData> data = view->getData();
        FileData current_file;

        for( int i = 0; i < filesToShow.size(); ++i ) {
            current_file = view->getFileData( filesToShow.at(i) );

            ViewTable->insertRow( ViewTable->rowCount() );

            ViewTable->setItem( i, 0, new QTableWidgetItem( current_file.getFilename().split("/").last() ) );
            ViewTable->item( i, 0 )->setToolTip( current_file.getFilename() );
            ViewTable->setItem( i, 1, new QTableWidgetItem( QString::number(current_file.getTotalLines() ) ) );
            ViewTable->setItem( i, 2, new QTableWidgetItem( QString::number(current_file.getCodeLines() ) ) );
            ViewTable->setItem( i, 3, new QTableWidgetItem( QString::number(current_file.getCommentLines() ) ) );
            ViewTable->setItem( i, 4, new QTableWidgetItem( QString::number(current_file.getVoidLines() ) ) );
            ViewTable->setItem( i, 5, new QTableWidgetItem( QString::number(current_file.getChars() ) ) );

            //columns styles
            ViewTable->item( i, 1 )->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
            ViewTable->item( i, 2 )->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
            ViewTable->item( i, 3 )->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
            ViewTable->item( i, 4 )->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);


            ViewTable->item( i, 0 )->setFont( default_font );
        }

    } else {
        InformationLabel->setText( tr("Monitor:") + "    ---" );
    }
}

void CodeMonitorWindow::setup_monitor_table() {

    MonitorTable->setRowCount(0);
    MonitorTable->setColumnCount(3);
    MonitorTable->setHorizontalHeaderLabels( QStringList() << tr("Date") <<
                                                              tr("Total lines") <<
                                                              tr("Total Size(KB)") );

    MonitorTable->setColumnWidth(0,600);
    MonitorTable->setColumnWidth(1,300);
    MonitorTable->setColumnWidth(2,250);

    MonitorTable->horizontalHeader()->setStretchLastSection( true );

    MonitorTable->verticalHeader()->setVisible(true);
    MonitorTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    MonitorTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    MonitorTable->setSelectionMode(QAbstractItemView::SingleSelection);
    MonitorTable->setShowGrid(true);

}

void CodeMonitorWindow::setup_view_table() {

    //setting up table
    ViewTable->setRowCount( 0 );
    ViewTable->setColumnCount(5);
    ViewTable->setHorizontalHeaderLabels( QStringList() << tr("File") <<
                                                           tr("Total lines") <<
                                                           tr("Code lines") <<
                                                           tr("Comment lines") <<
                                                           tr("Void lines") <<
                                                           tr("Chars") <<
                                                           tr("Size(KB)") <<
                                                           tr("Language") );

    ViewTable->setColumnWidth( 0, 300 );
    ViewTable->setColumnWidth( 1, 120 );
    ViewTable->setColumnWidth( 2, 120 );
    ViewTable->setColumnWidth( 3, 120 );

    ViewTable->horizontalHeader()->setStretchLastSection( true );
    ViewTable->verticalHeader()->setVisible(true);
    ViewTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ViewTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ViewTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ViewTable->setShowGrid(true);



}

void CodeMonitorWindow::clear_view_table() {
    ViewTable->setRowCount( 0 );
    InformationLabel->setText( tr("Monitor:") + "   -     " );
}

//---- menu slots -----

void CodeMonitorWindow::exit_slot() {
    this->close();
}

void CodeMonitorWindow::save_slot() {
    this->save();
}
void CodeMonitorWindow::add_file_slot() {
    add_file_button_clicked();
}

void CodeMonitorWindow::add_folder_slot() {
    add_folder_button_clicked();
}

void CodeMonitorWindow::remove_file_slot() {
    delete_file_slot();
}

void CodeMonitorWindow::general_settings_slot() {
    GeneralSettingsDialog* settings_dialog = new GeneralSettingsDialog( monitor.getCurrentFilespath(), this );
    settings_dialog->exec();

    delete settings_dialog;
}

void CodeMonitorWindow::monitor_settings_slot() {

    //stop timer while settings dialog is open
    autosave_timer->stop();

    MonitorSettingsDialog* dialog = new MonitorSettingsDialog( monitor.getSettings() );

    dialog->exec();

    delete dialog;

    //set new autosave delay
    if( monitor.getSettings().getAutosave() ) {
        autosave_timer->start(monitor.getSettings().getAutosaveEveryMins()*1000*60);
    }
}

void CodeMonitorWindow::about_slot() {
    AboutDialog* about_dialog = new AboutDialog( this );

    about_dialog->exec();

    delete about_dialog;
}

void CodeMonitorWindow::license_slot() {
    LicenseDialog* license_dialog = new LicenseDialog( this );

    license_dialog->exec();

    delete license_dialog;
}

void CodeMonitorWindow::delete_view_slot() {
    if( MonitorTable->selectedItems().size() > 0 ) {

        int index = -1;

        for( int i = 0; i <  MonitorTable->rowCount(); ++i ) {
            if( MonitorTable->selectedItems().at(0) == MonitorTable->item(i,0) ) {
                index = i;
            }
        }

        if( index != -1 ) {
            monitor.removeView( index );
            refresh_monitor_table();
            saved = false;
            clear_view_table();
        }

    }
}

void CodeMonitorWindow::delete_file_slot() {

    if( MonitorTree->selectedItems().size() > 0 ) {
        if( MonitorTree->selectedItems().at(0)->toolTip(0) != "" ) {

            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, tr("Selete file"), tr("Are you sure you want to remove %1 from current monitor?").arg( "\"" + MonitorTree->selectedItems().at(0)->text(0) + "\""),
                                          QMessageBox::Yes|QMessageBox::No);

            //check if file must be removed from monitor
            if( reply == QMessageBox::Yes ) {
                monitor.removeFilespath( QStringList() << MonitorTree->selectedItems().at(0)->toolTip(0) );
                refreshTree();
                refresh_monitor_table();

            }
        } else {
            QMessageBox::warning( this, "Select a file!", "No file selected: Select a file to delete!");
        }
    }

}

void CodeMonitorWindow::autosave_slot() {
    this->save();
}
