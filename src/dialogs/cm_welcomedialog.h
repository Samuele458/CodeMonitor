
#include <QString>
#include <QStringList>
#include <QFile>
#include <QDir>
#include "dialogs/dialogs.h"


class CM_WelcomeDialog : public GeneralDialog {
    Q_OBJECT

    public:
        CM_WelcomeDialog( QWidget* parent = nullptr, QString settings_filename_str = "config.ini" );
        ~CM_WelcomeDialog();

        //apply current settings (like language, teme, and other general settings
        void apply_settings() override;

        //connect all principal widgets signals to the corresponding slots
        void apply_slots() override;

        //configure the User Interface: allocating Widgets, layout, etc.
        void setup_ui() override;

    protected:

};
