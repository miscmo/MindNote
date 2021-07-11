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

using namespace MyNote;

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
    initMenuNotebook();

    initMenuEdit();

    initMenuImport();

    initMenuTools();

    initMenuView();

    initMenuAbout();
}

void NoteMenuBar::initMenuNotebook() {
    QMenu *menuFile = addMenu(tr("Notebook"));
    QAction *actionOpenDir = menuFile->addAction(tr("Open Notebook"));
    QAction *actionSaveFile = menuFile->addAction(tr("Save"));

    menuFile->addSeparator();

    QMenu *subMenuRecentlyFile = menuFile->addMenu(tr("Recently Access"));
    initRecentlyFileList(subMenuRecentlyFile);

    menuFile->addSeparator();

    QAction *actionExit = menuFile->addAction(tr("Exit"));

    connect(actionOpenDir, &QAction::triggered, this, &NoteMenuBar::openNotebook);
    connect(actionSaveFile, &QAction::triggered, this, &NoteMenuBar::saveNote);
    connect(actionExit, &QAction::triggered, this, &NoteMenuBar::exitApp);
}

void NoteMenuBar::openNotebook() {
    QString dir = QFileDialog::getExistingDirectory(
                this, tr("Open Notebook"),
                "",
                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks );

    NotebookManager::getInstance()->setCurNotebook(dir);
}

void NoteMenuBar::saveNote() {
    NotebookManager::getInstance()->saveCurrentNode();
}

void NoteMenuBar::exitApp() {
    MyNote::getInstance()->getMainWindow()->close();
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

void NoteMenuBar::initMenuEdit() {
    QMenu *menuEdit = addMenu(tr("Edit"));
    QAction *actionRename = menuEdit->addAction(tr("Rename"));
}

void NoteMenuBar::initMenuImport() {
    QMenu *menuImport = addMenu(tr("Import"));
    QAction *actionFromDir = menuImport->addAction(tr("From dir"));
}

void NoteMenuBar::initMenuView() {
    QMenu *menuImport = addMenu(tr("View"));
    QAction *actionFromDir = menuImport->addAction(tr("Options"));
}

void NoteMenuBar::initMenuTools() {
    QMenu *menuImport = addMenu(tr("Tools"));
    QAction *actionFromDir = menuImport->addAction(tr("More"));
}

void NoteMenuBar::initMenuAbout() {
    QMenu *menuAbout = addMenu(tr("About"));
    QAction *actionOpenDir = menuAbout->addAction(tr("Help"));
}

NoteMenuBar::~NoteMenuBar() {
}
