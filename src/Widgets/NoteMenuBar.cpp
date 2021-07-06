#include "NoteMenuBar.h"

#include "MainWindow.h"

#include <MyNote.h>
#include <Config/Config.h>
#include <Config/AppState.h>
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
    : QMenuBar(parent)
    , m_pSignalMapper(nullptr) {
    initUi();
}

void NoteMenuBar::initUi() {
    auto openDir = [=]() {
        QString dir = QFileDialog::getExistingDirectory(
                    this, tr("Open Directory"),
                    "",
                    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks );

        NotebookManager::getInstance()->setCurNotebook(dir);
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
   menuFile->addSeparator();
   QMenu *subMenuRecentlyFile = menuFile->addMenu("Recently");
   initRecentlyFileList(subMenuRecentlyFile);
   menuFile->addSeparator();
   QAction *actionExit = menuFile->addAction("Exit");

   connect(actionOpenDir, &QAction::triggered, openDir);
   connect(actionSaveFile, &QAction::triggered, saveNote);
   connect(actionExit, &QAction::triggered, ExitApp);

   QMenu *menuAbout = addMenu("about");
}

void NoteMenuBar::initRecentlyFileList(QMenu *menuRecentlyFile) {
    Q_ASSERT(menuRecentlyFile);

    auto onOpenRecentlyFile = [=](const QAction *action) {
        QString path = action->text();
        NotebookManager::getInstance()->setCurNotebook(path);
    };

    QStringList fileList = AppState::getInstance()->getRecentlyDirList();

    for (auto file : fileList) {
        menuRecentlyFile->addAction(file);
    }

    connect(menuRecentlyFile, &QMenu::triggered, onOpenRecentlyFile);

}

NoteMenuBar::~NoteMenuBar() {
}

}
