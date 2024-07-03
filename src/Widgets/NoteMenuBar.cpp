#include "NoteMenuBar.h"

#include "MainWindow.h"

#include <MyNote.h>
#include <Config/Config.h>
#include <Config/AppState.h>
#include <Notebook/NotebookManager.h>
#include <Notebook/BufferManager.h>
#include <Widgets/NoteEditor.h>
#include <Model/DBMgr.h>
#include <Widgets/WidgetMgr.h>
#include <Widgets/Dialogs/NoteInfoDialog.h>
#include <Widgets/NoteToolBar.h>

#include <QAction>
#include <QMenu>
#include <QFileDialog>
#include <QDebug>
#include <QFontDialog>
#include <QMessageBox>

using namespace MyNote;

NoteMenuBar *NoteMenuBar::m_pInstance = nullptr;

NoteMenuBar *NoteMenuBar::getInstance() {
    if (!m_pInstance)
        m_pInstance = new NoteMenuBar(MyNote::getInstance()->GetMainWindow());
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

    initMenuSetting();

    initMenuAbout();
}

void NoteMenuBar::initMenuNotebook() {
    QMenu *menuFile = addMenu(tr("Notebook"));

    QAction *actionNewNotebook = menuFile->addAction(tr("New Notebook"));
    QAction *actionOpenDir = menuFile->addAction(tr("Open Notebook"));
    QAction *actionSaveFile = menuFile->addAction(tr("Save"));

    menuFile->addSeparator();

    QMenu *subMenuRecentlyFile = menuFile->addMenu(tr("Recently Access"));
    initRecentlyFileList(subMenuRecentlyFile);

    menuFile->addSeparator();

    QAction *actionExit = menuFile->addAction(tr("Exit"));

    connect(actionNewNotebook, &QAction::triggered, this, &NoteMenuBar::newNotebook);
    connect(actionOpenDir, &QAction::triggered, this, &NoteMenuBar::openNotebook);
    connect(actionSaveFile, &QAction::triggered, this, &NoteMenuBar::saveNote);
    connect(actionExit, &QAction::triggered, this, &NoteMenuBar::exitApp);
}

void NoteMenuBar::newNotebook() {

    NoteInfoDialog dig(this);
    if (dig.exec() == QDialog::Accepted) {
        qDebug() << "create new note succ" << "\n";
    } else {
        qDebug() << "create new note failed" << "\n";
        return;
    }

    // todo 将新笔记添加到侧边栏
}

void NoteMenuBar::openNotebook() {
    QString dir = QFileDialog::getExistingDirectory(
                this, tr("Open Notebook"),
                "",
                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks );

    qDebug() << "open note path: " << dir << "\n";

    Error err = NoteMgr::GetInstance()->openNote(dir);
    if (!err.isSuccess()) {
        // todo 不应该是这个this，应该是主窗口，暂时先写这个
        //QMessageBox::warning(this, tr("open error"), err.message);
        //qWarning() << "open note failed, errcode: " << int(err.code) << ", msg: " << err.message << Qt::endl;
        qDebug() << "open note failed" << Qt::endl;
    }
}

void NoteMenuBar::saveNote() {
    NoteMgr::GetInstance()->SaveCurNode();
}

void NoteMenuBar::exitApp() {
    MyNote::getInstance()->GetMainWindow()->close();
}

void NoteMenuBar::initRecentlyFileList(QMenu *menuRecentlyFile) {
    Q_ASSERT(menuRecentlyFile);

    auto onOpenRecentlyFile = [=](const QAction *action) {
        QString path = action->text();

        qDebug() << "open recently note, path: " << path << "\n";

        NoteMgr::GetInstance()->openNote(path);
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

    QAction *actionToolBar = menuImport->addAction(tr("ToolBar"));
    actionToolBar->setCheckable(true);
    actionToolBar->setChecked(NoteToolBar::getInstance()->isVisible());

    connect(actionToolBar, &QAction::toggled, NoteToolBar::getInstance(), &QToolBar::setVisible);
}

void NoteMenuBar::initMenuTools() {
    QMenu *menuImport = addMenu(tr("Tools"));
    QAction *actionNoteFrameExchange = menuImport->addAction(tr("Notebook Frame Exchange"));
    addSeparator();
    QAction *actionMore = menuImport->addAction(tr("More"));
}

void NoteMenuBar::initMenuSetting() {
    // todo 这里做一个通用的字体管理控件，可以分别设置中文和英文字体
    auto fontSelecter = [=]() {
        bool ok;
        QFont curFont = NoteEditor::getInstance()->getCurFont();
        QFont font = QFontDialog::getFont(&ok, curFont, this, tr("Choose Font"));
        if (ok) {
            NoteEditor::getInstance()->setCurFont(font);
        }
    };

    auto SettingMore = [=]() {
        Setting curSet = DBMgr::GetInstance()->GetCurSetting();
        qDebug() << curSet.Name << Qt::endl;
    };

    QMenu *menuSetting = addMenu(tr("Setting"));

    QAction *actionFont = menuSetting->addAction(tr("Font"));

    menuSetting->addSeparator();

    QAction *actionShortcut = menuSetting->addAction(tr("Shortcut"));

    menuSetting->addSeparator();

    QMenu *menuTheme = menuSetting->addMenu(tr("Theme"));
    menuTheme->addAction(":/Res/default.style");
    menuTheme->addAction(":/Res/solarized-dark.style");
    menuTheme->addAction(":/Res/solarized-dark-subtle.style");
    menuTheme->addAction(":/Res/solarized-light.style");
    menuTheme->addAction(":/Res/solarized-light-subtle.style");

    auto onReloadTheme = [=](const QAction *action) {
        QString path = action->text();

        qDebug() << "open recently note, path: " << path << "\n";

        NoteEditor::getInstance()->loadStyleFromStylesheet(path);
    };



    QAction *actionMore = menuSetting->addAction(tr("More"));

    connect(actionFont, &QAction::triggered, fontSelecter);
    connect(actionMore, &QAction::triggered, SettingMore);
    connect(actionShortcut, &QAction::triggered, WidgetMgr::GetInstance(), &WidgetMgr::TodoDialog);
    connect(menuTheme, &QMenu::triggered, onReloadTheme);
}

void NoteMenuBar::initMenuAbout() {
    QMenu *menuAbout = addMenu(tr("About"));

    QAction *actionHelp = menuAbout->addAction(tr("Help"));
}

NoteMenuBar::~NoteMenuBar() {
}
