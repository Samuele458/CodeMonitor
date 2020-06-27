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


#include "dialogs/dialogs.h"


//------ WindowManager -------
WindowManager::WindowManager( QString settings_filename_str ) : settings( settings_filename_str ) {

}



//------ GeneralWindow class ------
GeneralWindow::GeneralWindow( QWidget* parent, QString settings_filename_str ) :
    QMainWindow(parent),
    WindowManager( settings_filename_str )
{
    //configuring ui, settings, and slots
    setup_ui();
    apply_settings();
    apply_slots();
}


GeneralWindow::~GeneralWindow() {

}


//------ GeneralDialog class ------
GeneralDialog::GeneralDialog( QWidget* parent, QString settings_filename_str ) :
    QDialog(parent),
    WindowManager( settings_filename_str )
{
    //configuring ui, settings, and slots
    setup_ui();
    apply_settings();
    apply_slots();
}


GeneralDialog::~GeneralDialog() {

}





