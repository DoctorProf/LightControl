QT += quick network widgets

SOURCES += \
        Sources/networkutils.cpp \
        main.cpp \
        Sources/requesthandler.cpp

CONFIG += c++17

resources.files = Layouts/main.qml
resources.prefix = /$${TARGET}
RESOURCES += resources \
    resources.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RC_FILE = desktop.rc

HEADERS += \
    Headers/colordialoghelper.h \
    Headers/networkutils.h \
    Headers/requesthandler.h

DISTFILES += \
    Layouts/MainPage.qml \
    Layouts/Snackbar.qml \
    Resources/colors
