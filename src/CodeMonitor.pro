QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    common/error.cpp \
    common/filesutility.cpp \
    common/managers.cpp \
    common/textsanitizer.cpp \
    dialogs/aboutdialog.cpp \
    dialogs/cm_mainwindow.cpp \
    dialogs/cm_welcomedialog.cpp \
    dialogs/dialogs.cpp \
    dialogs/filesdialog.cpp \
    dialogs/general_settings.cpp \
    dialogs/inputbox.cpp \
    dialogs/languagedialog.cpp \
    dialogs/licensedialog.cpp \
    dialogs/monitor_settings.cpp \
    main.cpp \
    monitor.cpp \
    widgets/widgets_utilities.cpp

HEADERS += \
    common/error.h \
    common/filesutility.h \
    common/managers.h \
    common/textsanitizer.h \
    common/version.h \
    dialogs/aboutdialog.h \
    dialogs/cm_mainwindow.h \
    dialogs/cm_welcomedialog.h \
    dialogs/dialogs.h \
    dialogs/filesdialog.h \
    dialogs/general_settings.h \
    dialogs/inputbox.h \
    dialogs/languagedialog.h \
    dialogs/licensedialog.h \
    dialogs/monitor_settings.h \
    monitor.h \
    widgets/widgets_utilities.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

#IDI_ICON1 ICON    "/img/icons/applogo.ico"

#RC_FILE = resources.qrc
RC_ICONS = img/icons/applogo.ico
