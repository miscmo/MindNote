#include "WidgetFactory.h"

#include <QFormLayout>
#include <QTreeWidget>
#include <QTreeWidgetItem>

using namespace MyNote;

QFormLayout *WidgetFactory::createFormLayout(QWidget *parent) {
    QFormLayout *layout = new QFormLayout(parent);

    return layout;
}

QTreeWidgetItem *WidgetFactory::createNoteExplorerItem(QTreeWidget *parent) {
    QTreeWidgetItem *item = new QTreeWidgetItem(parent);

    Qt::ItemFlags flags = Qt::ItemIsEnabled;
    flags = flags | Qt::ItemIsSelectable;

    item->setFlags(flags);

    return item;
}

QTreeWidgetItem *WidgetFactory::createNoteExplorerItem(QTreeWidgetItem *parent) {
    QTreeWidgetItem *item = new QTreeWidgetItem(parent);

    Qt::ItemFlags flags = Qt::ItemIsEnabled;
    flags = flags | Qt::ItemIsSelectable;
    //flags = flags | Qt::ItemIsEditable;

    item->setFlags(flags);

    return item;
}

