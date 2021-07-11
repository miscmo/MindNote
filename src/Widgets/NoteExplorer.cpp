#include "NoteExplorer.h"

#include "NoteEditor.h"
#include "MainWindow.h"

#include <MyNote.h>
#include <Notebook/Notebook.h>
#include <Notebook/NotebookManager.h>
#include <Notebook/BufferManager.h>
#include <Notebook/Node.h>
#include <Widgets/NoteExplorerPopMenu.h>
#include <Widgets/NoteExplorerItem.h>
#include <Widgets/Dialogs/NewNodeDialog.h>

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
    NoteExplorerItem *rootItem = new NoteExplorerItem(this);
    rootItem->setData(0, Qt::UserRole, QVariant().fromValue(rootNode));
    rootItem->setText(0, rootNode->getName());

    for (auto node : rootNode->getChilds()) {
        NoteExplorerItem *item = new NoteExplorerItem(rootItem);
        item->setNode(node);
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
    qDebug() << "~NoteExplorer" << endl;
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
    NoteExplorerItem* curItem = dynamic_cast<NoteExplorerItem *>(currentItem());
    if (!curItem)
        return ;

    Node *curNode = curItem->data(0, Qt::UserRole).value<Node *>();

    NewNoteDialog dig(curNode, -1, this);
    if (dig.exec() == QDialog::Accepted) {
        NoteExplorerItem *newItem = new NoteExplorerItem(curItem);
        newItem->setData(0, Qt::UserRole, QVariant().fromValue(dig.getNewNode()));
        newItem->setText(0, dig.getNewNode()->getName());

        setCurrentItem(newItem);

        emit itemClicked(newItem, 0);
    }
}

void NoteExplorer::onAddPre() {
    NoteExplorerItem* curItem = dynamic_cast<NoteExplorerItem *>(currentItem());
    if (!curItem)
        return ;

    int preIndex = curItem->parent()->indexOfChild(curItem);
    Node *parentNode = curItem->parent()->data(0, Qt::UserRole).value<Node *>();

    NewNoteDialog dig(parentNode, preIndex, this);
    if (dig.exec() == QDialog::Accepted) {
        NoteExplorerItem *newItem = new NoteExplorerItem();
        newItem->setData(0, Qt::UserRole, QVariant().fromValue(dig.getNewNode()));
        newItem->setText(0, dig.getNewNode()->getName());

        curItem->parent()->insertChild(preIndex, newItem);

        setCurrentItem(newItem);

        emit itemClicked(newItem, 0);
    }
}

void NoteExplorer::onAddPost() {
    NoteExplorerItem* curItem = dynamic_cast<NoteExplorerItem *>(currentItem());
    if (!curItem)
        return ;

    int postIndex = curItem->parent()->indexOfChild(curItem) + 1;
    Node *parentNode = curItem->parent()->data(0, Qt::UserRole).value<Node *>();

    NewNoteDialog dig(parentNode, postIndex, this);
    if (dig.exec() == QDialog::Accepted) {
        NoteExplorerItem *newItem = new NoteExplorerItem();
        newItem->setData(0, Qt::UserRole, QVariant().fromValue(dig.getNewNode()));
        newItem->setText(0, dig.getNewNode()->getName());

        curItem->parent()->insertChild(postIndex, newItem);

        setCurrentItem(newItem);

        emit itemClicked(newItem, 0);
    }
}

void NoteExplorer::onDelete() {
    NoteExplorerItem* curItem = dynamic_cast<NoteExplorerItem *>(currentItem());
    if (!curItem)
        return ;

    QString itemName = curItem->text(0);

    int index = indexOfTopLevelItem(curItem);
    if (-1 == index) {
        NoteExplorerItem *parentItem = dynamic_cast<NoteExplorerItem *>(curItem->parent());
        int childIdx = parentItem->indexOfChild(curItem);
        parentItem->takeChild(childIdx);
        return ;
    }

    takeTopLevelItem(index);
}

void NoteExplorer::onItemClicked(QTreeWidgetItem *p_item, int column) {
    Node *itemNode = p_item->data(0, Qt::UserRole).value<Node *>();

    NotebookManager::getInstance()->setCurrentNode(itemNode);
}

void NoteExplorer::onPopMenuRequest(const QPoint &point) {
    NoteExplorerItem* curItem = dynamic_cast<NoteExplorerItem *>(currentItem());
    if (!curItem)
        return ;

    NoteExplorerPopMenu popMenu(this);
    popMenu.exec(QCursor::pos());
}

void NoteExplorer::loadNode(NoteExplorerItem *parent_item, Node *node) {
    auto subNodeList = node->getChilds();

    if (subNodeList.isEmpty())
        return ;

    for (auto subNode : subNodeList) {
        NoteExplorerItem *item = new NoteExplorerItem(parent_item);
        item->setNode(subNode);
        item->setData(0, Qt::UserRole, QVariant().fromValue(subNode));
        item->setText(0, subNode->getName());
        loadNode(item, subNode);
    }
}
