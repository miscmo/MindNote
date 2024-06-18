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

    QAction *iconItem = addAction(tr("editIcon"));

    addSeparator();

    QAction *delItem = addAction(tr("delete"));


    connect(addSub, &QAction::triggered, NoteExplorer::getInstance(), &NoteExplorer::onAddSub);
    connect(addPre, &QAction::triggered, NoteExplorer::getInstance(), &NoteExplorer::onAddPre);
    connect(addPost, &QAction::triggered, NoteExplorer::getInstance(), &NoteExplorer::onAddPost);
    connect(delItem, &QAction::triggered, WidgetMgr::GetInstance(), &WidgetMgr::TodoDialog);
    connect(renameItem, &QAction::triggered, NoteExplorer::getInstance(), &NoteExplorer::onRename);
    connect(iconItem, &QAction::triggered, WidgetMgr::GetInstance(), &WidgetMgr::TodoDialog);
}

void NoteExplorerPopMenu::initSignal() {
}

}
