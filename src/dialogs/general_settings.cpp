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

#include "dialogs/general_settings.h"


GeneralSettingsDialog::GeneralSettingsDialog( QWidget* parent , QString settings_filename_str ) :
    GeneralDialog( parent, settings_filename_str )
{

    this->resize( 750, 580 );

    //setup ui
    setup_ui();
    apply_settings();
    apply_slots();

    load();

    saved = false;

}

GeneralSettingsDialog::~GeneralSettingsDialog() {

}

//configure the User Interface: allocating Widgets, layout, etc.
void GeneralSettingsDialog::setup_ui() {
    MainLayout = new QVBoxLayout;
    StyleBox = new QGroupBox;
    StyleMainLayout = new QGridLayout;
    fontLabel = new QLabel;
    fontCombo = new QFontComboBox;
    sizeLabel = new QLabel;
    sizeSlider = new QSlider( Qt::Orientation::Horizontal );
    sizeLine = new QLineEdit;

    ProgLangBox = new QGroupBox;
    LangMainLayout = new QVBoxLayout;
    LangLabel = new QLabel;
    LangTable = new QTableWidget;
    LangButtonsLayout = new QHBoxLayout;
    AddLangButton = new QToolButton;
    RemoveLangButton = new QToolButton;
    EditLangButton = new QToolButton;

    GeneralBox = new QGroupBox;
    GeneralMainLayout = new QGridLayout;
    dateFormatLabel = new QLabel;
    dateFormatCombo = new QComboBox;

    ButtonsLayout = new QHBoxLayout;
    ConfirmButton = new QPushButton;
    CancelButton = new QPushButton;




    MainLayout->addWidget( StyleBox );
    StyleBox->setLayout( StyleMainLayout );
    StyleMainLayout->addWidget( fontLabel, 0, 0, 1, 1 );
    StyleMainLayout->addWidget( fontCombo, 0, 1, 1, 2 );
    StyleMainLayout->addWidget( sizeLabel, 1, 0 );
    StyleMainLayout->addWidget( sizeSlider, 1, 1 );
    StyleMainLayout->addWidget( sizeLine, 1, 2 );




    MainLayout->addWidget( ProgLangBox );
    ProgLangBox->setLayout( LangMainLayout );
    LangButtonsLayout->addWidget( AddLangButton );
    LangButtonsLayout->addWidget( RemoveLangButton );
    LangButtonsLayout->addWidget( EditLangButton );
    LangButtonsLayout->addStretch();
    LangMainLayout->addWidget( LangLabel );
    LangMainLayout->addWidget( LangTable );
    LangMainLayout->addLayout( LangButtonsLayout );

    MainLayout->addWidget( GeneralBox );
    GeneralBox->setLayout( GeneralMainLayout );
    GeneralMainLayout->addWidget( dateFormatLabel, 0, 0 );
    GeneralMainLayout->addWidget( dateFormatCombo, 0, 1 );


    MainLayout->addLayout( ButtonsLayout );
    ButtonsLayout->addStretch();
    ButtonsLayout->addWidget( ConfirmButton );
    ButtonsLayout->addWidget( CancelButton );

    this->setLayout( MainLayout );

    //other settings
    sizeLine->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );
    sizeLine->setMaximumWidth( 80 );
    sizeLine->setAlignment( Qt::AlignCenter );

    AddLangButton->setIcon( QIcon( ":/img/icons/more.png") );
    RemoveLangButton->setIcon( QIcon( ":/img/icons/criss-cross.png") );
    EditLangButton->setIcon( QIcon( ":/img/icons/pencil.png") );

    sizeLine->setReadOnly( true );
    dateFormatLabel->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );
    LangLabel->setAlignment( Qt::AlignCenter );


    CancelButton->setObjectName( "cancel" );
    ConfirmButton->setObjectName( "confirm" );



}

//apply current settings (like language, teme, and other general settings
void GeneralSettingsDialog::apply_settings() {

    ConfirmButton->setText( tr( "Save" ) );
    CancelButton->setText( tr( "Cancel" ) );

    StyleBox->setTitle( tr( "Style" ) );
    fontLabel->setText( tr( "Font:" ) );
    sizeLabel->setText( tr( "Font size:" ) );


    GeneralBox->setTitle( tr( "General" ) );
    dateFormatLabel->setText( tr( "date format:" ) );

    ProgLangBox->setTitle( tr( "Programming Languages" ) );
    LangLabel->setText( tr("Programming languages loaded:" ) );

    dateFormatCombo->clear();
    dateFormatCombo->addItem( "DD/MM/YYYY" );
    dateFormatCombo->addItem( "MM/DD/YYYY" );
    dateFormatCombo->addItem( "YYYY/MM/DD" );

    sizeSlider->setRange( 5, 25 );

    load();


}

//connect all principal widgets signals to the corresponding slots
void GeneralSettingsDialog::apply_slots() {

    connect( ConfirmButton, SIGNAL(clicked()), this, SLOT(confirm_button_clicked()));
    connect( CancelButton, SIGNAL(clicked()), this, SLOT(cancel_button_clicked()));
    connect( AddLangButton, SIGNAL(clicked()), this, SLOT(add_lang_button_clicked()));
    connect( RemoveLangButton, SIGNAL(clicked()), this, SLOT(remove_lang_button_clicked()));
    connect( EditLangButton, SIGNAL(clicked()), this, SLOT(edit_lang_button_clicked()));
    connect( sizeSlider, SIGNAL(valueChanged(int)), this, SLOT(size_slider_changed(int)));
    connect( LangTable, SIGNAL(cellDoubleClicked(int,int) ), this, SLOT(lang_table_cell_double_clicked(int,int)));

}

//load settings
void GeneralSettingsDialog::load() {
    fontCombo->setCurrentText( settings.getValue( "font_family" ) );
    sizeSlider->setValue(  settings.getValue( "font_size" ).toInt() );
    sizeLine->setText( settings.getValue( "font_size" ) );
    dateFormatCombo->setCurrentText( settings.getValue( "date_format" ) );

    //load all languages into lang table
    setup_lang_table();
}

//save settings
void GeneralSettingsDialog::save() {
    settings.setValue( "font_family", fontCombo->currentText() );
    settings.setValue( "font_size", QString::number(sizeSlider->value()) );
    settings.setValue( "date_format", dateFormatCombo->currentText() );
    settings.save();

    //clear rpogramming languages file
    QFile langs_file( QDir::currentPath() + "/programming_languages.ini" );
    langs_file.resize(0);


    //rewrite all data to programming langauges file
    QSettings prog_langs( QDir::currentPath() + "/programming_languages.ini", QSettings::IniFormat );

    for( int i = 0; i < LangTable->rowCount(); ++i ) {
        prog_langs.beginGroup( LangTable->item(i,0)->text() );

        prog_langs.setValue( "single_line_comment", LangTable->item(i,1)->text() );
        prog_langs.setValue( "multi_line_comment_start", LangTable->item(i,2)->text().split(" ").at(0) );
        prog_langs.setValue( "multi_line_comment_end", LangTable->item(i,2)->text().split(" ").at(1) );
        prog_langs.setValue( "files_extensions", LangTable->item(i,3)->text() );

        prog_langs.endGroup();
    }



}

//setup programming language table;
void GeneralSettingsDialog::setup_lang_table() {

    LangTable->setRowCount( 0 );
    LangTable->setColumnCount( 4 );

    //loading header table
    QStringList header;
    header << tr("Langauge") <<
              tr("Single line comment") <<
              tr("Multi line comment") <<
              tr("Extenstions");

    LangTable->setHorizontalHeaderLabels( header );
    LangTable->horizontalHeader()->setStretchLastSection(true);
    LangTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    LangTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    LangTable->setSelectionMode(QAbstractItemView::SingleSelection);

    LangTable->setColumnWidth( 0 , 110 );
    LangTable->setColumnWidth( 1 , 200 );
    LangTable->setColumnWidth( 2 , 200 );


    //languages are stored in programming_languages.ini
    QSettings prog_langs( QDir::currentPath() + "/programming_languages.ini", QSettings::IniFormat );
    QStringList languages = prog_langs.childGroups();
    for( int i = 0; i < languages.size(); ++i ) {
        prog_langs.beginGroup( languages.at(i) );

        LangTable->insertRow( LangTable->rowCount() );

        LangTable->setItem( LangTable->rowCount() - 1, 0, new QTableWidgetItem( languages.at(i) ) );
        LangTable->setItem( LangTable->rowCount() - 1, 1, new QTableWidgetItem( prog_langs.value( "single_line_comment" ).toString() ) );
        LangTable->setItem( LangTable->rowCount() - 1, 2, new QTableWidgetItem( prog_langs.value( "multi_line_comment_start" ).toString() +
                                                                                " " +
                                                                                prog_langs.value( "multi_line_comment_end" ).toString()) );
        LangTable->setItem( LangTable->rowCount() - 1, 3, new QTableWidgetItem( prog_langs.value( "files_extensions" ).toString() ) );


        prog_langs.endGroup();
    }
}

// ---- slots funxtions ----

void GeneralSettingsDialog::confirm_button_clicked() {
    this->close();
    save();
    saved = true;
}

void GeneralSettingsDialog::cancel_button_clicked() {
    this->close();
}

void GeneralSettingsDialog::add_lang_button_clicked() {
    LanguageDialog* language_dialog = new LanguageDialog( tr("New language:") );
    language_dialog->exec();

    //check if form was confirmer or not
    if(language_dialog->wasFormConfirmed() ) {
        //form confirmed, so new prog lang must be added

        ProgrammingLanguage lang = language_dialog->getLanguage();

        //check if a language with the same name is present
        bool langIsPresent = false;
        for( int i = 0; i < LangTable->rowCount(); ++i ) {
            if( LangTable->item(i,0)->text() == lang.getName() ) {
                langIsPresent = true;
            }
        }

        if( langIsPresent) {
            //a language with the same name is already present
            QMessageBox::critical( this,
                                   tr("Error"),
                                   tr("Language %1 is already present!").arg( "\"" + lang.getName() + "\"") );


        } else {
            //new language is unique, so it can be added
            LangTable->insertRow( LangTable->rowCount() );
            LangTable->setItem( LangTable->rowCount() - 1, 0, new QTableWidgetItem(lang.getName()) );
            LangTable->setItem( LangTable->rowCount() - 1, 1, new QTableWidgetItem(lang.getSingleLine() ) );
            LangTable->setItem( LangTable->rowCount() - 1, 2, new QTableWidgetItem( lang.getMultiLineStart() +
                                                                                    " " +
                                                                                    lang.getMultiLineEnd() ) );


            QString extensions_list_str = "";

            foreach( QString ext, lang.getExtensions() ) {
                extensions_list_str += ext + " ";
            }
            LangTable->setItem( LangTable->rowCount() - 1, 3, new QTableWidgetItem( extensions_list_str ) );

        }

    }
}

void GeneralSettingsDialog::remove_lang_button_clicked() {
    if( LangTable->selectedItems().size() == 0 ) {
        QMessageBox::critical( this, tr("Error"), tr("Select a language!") );
    } else {
        QString languageName = LangTable->selectedItems().at(0)->text();
        int index = -1;

        for ( int i = 0; i < LangTable->rowCount(); ++i ) {
            if( LangTable->item( i, 0 )->text() == languageName ) {
                index = i;
            }
        }

        if( index != -1 ) {
            LangTable->removeRow( index );
        }
    }
}

void GeneralSettingsDialog::edit_lang_button_clicked() {
    if( LangTable->selectedItems().size() == 0 ) {
        QMessageBox::critical( this, tr("Error"), tr("Select a language!") );
    } else {
        QString languageName = LangTable->selectedItems().at(0)->text();
        int index = -1;

        for ( int i = 0; i < LangTable->rowCount(); ++i ) {
            if( LangTable->item( i, 0 )->text() == languageName ) {
                index = i;
            }
        }

        if( index != -1 ) {

            ProgrammingLanguage lang;

            lang.setName( LangTable->item( index, 0 )->text() );
            lang.setSingleLine( LangTable->item( index, 1 )->text() );
            lang.setMultiLineEnd( LangTable->item( index, 2 )->text().split( " " ).at(1) );
            lang.setMultiLineStart( LangTable->item( index, 2 )->text().split( " " ).at(0) );
            lang.setExtensions( LangTable->item( index, 3 )->text().split( " " ) );

            LanguageDialog* language_dialog = new LanguageDialog( tr("Edit language"), lang );

            language_dialog->exec();

            //check if form was confirmed or not
            if( language_dialog->wasFormConfirmed() ) {
                //form confirmed, so new prog lang must be added

                lang = language_dialog->getLanguage();

                //check if a language with the same name is present
                bool langIsPresent = false;
                for( int i = 0; i < LangTable->rowCount(); ++i ) {
                    if( LangTable->item(i,0)->text() == lang.getName() && i != index ) {
                        langIsPresent = true;
                    }
                }

                if( langIsPresent) {
                    //a language with the same name is already present
                    QMessageBox::critical( this,
                                           tr("Error"),
                                           tr("Language %1 is already present!").arg( "\"" + lang.getName() + "\"") );


                } else {
                    //new language is unique, so it can be modified
                    LangTable->setItem( index, 0, new QTableWidgetItem(lang.getName()) );
                    LangTable->setItem( index, 1, new QTableWidgetItem(lang.getSingleLine() ) );
                    LangTable->setItem( index, 2, new QTableWidgetItem( lang.getMultiLineStart() +
                                                                        " " +
                                                                        lang.getMultiLineEnd() ) );


                    QString extensions_list_str = "";

                    foreach( QString ext, lang.getExtensions() ) {
                        extensions_list_str += ext + " ";
                    }
                    LangTable->setItem( index, 3, new QTableWidgetItem( extensions_list_str ) );

                }
            }
        }
    }
}

void GeneralSettingsDialog::size_slider_changed( int value ) {
    sizeLine->setText( QString::number( value ) );
}

void GeneralSettingsDialog::lang_table_cell_double_clicked( int row, int column ) {
    edit_lang_button_clicked();
}

