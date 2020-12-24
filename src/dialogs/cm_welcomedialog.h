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

#ifndef CM_WELCOMEDIALOG_H
#define CM_WELCOMEDIALOG_H

#include <QString>
#include <QStringList>
#include <QFile>
#include <QDir>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>
#include <QFont>
#include <QApplication>

#include "dialogs/dialogs.h"
#include "dialogs/inputbox.h"
#include "dialogs/cm_mainwindow.h"
#include "dialogs/general_settings.h"

#include "common/filesutility.h"
#include "common/error.h"


class CM_WelcomeDialog : public GeneralWindow {
    Q_OBJECT

    public:
        CM_WelcomeDialog( QWidget* parent = nullptr, QString settings_filename_str = "config.ini" );
        ~CM_WelcomeDialog();

        //get all monitors entries
        QStringList monitorsList() const;

    private slots:
        void SettingsButtonClicked();
        void ExitButtonClicked();
        void NewMonitorButtonClicked();
        void OpenMonitorButtonClicked();
        void EditMonitorButtonClicked();
        void DeleteMonitorButtonCLicked();

    protected:
        //apply current settings (like language, teme, and other general settings
        void apply_settings() override;

        //connect all principal widgets signals to the corresponding slots
        void apply_slots() override;

        //configure the User Interface: allocating Widgets, layout, etc.
        void setup_ui() override;


        //refresh monitors list
        void refresh_monitor_widget();


        //widgets
        QWidget* MainWidget;
        QHBoxLayout* MainLayout;
        QGridLayout* ButtonsLayout;
        QVBoxLayout* MonitorLayout;
        QLabel* MonitorLabel;
        QListWidget* MonitorWidget;
        QPushButton* SettingsButton;
        QPushButton* ExitButton;
        QPushButton* NewMonitorButton;
        QPushButton* OpenMonitorButton;
        QPushButton* EditMonitorButton;
        QPushButton* DeleteMonitorButton;


        //database
        QSqlDatabase* db;

        QSqlDatabase* monitors_db;


};

#endif
