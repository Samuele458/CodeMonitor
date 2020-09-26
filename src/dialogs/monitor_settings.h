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

#ifndef MONITOR_SETTINGS_H
#define MONITOR_SETTINGS_H

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>
#include <QGridLayout>
#include <QLineEdit>
#include <QCheckBox>
#include <QRadioButton>

#include "dialogs/dialogs.h"
#include "common/textsanitizer.h"
#include "common/managers.h"
#include "monitor.h"



class MonitorSettingsDialog : public GeneralDialog {
    Q_OBJECT

    public:
        MonitorSettingsDialog( MonitorSettings settings_manager_in,
                               QWidget* parent = nullptr,
                               QString settings_filename_str = "config.ini" );

        ~MonitorSettingsDialog();


    protected slots:
        void confirm_button_clicked();
        void cancel_button_clicked();

    protected:

        //widgets
        QVBoxLayout* MainLayout;

        QGroupBox* SaveGroup;
        QGridLayout* SaveLayout;
        QCheckBox* AutosaveCheckbox;
        QHBoxLayout* AutosaveLayout;
        QLabel* EveryLabel;
        QLineEdit* TimeLine;
        QLabel* MinutesLabel;
        QLabel* WhenClosingLabel;
        QRadioButton* AskRadio;
        QRadioButton* AutosaveRadio;

        QGroupBox* DataGroup;
        QGridLayout* DataLayout;
        QCheckBox* DontDuplicateCheckbox;

        QHBoxLayout* ButtonsLayout;
        QPushButton* ConfirmButton;
        QPushButton* CancelButton;



        //apply current settings (like language, teme, and other general settings
        void apply_settings() override;

        //connect all principal widgets signals to the corresponding slots
        void apply_slots() override;

        //configure the User Interface: allocating Widgets, layout, etc.
        void setup_ui() override;

        void load();
        void save();

        bool saved;

        MonitorSettings monitor_settings;

};


#endif
