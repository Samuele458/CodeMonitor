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

#include "dialogs/filesdialog.h"

FilesDialog::FilesDialog( QStringList filenames_list,
                          QWidget* parent,
                          QString settings_filename_str ) :
    GeneralDialog( parent, settings_filename_str )
{

    input_filenames = filenames_list;

    form_confirmed = false;

    //setting up ui
    setup_ui();
    apply_settings();
    apply_slots();


}

FilesDialog::~FilesDialog() {

}

//configure the User Interface: allocating Widgets, layout, etc.
void FilesDialog::setup_ui() {

    MainLayout = new QVBoxLayout;
    ButtonsLayout = new QHBoxLayout;
    CancelButton = new QPushButton;
    ConfirmButton = new QPushButton;
    FilesTable = new QTableWidget;
    TitleLabel = new QLabel;
    ValidFilesLabel = new QLabel;
    InvalidFilesLabel = new QLabel;

    ButtonsLayout->addStretch();
    ButtonsLayout->addWidget( ConfirmButton );
    ButtonsLayout->addWidget( CancelButton );
    MainLayout->addWidget( TitleLabel );
    MainLayout->addWidget( FilesTable );
    MainLayout->addWidget( ValidFilesLabel );
    MainLayout->addWidget( InvalidFilesLabel );
    MainLayout->addLayout( ButtonsLayout );


    MainLayout->setMargin( 5 );

    this->setLayout( MainLayout );

}

//apply current settings (like language, teme, and other general settings
void FilesDialog::apply_settings()  {
    TitleLabel->setText( tr("Selected files:") );
    CancelButton->setText( tr("Cancel") );
    ConfirmButton->setText( tr("Load") );


    this->resize( 1100, 400 );
    //loading table
    QStringList table_header;
    table_header << tr("File") <<
                    tr("Format") <<
                    "";

    FilesTable->setRowCount( 0 );
    FilesTable->setColumnCount( 3 );
    FilesTable->setHorizontalHeaderLabels( table_header );
    FilesTable->verticalHeader()->setVisible(true);
    FilesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    FilesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    FilesTable->setSelectionMode(QAbstractItemView::SingleSelection);
    FilesTable->setShowGrid(false);
    FilesTable->horizontalHeader()->setStretchLastSection( true );
    FilesTable->setColumnWidth(0,650);
    FilesTable->setColumnWidth(1,80);

    //files counters
    unsigned int valid_files_count = 0;
    unsigned int invalid_files_count = 0;


    //addint items to table
    foreach( QString filename, input_filenames ) {
        FilesTable->insertRow( FilesTable->rowCount() );
        FilesTable->setItem( FilesTable->rowCount() - 1,
                             0,
                             new QTableWidgetItem(filename) );
        QString extension;
        extension = FilesUtilities::getFileExtension( filename );
        if( FilesUtilities::getProgLangName( extension ) != "" ) {
            //correct file type
            FilesTable->setItem( FilesTable->rowCount() - 1,
                                 1,
                                 new QTableWidgetItem( FilesUtilities::getProgLangName( extension ) ) );
            output_filenames.push_back( filename );

            ++valid_files_count;
        } else {
            //unknown file type

            FilesTable->setItem( FilesTable->rowCount() - 1,
                                 1,
                                 new QTableWidgetItem(tr("Invalid")) );

            FilesTable->setItem( FilesTable->rowCount() - 1,
                                 2,
                                 new QTableWidgetItem( tr("File not loadable: unknown format") ) );

            WidgetsUtilities::colorTableWidgetRow( FilesTable, FilesTable->rowCount()-1, QColor( 255, 100, 100 ) );

            ++invalid_files_count;
        }
    }


    ValidFilesLabel->setText( tr("Valid files:") + " " + QString::number( valid_files_count ) );
    InvalidFilesLabel->setText( tr("Invalid files:") + " " + QString::number( invalid_files_count ) );


}


//connect all principal widgets signals to the corresponding slots
void FilesDialog::apply_slots()  {
    connect( ConfirmButton, SIGNAL(clicked()), this, SLOT(confirm_button_clicked() ) );
    connect( CancelButton, SIGNAL(clicked()), this, SLOT(cancel_button_clicked()));
}

//getter - setter methods

QStringList FilesDialog::getInputFilenames() const {
    return input_filenames;
}

QStringList FilesDialog::getOutputFilenames() const {
    return output_filenames;
}

// ------------------

bool FilesDialog::wasFormConfirmed() {
    return form_confirmed;
}

void FilesDialog::confirm_button_clicked() {
    form_confirmed = true;
    this->close();
}

void FilesDialog::cancel_button_clicked() {
    this->close();
}















