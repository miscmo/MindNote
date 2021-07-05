#include "NoteExplorerPopMenu.h"

#include <Widgets/NoteExplorer.h>

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

    QAction *delItem = addAction(tr("delete"));

    connect(addSub, &QAction::triggered, NoteExplorer::getInstance(), &NoteExplorer::onAddSub);
    connect(addPre, &QAction::triggered, NoteExplorer::getInstance(), &NoteExplorer::onAddPre);
    connect(addPost, &QAction::triggered, NoteExplorer::getInstance(), &NoteExplorer::onAddPost);
    connect(delItem, &QAction::triggered, NoteExplorer::getInstance(), &NoteExplorer::onDelete);
}

void NoteExplorerPopMenu::initSignal() {
}

}
