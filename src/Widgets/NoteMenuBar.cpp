#include "NoteMenuBar.h"

#include "MainWindow.h"

#include <MyNote.h>
#include <Notebook/NotebookManager.h>
#include <Notebook/BufferManager.h>

#include <QAction>
#include <QMenu>
#include <QFileDialog>
#include <QDebug>

namespace MyNote {

NoteMenuBar *NoteMenuBar::m_pInstance = nullptr;

NoteMenuBar *NoteMenuBar::getInstance() {
    if (!m_pInstance)
        m_pInstance = new NoteMenuBar(MyNote::getInstance()->getMainWindow());
    return m_pInstance;
}

NoteMenuBar::NoteMenuBar(QWidget *parent)
    : QMenuBar(parent) {
    initUi();
}

void NoteMenuBar::initUi() {
    auto openDir = [=]() {
        QString dir = QFileDialog::getExistingDirectory(
                    this, tr("Open Directory"),
                    "",
                    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks );

        NotebookManager::getInstance()->resetNote(dir);
    };

    auto saveNote = [=]() {
        BufferManager::getInstance()->saveBuffer();
    };

    auto ExitApp = []() {
        MyNote::getInstance()->getMainWindow()->close();
    };

   QMenu *menuFile = addMenu("File");
   QAction *actionOpenDir = menuFile->addAction("Open");
   QAction *actionSaveFile = menuFile->addAction("Save");
   QAction *actionExit = menuFile->addAction("Exit");

   connect(actionOpenDir, &QAction::triggered, openDir);
   connect(actionSaveFile, &QAction::triggered, saveNote);
   connect(actionExit, &QAction::triggered, ExitApp);

   QMenu *menuAbout = addMenu("about");
}

NoteMenuBar::~NoteMenuBar() {
}

}
