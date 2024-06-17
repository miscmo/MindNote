#include "MainWindow.h"

#include "FileExplorer.h"
#include "NoteExplorer.h"
#include "NoteEditor.h"
#include "ViewArea.h"
#include "NoteMenuBar.h"

#include <MyNote.h>
#include <Config/Config.h>
#include <Notebook/Notebook.h>
#include <Notebook/NotebookManager.h>
#include <Notebook/BufferManager.h>
#include <Widgets/NoteToolBar.h>
#include <Widgets/NoteStatusBar.h>
#include <Model/DBMgr.h>

#include <QRect>
#include <QVariant>
#include <QDockWidget>
#include <QMenuBar>
#include <QFileDialog>
#include <QDebug>

#define TEST_NOTE_PATH "D:\\Temp"

namespace MyNote {

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    MyNote::getInstance()->SetMainWindow(this);
    loadStateAndGeometry();
}

void MainWindow::init() {
    initUi();
}

void MainWindow::initUi() {

    initToolBar();

    initMenuBar();

    initCentralWindow();

    initDock();

    initStatusBar();
}

void MainWindow::initToolBar() {
    QToolBar *mainToolBar = NoteToolBar::getInstance();

    addToolBar(Qt::TopToolBarArea, mainToolBar);
}

void MainWindow::initMenuBar() {
    QMenuBar * mainMenuBar = NoteMenuBar::getInstance();

    setMenuBar(mainMenuBar);
}

void MainWindow::initStatusBar() {
    QStatusBar *mainStatusBar = NoteStatusBar::getInstance();

    setStatusBar(mainStatusBar);
}

void MainWindow::initCentralWindow() {
    //设置中心窗口
    m_pViewArea = ViewArea::getInstance();

    setCentralWidget(m_pViewArea);

    m_pNoteExplorer = NoteExplorer::getInstance();
    m_pFileExplorer = FileExplorer::getInstance();
}

void MainWindow::initDock() {
    //设置Dock
    setTabPosition(Qt::LeftDockWidgetArea, QTabWidget::West);
    setTabPosition(Qt::RightDockWidgetArea, QTabWidget::East);
    setTabPosition(Qt::TopDockWidgetArea, QTabWidget::North);
    setTabPosition(Qt::BottomDockWidgetArea, QTabWidget::North);

    setDockNestingEnabled(true);

    //设置笔记目录Dock
    m_pNotebookDock = new QDockWidget("Notebook", this);
    m_pNotebookDock->setWidget(m_pNoteExplorer);
    m_pNotebookDock->setFocusProxy(m_pNoteExplorer);

    addDockWidget(Qt::LeftDockWidgetArea, m_pNotebookDock);

    //设置文件系统Dock
    m_pFileDock = new QDockWidget("File", this);
    m_pFileDock->setWidget(m_pFileExplorer);
    addDockWidget(Qt::LeftDockWidgetArea, m_pFileDock);

    tabifyDockWidget(m_pNotebookDock, m_pFileDock);

    //开始时显示notebook tab页
    m_pNotebookDock->raise();
}

void MainWindow::loadStateAndGeometry() {
    Config *config = Config::getInstance();

    auto winGeometry  = config->get(CONF_WIN_GEOMETRY_KEY).toByteArray();
    auto winState = config->get(CONF_WIN_STATE_KEY).toByteArray();

    if (!winGeometry.isEmpty())
        restoreGeometry(winGeometry);

    if (!winState.isEmpty())
        restoreState(winState);
}

void MainWindow::saveStateAndGeometry() {
    Config *config = Config::getInstance();

    config->set(CONF_WIN_GEOMETRY_KEY, saveGeometry());
    config->set(CONF_WIN_STATE_KEY, saveState());

    NoteMgr::GetInstance()->SaveCurNode();
    DBMgr::GetInstance()->Close();
}

MainWindow::~MainWindow() {
    qDebug() << "~MainWindow" << Qt::endl;
}

void MainWindow::closeEvent(QCloseEvent *p_event) {
    saveStateAndGeometry();
}

}

