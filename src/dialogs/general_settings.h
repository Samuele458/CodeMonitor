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

#ifndef GENERAL_SETTINGS_H
#define GENERAL_SETTINGS_H

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSlider>
#include <QComboBox>
#include <QFontComboBox>
#include <QFont>
#include <QGroupBox>
#include <QTableWidget>
#include <QToolButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QSizePolicy>
#include <QIcon>
#include <QSettings>
#include <QHeaderView>
#include <QMessageBox>
#include <QStringList>


#include "dialogs/dialogs.h"
#include "dialogs/languagedialog.h"

class GeneralSettingsDialog : public GeneralDialog {
    Q_OBJECT

    public:
        GeneralSettingsDialog( QWidget* parent = nullptr, QString settings_filename_str = "config.ini" );
        GeneralSettingsDialog( QStringList openedFiles, QWidget* parent = nullptr, QString settings_filename_str = "config.ini" );
        ~GeneralSettingsDialog();



    protected slots:
        void confirm_button_clicked();
        void cancel_button_clicked();
        void add_lang_button_clicked();
        void remove_lang_button_clicked();
        void edit_lang_button_clicked();
        void size_slider_changed( int value );
        void lang_table_cell_double_clicked( int row, int column );


    protected:
        //apply current settings (like language, teme, and other general settings
        void apply_settings() override;

        //connect all principal widgets signals to the corresponding slots
        void apply_slots() override;

        //configure the User Interface: allocating Widgets, layout, etc.
        void setup_ui() override;


        void load();
        void save();

        //setup programming language table;
        void setup_lang_table();

        bool saved;

        QStringList& openedFiles;

        //widgets
        QVBoxLayout* MainLayout;
        QGroupBox* StyleBox;
        QGridLayout* StyleMainLayout;
        QLabel* fontLabel;
        QFontComboBox* fontCombo;
        QLabel* sizeLabel;
        QSlider* sizeSlider;
        QLineEdit* sizeLine;

        QGroupBox* ProgLangBox;
        QVBoxLayout* LangMainLayout;
        QLabel* LangLabel;
        QTableWidget* LangTable;
        QHBoxLayout* LangButtonsLayout;
        QToolButton* AddLangButton;
        QToolButton* RemoveLangButton;
        QToolButton* EditLangButton;

        QGroupBox* GeneralBox;
        QGridLayout* GeneralMainLayout;
        QLabel* dateFormatLabel;
        QComboBox* dateFormatCombo;

        QHBoxLayout* ButtonsLayout;
        QPushButton* ConfirmButton;
        QPushButton* CancelButton;


};


#endif
















