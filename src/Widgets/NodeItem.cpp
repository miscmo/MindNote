#include "NodeItem.h"

#include "Notebook/Node.h"

#include <QTreeWidgetItem>
#include <QTreeWidget>

using namespace  MyNote;

NodeItem::NodeItem(QTreeWidgetItem *parent)
    : QTreeWidgetItem(parent) {
}

NodeItem::NodeItem(QTreeWidget *parent)
    : QTreeWidgetItem(parent) {
}

NodeItem::~NodeItem() {
    qDebug() << "~NodeItem" << Qt::endl;
}

void NodeItem::ConnNodeIsMod(Node *node) {
    connect(node, &Node::SignalModStatusChanged, this, &NodeItem::HandleNodeIsMod);
}

void NodeItem::HandleNodeIsMod(Node *node) {
    qDebug() << "trigger node mod changed, isMod: " << node->NeedSave() << Qt::endl;

    if (node->NeedSave()) {
        setForeground(0, QBrush(QColor(255,0,0)));
    } else {
        setForeground(0, QBrush(QColor(0,0,0)));
    }
}
