#include "dialogs/inputbox.h"


InputBox::InputBox( QString title_str,
                    QString message_str,
                    QWidget* parent,
                    QString settings_filename_str  ) :
    GeneralDialog( parent, settings_filename_str ),
    title( title_str ),
    message( message_str )
{

    input_type = TextSanitizer::TYPES::LETTER |
                 TextSanitizer::TYPES::DIGIT;

    form_confirmed = false;

    //setting up ui
    setup_ui();
    apply_settings();
    apply_slots();
}


InputBox::~InputBox() {

}


//getter - setter methods
void InputBox::setTitle( QString title_str ) {
    title = title_str;
}

QString InputBox::getTitle() const {
    return title;
}

void InputBox::setMessage( QString message_str ) {
    message = message_str;
}

QString InputBox::getMessage() const {
    return message;
}

QString InputBox::getInputStr() const {
    return input;
}

bool InputBox::wasFormConfirmed() const {
    return form_confirmed;
}


//apply current settings (like language, teme, and other general settings
void InputBox::apply_settings() {

}



//configure the User Interface: allocating Widgets, layout, etc.
void InputBox::setup_ui() {
    MainLayout = new QGridLayout;
    EnterMessageLabel = new QLabel;
    InputLine = new QLineEdit;
    ConfirmButton = new QPushButton;
    CancelButton = new QPushButton;

    MainLayout->addWidget( EnterMessageLabel, 0, 0 );
    MainLayout->addWidget( InputLine, 1, 0, 1, 3 );
    MainLayout->addWidget( ConfirmButton, 2, 0 );
    MainLayout->addWidget( CancelButton, 2, 2 );
    this->setLayout( MainLayout );

    ConfirmButton->setText( tr("Confirm") );
    CancelButton->setText( tr("Cancel") );
    EnterMessageLabel->setText( message );
    this->setWindowTitle( title );
}

// ----- slots -----

//connect all principal widgets signals to the corresponding slots
void InputBox::apply_slots() {
    connect( ConfirmButton, SIGNAL(clicked()), this, SLOT(confirm_button_clicked()));
    connect( CancelButton, SIGNAL(clicked()), this, SLOT(cancel_button_clicked()));
}

void InputBox::confirm_button_clicked() {
    if( InputLine->text() != "" ) {
        form_confirmed = true;
        input = InputLine->text();
        this->close();
    } else {
        QMessageBox::warning( this, tr("Error"), tr("Enter a monitor name!") );
    }
}

void InputBox::cancel_button_clicked() {
    form_confirmed = false;
    this->close();
}








