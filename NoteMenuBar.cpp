#include "NoteMenuBar.h"

#include <MainWindow.h>

namespace gnote {

NoteMenuBar *NoteMenuBar::getInstance() {
    static NoteMenuBar noteMenuBar(MainWindow::getInstance());
    return &noteMenuBar;
}

NoteMenuBar::NoteMenuBar(QWidget *parent)
    : QMenuBar(parent) {
    initUi();
}

void NoteMenuBar::initUi() {
    QMenu *menuFile = addMenu("File");
    QAction *actionOpenDir = menuFile->addAction("Open");
    QAction *actionSaveFile = menuFile->addAction("Save");
    QAction *actionExit = menuFile->addAction("Exit");

}

NoteMenuBar::~NoteMenuBar() {
}

}
