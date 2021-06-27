#include "MainWindow.h"

#include <config.h>
#include <noteexplorer.h>
#include <Notebook.h>
#include <FileExplorer.h>
#include <noteeditor.h>
#include <ViewArea.h>
#include <NotebookManager.h>

#include <QRect>
#include <QVariant>
#include <QDockWidget>
#include <QMenuBar>
#include <QFileDialog>

#define WIN_GEOMETRY_KEY "window_geometry"
#define WIN_STATE_KEY "window_state"
#define TEST_NOTE_PATH "D:\\Temp"

namespace gnote {


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
}

void MainWindow::init() {
    initUi();

    loadStateAndGeometry();
}

MainWindow *MainWindow::getInstance() {
    static MainWindow window;
    return &window;
}

void MainWindow::initUi() {
    //菜单栏
    initMenuBar();

    //设置中心窗口
    m_pViewArea = ViewArea::getInstance();

    setCentralWidget(m_pViewArea);

    m_pNoteExplorer = NoteExplorer::getInstance();

    m_pNoteExplorer->registerEditor(NoteEditor::getInstance());
    m_pNoteExplorer->setupSignal();

    m_pFileExplorer = FileExplorer::getInstance();

    //设置Dock
    setTabPosition(Qt::LeftDockWidgetArea, QTabWidget::West);
    setTabPosition(Qt::RightDockWidgetArea, QTabWidget::East);
    setTabPosition(Qt::TopDockWidgetArea, QTabWidget::North);
    setTabPosition(Qt::BottomDockWidgetArea, QTabWidget::North);

    setDockNestingEnabled(true);

    //设置笔记目录Dock
    QDockWidget *notebookDock = new QDockWidget("Notebook", this);
    m_docks.push_back(notebookDock);

    notebookDock->setWidget(m_pNoteExplorer);
    notebookDock->setFocusProxy(m_pNoteExplorer);

    addDockWidget(Qt::LeftDockWidgetArea, notebookDock);

    //设置文件系统Dock
    QDockWidget *fileDock = new QDockWidget("File", this);
    m_docks.push_back(fileDock);

    fileDock->setWidget(m_pFileExplorer);

    addDockWidget(Qt::LeftDockWidgetArea, fileDock);

    for (int i = 1; i < m_docks.size(); ++i) {
        tabifyDockWidget(m_docks[i-1], m_docks[i]);
    }
}

void MainWindow::initMenuBar() {
    QMenuBar * menuBar = this->menuBar();

    auto openDir = [=]() {
        QString dir = QFileDialog::getExistingDirectory(
                    this, tr("Open Directory"),
                    "",
                    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks );

        NotebookManager::getInstance()->resetNote(dir);
    };

    QMenu *menuFile = menuBar->addMenu("File");
    QAction *actionOpenDir = menuFile->addAction("Open");
    QAction *actionSaveFile = menuFile->addAction("Save");
    QAction *actionExit = menuFile->addAction("Exit");

    connect(actionOpenDir, &QAction::triggered, openDir);

}

void MainWindow::loadStateAndGeometry() {
    Config *config = Config::Instance();

    auto winGeometry  = config->get(WIN_GEOMETRY_KEY).toByteArray();
    auto winState = config->get(WIN_STATE_KEY).toByteArray();

    if (!winGeometry.isEmpty())
        restoreGeometry(winGeometry);

    if (!winState.isEmpty())
        restoreState(winState);
}

void MainWindow::saveStateAndGeometry() {
    Config *config = Config::Instance();

    config->set(WIN_GEOMETRY_KEY, saveGeometry());
    config->set(WIN_STATE_KEY, saveState());
}

MainWindow::~MainWindow() {
    delete m_pViewArea;
}

void MainWindow::closeEvent(QCloseEvent *p_event) {
    saveStateAndGeometry();
}

}

