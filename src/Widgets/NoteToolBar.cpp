#include "NoteToolBar.h"

#include <MyNote.h>
#include <Widgets/MainWindow.h>
#include <Widgets/NoteEditor.h>
#include <Notebook/NotebookManager.h>
#include <Config/AppState.h>
#include <Widgets/WidgetMgr.h>

#include <QFontDialog>
#include <QToolButton>
#include <QMenu>

using namespace MyNote;

NoteToolBar *NoteToolBar::m_pInstance = nullptr;

NoteToolBar *NoteToolBar::getInstance() {
    if (!m_pInstance) {
        m_pInstance = new NoteToolBar(MyNote::getInstance()->GetMainWindow());
    }

    return m_pInstance;
}

NoteToolBar::NoteToolBar(QWidget *parent)
    : QToolBar(parent) {
    initUi();
}

NoteToolBar::~NoteToolBar() {
}

void NoteToolBar::initUi() {
    setAllowedAreas(Qt::TopToolBarArea);
    setFloatable(false);
    setMovable(false);
    setIconSize(QSize(15, 15));
    setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    //setFixedHeight(20);

    initNotebookManage();
}

void NoteToolBar::initNotebookManage() {
    const QString strFromDisk = "From Disk";

    QIcon openIcon(":/Res/addNewNotebook.svg");
    QIcon saveIcon(":/Res/save.svg");
    QIcon fontSetIcon(":/Res/font_set.svg");
    QIcon noteIcon(":/Res/notebook_icon.svg");
    QIcon hddIcon(":/Res/hdd.svg");

    QToolButton *btnOpenNote = new QToolButton(this);
    QMenu *menuOpenNote = new QMenu();

    auto onOpenRecentlyFile = [=](const QAction *action) {
        QString path = action->text();

        if (path == strFromDisk) {
            qDebug() << "todo: open from disk" << Qt::endl;
            return ;
        }

        qDebug() << "open recently note, path: " << path << "\n";

        // 错误处理，如果是一个错误的path，要弹窗告警出来
        NoteMgr::GetInstance()->openNote(path);
    };

    QStringList fileList = AppState::getInstance()->getRecentlyDirList();

    for (auto file : fileList) {
        menuOpenNote->addAction(noteIcon, file);
    }

    menuOpenNote->addSeparator();

    menuOpenNote->addAction(hddIcon, tr("From Disk"));


    connect(menuOpenNote, &QMenu::triggered, onOpenRecentlyFile);

    btnOpenNote->setMenu(menuOpenNote);

    btnOpenNote->setPopupMode(QToolButton::MenuButtonPopup);
    btnOpenNote->setText(tr("Open Note"));
    //btnOpenNote->setIcon(openIcon);
    btnOpenNote->setLayoutDirection(Qt::LeftToRight);

    addWidget(btnOpenNote);

    addSeparator();

    auto onSave = [=]() {
        NoteMgr::GetInstance()->SaveCurNode();
    };

    QAction *actionSave = new QAction(saveIcon, tr("Save"), this);
    actionSave->setToolTip(tr("save note"));

    addAction(actionSave);
    connect(actionSave, &QAction::triggered, onSave);

    addSeparator();

    QAction *actionFont = new QAction(fontSetIcon, tr("Font"), this);
    actionFont->setToolTip(tr("set font"));

    addAction(actionFont);

    auto fontSelecter = [=]() {
        bool ok;
        QFont curFont = NoteEditor::getInstance()->getCurFont();
        QFont font = QFontDialog::getFont(&ok, curFont, this, tr("Choose Font"));
        if (ok) {
            NoteEditor::getInstance()->setCurFont(font);
        }
    };

    connect(actionFont, &QAction::triggered, fontSelecter);
}
