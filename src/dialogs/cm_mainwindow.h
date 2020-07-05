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

#include <QMainWindow>
#include <QLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QLineEdit>
#include <QLabel>
#include <QList>
#include <QString>
#include <QStringList>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>
#include <QTreeWidget>
#include <QGroupBox>
#include <QFileDialog>
#include <QDirIterator>
#include <QHeaderView>
#include <QMessageBox>
#include <QCloseEvent>
#include <QProgressDialog>

#include "dialogs/dialogs.h"
#include "common/textsanitizer.h"
#include "monitor.h"
#include "dialogs/filesdialog.h"

class CodeMonitorWindow : public GeneralWindow {
    Q_OBJECT

    public:
        CodeMonitorWindow( QString monitor_name_str, QWidget* parent = nullptr, QString settings_filename_str = "config.ini" );
        ~CodeMonitorWindow();

    protected slots:
        void monitor_tree_item_clicked( QTreeWidgetItem* item, int column );
        void add_file_button_clicked();
        void settings_button_clicked();
        void add_folder_button_clicked();
        void monitor_now_button_clicked();

    protected:
        //apply current settings (like language, teme, and other general settings
        void apply_settings() override;

        //connect all principal widgets signals to the corresponding slots
        void apply_slots() override;

        //configure the User Interface: allocating Widgets, layout, etc.
        void setup_ui() override;


        void closeEvent( QCloseEvent* event ) override;

        //data
        QString monitor_name;
        Monitor monitor;

        //widgets
        QWidget* MainWidget;
        QHBoxLayout* MainLayout;
        QSplitter* CentralSplitter;
        QWidget* LeftWidget;
        QWidget* RightWidget;
        QVBoxLayout* LeftLayout;
        QLabel* MonitorNameLabel;
        QTreeWidget* MonitorTree;
        QVBoxLayout* RightLayout;
        QVBoxLayout* RightSplitterLayout;
        QSplitter* RightSplitter;
        QTableWidget* MonitorTable;
        QGroupBox* DataGroup;
        QHBoxLayout* ButtonsLayout;
        QPushButton* AddFileButton;
        QPushButton* AddFolderButton;
        QPushButton* SettingsButton;
        QPushButton* MonitorNowButton;



        //other ---

        void refreshTree();
        QStringList filesToShow;
        void setFilesToShow();
        void checkTreeItemsState( QTreeWidgetItem* item );
        void refresh_monitor_table();
        void save();

        //keep trace of save state.
        bool saved;


};





