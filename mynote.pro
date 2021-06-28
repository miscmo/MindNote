QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Buffer.cpp \
    BufferManager.cpp \
    FileExplorer.cpp \
    MainWindow.cpp \
    Node.cpp \
    NoteMenuBar.cpp \
    Notebook.cpp \
    NotebookManager.cpp \
    ViewArea.cpp \
    config.cpp \
    main.cpp \
    noteeditor.cpp \
    noteexplorer.cpp \
    utils.cpp \
    viewwindow.cpp

HEADERS += \
    Buffer.h \
    BufferManager.h \
    FileExplorer.h \
    GSingleton.h \
    MainWindow.h \
    Node.h \
    NoteMenuBar.h \
    Notebook.h \
    NotebookManager.h \
    ViewArea.h \
    base.h \
    config.h \
    noteeditor.h \
    noteexplorer.h \
    utils.h \
    viewwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
