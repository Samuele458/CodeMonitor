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


#include <QLayout>
#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QHeaderView>

#include "dialogs/dialogs.h"
#include "common/filesutility.h"
#include "widgets/widgets_utilities.h"

#ifndef FILESDIALOG_H
#define FILESDIALOG_H

class FilesDialog : public GeneralDialog {
    Q_OBJECT

public:
    FilesDialog( QStringList filenames_list,
                 QWidget* parent = nullptr,
                 QString settings_filename_str = "config.ini" );

    ~FilesDialog();

    //getter - setter methods
    QStringList getInputFilenames() const;
    QStringList getOutputFilenames() const;


    bool wasFormConfirmed();

protected slots:
    void confirm_button_clicked();
    void cancel_button_clicked();

protected:
    QStringList input_filenames;
    QStringList output_filenames;

    //widgets
    QVBoxLayout* MainLayout;
    QHBoxLayout* ButtonsLayout;
    QPushButton* CancelButton;
    QPushButton* ConfirmButton;
    QTableWidget* FilesTable;
    QLabel* TitleLabel;
    QLabel* ValidFilesLabel;
    QLabel* InvalidFilesLabel;


    bool form_confirmed;


    //apply current settings (like language, teme, and other general settings
    void apply_settings() override;

    //connect all principal widgets signals to the corresponding slots
    void apply_slots() override;

    //configure the User Interface: allocating Widgets, layout, etc.
    void setup_ui() override;
};

#endif
