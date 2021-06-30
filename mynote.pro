QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Buffer.cpp \
    BufferManager.cpp \
    Config.cpp \
    FileExplorer.cpp \
    MainWindow.cpp \
    Node.cpp \
    NoteEditor.cpp \
    NoteExplorer.cpp \
    NoteMenuBar.cpp \
    NoteState.cpp \
    Notebook.cpp \
    NotebookManager.cpp \
    Utils.cpp \
    ViewArea.cpp \
    ViewWindow.cpp \
    main.cpp

HEADERS += \
    Buffer.h \
    BufferManager.h \
    Config.h \
    FileExplorer.h \
    GSingleton.h \
    MainWindow.h \
    Node.h \
    NoteEditor.h \
    NoteExplorer.h \
    NoteMenuBar.h \
    NoteState.h \
    Notebook.h \
    NotebookManager.h \
    Utils.h \
    ViewArea.h \
    ViewWindow.h \
    base.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
