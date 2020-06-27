#include "dialogs/dialogs.h"

GeneralWindow::GeneralWindow( QWidget* parent ) :
    QMainWindow(parent)
{
    //configuring ui, settings, and slots
    setup_ui();
    apply_settings();
    apply_slots();
}


GeneralWindow::~GeneralWindow() {

}




