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

#ifndef LICENSEDIALOG_H
#define LICENSEDIALOG_H

#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QFile>
#include <QFont>

#include "dialogs/dialogs.h"

class LicenseDialog : public GeneralDialog {
    Q_OBJECT

    public:
        LicenseDialog( QWidget* parent = nullptr,
                       QString settings_filename_str = "config.ini"  );

        ~LicenseDialog();

    protected slots:
        void ok_button_clicked();

    protected:

        //widgets
        QVBoxLayout* MainLayout;
        QLabel* TitleLabel;
        QTextEdit* LicenseEdit;
        QHBoxLayout* ButtonsLayout;
        QPushButton* OkButton;



        //------ ui methods ------

        //apply current settings (like language, teme, and other general settings
        void apply_settings() override;

        //connect all principal widgets signals to the corresponding slots
        void apply_slots() override;

        //configure the User Interface: allocating Widgets, layout, etc.
        void setup_ui() override;



};

#endif
