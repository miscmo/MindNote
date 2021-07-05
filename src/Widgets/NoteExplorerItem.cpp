#include "NoteExplorerItem.h"

#include <QTreeWidget>
#include <QTreeWidgetItem>

namespace MyNote {

NoteExplorerItem::NoteExplorerItem(QTreeWidget *parent)
    :QTreeWidgetItem(parent) {
}

NoteExplorerItem::NoteExplorerItem(QTreeWidgetItem *parent)
    :QTreeWidgetItem(parent) {
}

NoteExplorerItem::~NoteExplorerItem() {

}

void NoteExplorerItem::initUi() {
    setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
}

}
