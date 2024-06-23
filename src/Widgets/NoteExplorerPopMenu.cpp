#include "NoteExplorerPopMenu.h"

#include <Widgets/NoteExplorer.h>
#include <QMessageBox>
#include <Widgets/WidgetMgr.h>

namespace MyNote {

NoteExplorerPopMenu::NoteExplorerPopMenu(QWidget *parent)
    :QMenu(parent) {
    initUi();

    initSignal();
}

NoteExplorerPopMenu::~NoteExplorerPopMenu() {
}

void NoteExplorerPopMenu::initUi() {
    QAction *addSub = addAction(tr("addSub"));
    QAction *addPre = addAction(tr("addPre"));
    QAction *addPost = addAction(tr("addPost"));

    addSeparator();

    QAction *renameItem = addAction(tr("rename"));

    //QAction *iconItem = addAction(tr("editIcon"));
    QAction *moveItem = addAction(tr("move"));

    addSeparator();

    QAction *delItem = addAction(tr("delete"));


    connect(addSub, &QAction::triggered, NoteExplorer::getInstance(), &NoteExplorer::onAddSub);
    connect(addPre, &QAction::triggered, NoteExplorer::getInstance(), &NoteExplorer::onAddPre);
    connect(addPost, &QAction::triggered, NoteExplorer::getInstance(), &NoteExplorer::onAddPost);
    connect(renameItem, &QAction::triggered, NoteExplorer::getInstance(), &NoteExplorer::onRename);
    connect(moveItem, &QAction::triggered, WidgetMgr::GetInstance(), &WidgetMgr::TodoDialog);
    connect(delItem, &QAction::triggered, NoteExplorer::getInstance(), &NoteExplorer::onDelete);
}

void NoteExplorerPopMenu::initSignal() {
}

NoteExplorerTopLevelPopMenu::NoteExplorerTopLevelPopMenu(QWidget *parent)
    :QMenu(parent) {
    initUi();

    initSignal();
}

NoteExplorerTopLevelPopMenu::~NoteExplorerTopLevelPopMenu() {
}

void NoteExplorerTopLevelPopMenu::initUi() {
    QAction *addSub = addAction(tr("addSub"));
    //QAction *addPre = addAction(tr("addPre"));
    //QAction *addPost = addAction(tr("addPost"));

    addSeparator();

    QAction *renameItem = addAction(tr("rename note"));

    //QAction *iconItem = addAction(tr("editIcon"));
    //QAction *moveItem = addAction(tr("move"));

    addSeparator();

    QAction *delItem = addAction(tr("delete note"));


    QAction *trashItem = addAction(tr("trash info"));
    QAction *infoItem = addAction(tr("note info"));


    connect(addSub, &QAction::triggered, NoteExplorer::getInstance(), &NoteExplorer::onAddSub);
    //connect(renameItem, &QAction::triggered, NoteExplorer::getInstance(), &NoteExplorer::onRename);
    //connect(moveItem, &QAction::triggered, WidgetMgr::GetInstance(), &WidgetMgr::TodoDialog);
    connect(renameItem, &QAction::triggered, WidgetMgr::GetInstance(), &WidgetMgr::TodoDialog);
    connect(delItem, &QAction::triggered, WidgetMgr::GetInstance(), &WidgetMgr::TodoDialog);
    connect(trashItem, &QAction::triggered, WidgetMgr::GetInstance(), &WidgetMgr::TodoDialog);
    connect(infoItem, &QAction::triggered, WidgetMgr::GetInstance(), &WidgetMgr::TodoDialog);
}

void NoteExplorerTopLevelPopMenu::initSignal() {
}
}
