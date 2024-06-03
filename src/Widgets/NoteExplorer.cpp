#include "NoteExplorer.h"

#include "NoteEditor.h"
#include "MainWindow.h"

#include <MyNote.h>
#include <Notebook/Notebook.h>
#include <Notebook/NotebookManager.h>
#include <Notebook/BufferManager.h>
#include <Notebook/Node.h>
#include <Widgets/NoteExplorerPopMenu.h>
#include <Widgets/WidgetFactory.h>
#include <Widgets/Dialogs/NewNodeDialog.h>
#include <Widgets/Dialogs/NodeDeleteConfirmDialog.h>

#include <QDebug>

using namespace MyNote;

Q_DECLARE_METATYPE(Node *);

NoteExplorer* NoteExplorer::m_pInstance = nullptr;
NoteExplorer *NoteExplorer::getInstance() {
    if (m_pInstance == nullptr) {
        m_pInstance = new NoteExplorer(MyNote::getInstance()->getMainWindow());
    }

    return m_pInstance;
}

NoteExplorer::NoteExplorer(QWidget *p_parent)
    : QTreeWidget(p_parent) {
    setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);

    initUi();

    setupSignal();
}

void NoteExplorer::clearAllNote() {
    clear();
}

void NoteExplorer::resetNote() {
    QList<QTreeWidgetItem *> items;

    Notebook *note = NotebookManager::getInstance()->getCurNotebook();

    Q_ASSERT(note != nullptr);

    clearAllNote();

    Node *rootNode = note->getRootNode();
    QTreeWidgetItem *rootItem = WidgetFactory::createNoteExplorerItem(this);
    rootItem->setData(0, Qt::UserRole, QVariant().fromValue(rootNode));
    rootItem->setText(0, rootNode->getName());

    for (auto node : rootNode->getChilds()) {
        QTreeWidgetItem *item = WidgetFactory::createNoteExplorerItem(rootItem);
        item->setData(0, Qt::UserRole, QVariant().fromValue(node));
        item->setText(0, node->getName());
        if (!node->getChilds().isEmpty()) {
            loadNode(item, node);
        }
        items.append(item);
    }

    rootItem->setExpanded(true);
    setRootIsDecorated(false);
}

NoteExplorer::~NoteExplorer() {
    qDebug() << "~NoteExplorer" << Qt::endl;
}

void NoteExplorer::initUi() {
    setColumnCount(1);
    setHeaderHidden(true);
}

void NoteExplorer::setupSignal() {
    connect(this, &QTreeWidget::itemClicked, this, &NoteExplorer::onItemClicked);
    connect(NotebookManager::getInstance(), &NotebookManager::signalNotebookChanged,
            this, &NoteExplorer::resetNote);
    connect(this, &QTreeWidget::customContextMenuRequested, this, &NoteExplorer::onPopMenuRequest);
    connect(this, &NoteExplorer::itemChanged, NotebookManager::getInstance(), &NotebookManager::onItemChanged);
}

void NoteExplorer::onAddSub() {
    QTreeWidgetItem* curItem = currentItem();
    if (!curItem)
        return ;

    Node *curNode = curItem->data(0, Qt::UserRole).value<Node *>();

    NewNoteDialog dig(curNode, -1, this);
    if (dig.exec() == QDialog::Accepted) {
        QTreeWidgetItem *newItem = WidgetFactory::createNoteExplorerItem(curItem);
        newItem->setData(0, Qt::UserRole, QVariant().fromValue(dig.getNewNode()));
        newItem->setText(0, dig.getNewNode()->getName());

        setCurrentItem(newItem);

        emit itemClicked(newItem, 0);
    }
}

void NoteExplorer::onAddPre() {
    QTreeWidgetItem* curItem = currentItem();
    if (!curItem)
        return ;

    int preIndex = curItem->parent()->indexOfChild(curItem);
    Node *parentNode = curItem->parent()->data(0, Qt::UserRole).value<Node *>();

    NewNoteDialog dig(parentNode, preIndex, this);
    if (dig.exec() == QDialog::Accepted) {
        QTreeWidgetItem *newItem = WidgetFactory::createNoteExplorerItem((QTreeWidget *)nullptr);
        newItem->setData(0, Qt::UserRole, QVariant().fromValue(dig.getNewNode()));
        newItem->setText(0, dig.getNewNode()->getName());

        curItem->parent()->insertChild(preIndex, newItem);

        setCurrentItem(newItem);

        emit itemClicked(newItem, 0);
    }
}

void NoteExplorer::onAddPost() {
    QTreeWidgetItem* curItem = currentItem();
    if (!curItem)
        return ;

    int postIndex = curItem->parent()->indexOfChild(curItem) + 1;
    Node *parentNode = curItem->parent()->data(0, Qt::UserRole).value<Node *>();

    NewNoteDialog dig(parentNode, postIndex, this);
    if (dig.exec() == QDialog::Accepted) {
        QTreeWidgetItem *newItem = WidgetFactory::createNoteExplorerItem((QTreeWidget *)nullptr);
        newItem->setData(0, Qt::UserRole, QVariant().fromValue(dig.getNewNode()));
        newItem->setText(0, dig.getNewNode()->getName());

        curItem->parent()->insertChild(postIndex, newItem);

        setCurrentItem(newItem);

        emit itemClicked(newItem, 0);
    }
}

void NoteExplorer::onDelete() {
    QTreeWidgetItem* curItem = currentItem();
    if (!curItem)
        return ;

    Node *curNode = curItem->data(0, Qt::UserRole).value<Node *>();

    NodeDeleteConfirmDialog dig(curNode, this);
    if (dig.exec() == QDialog::Accepted) {
        QTreeWidgetItem *parentItem = curItem->parent();

        int childIndex = parentItem->indexOfChild(curItem);

        parentItem->takeChild(childIndex);
    }
}

void NoteExplorer::onItemClicked(QTreeWidgetItem *p_item, int column) {
    Node *itemNode = p_item->data(0, Qt::UserRole).value<Node *>();

    NotebookManager::getInstance()->setCurrentNode(itemNode);
}

void NoteExplorer::onPopMenuRequest(const QPoint &point) {
    QTreeWidgetItem* curItem = currentItem();
    if (!curItem)
        return ;

    NoteExplorerPopMenu popMenu(this);
    popMenu.exec(QCursor::pos());
}

void NoteExplorer::loadNode(QTreeWidgetItem *parent_item, Node *node) {
    auto subNodeList = node->getChilds();

    if (subNodeList.isEmpty())
        return ;

    for (auto subNode : subNodeList) {
        QTreeWidgetItem *item = WidgetFactory::createNoteExplorerItem(parent_item);
        item->setData(0, Qt::UserRole, QVariant().fromValue(subNode));
        item->setText(0, subNode->getName());

        loadNode(item, subNode);
    }
}
