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
#include <QDialog>
#include <QString>
#include "common/managers.h"


//class in common between GeneralDialog and GeneralWindow.
//It is used to manage settings, slots, and other.
class WindowManager {

    public:

        WindowManager( QString settings_filename_str );

        ~WindowManager() { };

    protected:
        //apply current settings (like language, teme, and other general settings
        virtual void apply_settings() { }

        //connect all principal widgets signals to the corresponding slots
        virtual void apply_slots() { }

        //configure the User Interface: allocating Widgets, layout, etc.
        virtual void setup_ui() { }

        //settings manager
        ManagerFromFile settings;
};


//General window used for main window
class GeneralWindow : public QMainWindow, public WindowManager {
    Q_OBJECT

    public:
        GeneralWindow( QWidget* parent = nullptr, QString settings_filename_str = "config.ini" );
        ~GeneralWindow();

};

//general dialog
class GeneralDialog : public QDialog, public WindowManager {
    Q_OBJECT
public:
    GeneralDialog( QWidget* parent = nullptr, QString settings_filename_str = "config.ini" );
    ~GeneralDialog();
};





