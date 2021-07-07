#include "NoteExplorerItem.h"

#include <QTreeWidget>
#include <QTreeWidgetItem>

namespace MyNote {

NoteExplorerItem::NoteExplorerItem(QTreeWidget *parent)
    :QTreeWidgetItem(parent) {
    init();
}

NoteExplorerItem::NoteExplorerItem(QTreeWidgetItem *parent)
    :QTreeWidgetItem(parent) {
    init();
}

void NoteExplorerItem::init() {
    initUi();
}

NoteExplorerItem::~NoteExplorerItem() {

}

void NoteExplorerItem::setNode(Node *node) {
    Q_ASSERT(node);

    m_pNode = node;
}

void NoteExplorerItem::initUi() {
    setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
}

}
