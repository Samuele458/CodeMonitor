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
        monitor.addFilespath( fileNames );
        refreshTree();
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
        monitor.addFilespath( fileNames );
        refreshTree();
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
    monitor.
}







