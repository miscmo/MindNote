QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TARGET = MyNote
TEMPLATE = app

include($$PWD/Utils/Utils.pri)
include($$PWD/Config/Config.pri)
include($$PWD/Widgets/Widgets.pri)
include($$PWD/Notebook/Notebook.pri)
include($$PWD/Model/Model.pri)

SOURCES += \
    Main.cpp \
    MyNote.cpp

HEADERS += \
    MyNote.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


RESOURCES += \
    res.qrc
