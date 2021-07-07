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

namespace MyNote {

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

    for (auto node : rootNode->getChilds()) {
        NoteExplorerItem *item = new NoteExplorerItem(this);
        item->setNode(node);
        item->setText(0, node->getName());
        if (!node->getChilds().isEmpty()) {
            loadNode(item, node);
        }
        items.append(item);
    }

    insertTopLevelItems(0, items);
}

NoteExplorer::~NoteExplorer() {
    qDebug() << "~NoteExplorer" << endl;
}

void NoteExplorer::initUi() {
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

    QString itemName = curItem->text(0);

    NewNoteDialog dig(this);
    dig.exec();

//    NoteExplorerItem *newItem = new NoteExplorerItem(curItem);
    //newItem->setText(0, "");

    //setCurrentItem(newItem);
    //editItem(currentItem());
}

void NoteExplorer::onAddPre() {
    NoteExplorerItem* curItem = dynamic_cast<NoteExplorerItem *>(currentItem());
    if (!curItem)
        return ;

    QString itemName = curItem->text(0);

    NoteExplorerItem *newItem = new NoteExplorerItem(curItem->parent());
    newItem->setText(0, "new");

    insertTopLevelItem(indexOfTopLevelItem(curItem), newItem);
}

void NoteExplorer::onAddPost() {
    NoteExplorerItem* curItem = dynamic_cast<NoteExplorerItem *>(currentItem());
    if (!curItem)
        return ;

    QString itemName = curItem->text(0);

    NoteExplorerItem *newItem = new NoteExplorerItem(curItem->parent());
    newItem->setText(0, "new");

    insertTopLevelItem(indexOfTopLevelItem(curItem)+1, newItem);
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
    QString itemText = p_item->text(0);

    BufferManager *manager = BufferManager::getInstance();
    manager->setCurrentBuffer(itemText);
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
        item->setText(0, subNode->getName());
        loadNode(item, subNode);
    }
}

}
