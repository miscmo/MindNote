#include "WidgetFactory.h"

#include "NodeItem.h"

#include <QFormLayout>
#include <QTreeWidget>
#include <QTreeWidgetItem>

using namespace MyNote;

QFormLayout *WidgetFactory::createFormLayout(QWidget *parent) {
    QFormLayout *layout = new QFormLayout(parent);

    return layout;
}

NodeItem *WidgetFactory::CreateNodeItem(QTreeWidget *parent) {
    NodeItem *item = new NodeItem(parent);

    Qt::ItemFlags flags = Qt::ItemIsEnabled;
    flags = flags | Qt::ItemIsSelectable;

    item->setFlags(flags);

    return item;
}

NodeItem *WidgetFactory::CreateNodeItem(QTreeWidgetItem *parent) {
    NodeItem *item = new NodeItem(parent);

    Qt::ItemFlags flags = Qt::ItemIsEnabled;
    flags = flags | Qt::ItemIsSelectable;
    //flags = flags | Qt::ItemIsEditable;

    item->setFlags(flags);

    return item;
}

