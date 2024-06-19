#include "NoteExplorer.h"

#include "NoteEditor.h"
#include "MainWindow.h"
#include "NodeItem.h"

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
        m_pInstance = new NoteExplorer(MyNote::getInstance()->GetMainWindow());
        m_pInstance->setRootIsDecorated(true);
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

void NoteExplorer::openNote(Note *note) {
    //Note *note = NoteMgr::GetInstance()->GetCurNote();

    Q_ASSERT(note != nullptr);

    QIcon itemIcon(":/Res/document.svg");
    QIcon rootIcon(":/Res/notebook_icon.svg");

    Node *rootNode = note->GetRootNode();

    NodeItem *rootItem = WidgetFactory::CreateNodeItem(this);
    rootItem->setData(0, Qt::UserRole, QVariant().fromValue(rootNode));
    rootItem->setText(0, rootNode->getTitle());
    //rootItem->setText(1, rootNode->getName());
    rootItem->ConnNodeIsMod(rootNode);
    rootItem->setIcon(0, rootIcon);

    loadNode(rootItem, rootNode);

    rootItem->setExpanded(true);
    setRootIsDecorated(false);
    //setIndentation(20);   设置缩进距离

}

void NoteExplorer::closeNote(Note *note) {

}

void NoteExplorer::delNote(Note *note) {

}


NoteExplorer::~NoteExplorer() {
    qDebug() << "~NoteExplorer" << Qt::endl;
}

void NoteExplorer::initUi() {
    setColumnCount(1);
    setHeaderHidden(true);
    setEditTriggers(QAbstractItemView::SelectedClicked | QAbstractItemView::DoubleClicked);
}

void NoteExplorer::setupSignal() {
    connect(this, &QTreeWidget::itemClicked,
            this, &NoteExplorer::onItemClicked);
    connect(this, &QTreeWidget::currentItemChanged,
            this, &NoteExplorer::onCurrentItemChanged);
    connect(this, &QTreeWidget::customContextMenuRequested,
            this, &NoteExplorer::onPopMenuRequest);

    // itemChanged 当树形控件中的某个项目的内容（如文本、复选框状态等）发生变化时触发。它通常在用户编辑项目内容后调用
    connect(this, &NoteExplorer::itemChanged,
            NoteMgr::GetInstance(), &NoteMgr::OnItemChanged);

    connect(NoteMgr::GetInstance(), &NoteMgr::signalOpenNote,
            this, &NoteExplorer::openNote);
    connect(NoteMgr::GetInstance(), &NoteMgr::signalCloseNote,
            this, &NoteExplorer::closeNote);
    connect(NoteMgr::GetInstance(), &NoteMgr::signalDelNote,
            this, &NoteExplorer::delNote);
}


// todo:考虑整合onAddSub,onAddPre,onAddPost这三个函数，都是重复代码
void NoteExplorer::onAddSub() {
    QTreeWidgetItem* curItem = currentItem();
    if (!curItem)
        return ;

    QIcon itemIcon(":/Res/document.svg");

    Node *curNode = curItem->data(0, Qt::UserRole).value<Node *>();

    NewNoteDialog dig(curNode, -1, this);
    if (dig.exec() == QDialog::Accepted) {
        NodeItem *newItem = WidgetFactory::CreateNodeItem(curItem);
        newItem->setData(0, Qt::UserRole, QVariant().fromValue(dig.getNewNode()));
        newItem->setText(0, dig.getNewNode()->getTitle());
        newItem->ConnNodeIsMod(dig.getNewNode());
        newItem->setIcon(0, itemIcon);

        setCurrentItem(newItem);

        emit itemClicked(newItem, 0);
    }
}

void NoteExplorer::onAddPre() {
    QTreeWidgetItem* curItem = currentItem();
    if (!curItem)
        return ;

    QIcon itemIcon(":/Res/document.svg");

    int preIndex = curItem->parent()->indexOfChild(curItem);
    Node *parentNode = curItem->parent()->data(0, Qt::UserRole).value<Node *>();

    NewNoteDialog dig(parentNode, preIndex, this);
    if (dig.exec() == QDialog::Accepted) {
        NodeItem *newItem = WidgetFactory::CreateNodeItem((QTreeWidget *)nullptr);
        newItem->setData(0, Qt::UserRole, QVariant().fromValue(dig.getNewNode()));
        newItem->setText(0, dig.getNewNode()->getTitle());
        newItem->ConnNodeIsMod(dig.getNewNode());
        newItem->setIcon(0, itemIcon);

        curItem->parent()->insertChild(preIndex, newItem);

        setCurrentItem(newItem);

        emit itemClicked(newItem, 0);
    }
}

void NoteExplorer::onAddPost() {
    QTreeWidgetItem* curItem = currentItem();
    if (!curItem)
        return ;

    QIcon itemIcon(":/Res/document.svg");

    int postIndex = curItem->parent()->indexOfChild(curItem) + 1;
    Node *parentNode = curItem->parent()->data(0, Qt::UserRole).value<Node *>();

    NewNoteDialog dig(parentNode, postIndex, this);
    if (dig.exec() == QDialog::Accepted) {
        NodeItem *newItem = WidgetFactory::CreateNodeItem((QTreeWidget *)nullptr);
        newItem->setData(0, Qt::UserRole, QVariant().fromValue(dig.getNewNode()));
        newItem->setText(0, dig.getNewNode()->getTitle());
        newItem->ConnNodeIsMod(dig.getNewNode());
        newItem->setIcon(0, itemIcon);

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

void NoteExplorer::onRename() {
    QTreeWidgetItem* curItem = currentItem();
    if (!curItem) {
        return ;
    }

    editItem(curItem);
}

void NoteExplorer::onItemClicked(QTreeWidgetItem *p_item, int column) {
}

void NoteExplorer::onCurrentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous) {
    // 先保存原来的
    if (previous != nullptr) {
        Node *preNode = previous->data(0, Qt::UserRole).value<Node *>();
        if (preNode->NeedSave()) {
            preNode->Save();
        }
    }

    // 再切换到新的结点
    Node *itemNode = current->data(0, Qt::UserRole).value<Node *>();

    NoteMgr::GetInstance()->SetCurNode(itemNode);
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

    QIcon itemIcon(":/Res/document.svg");

    for (auto subNode : subNodeList) {
        NodeItem *item = WidgetFactory::CreateNodeItem(parent_item);
        item->setData(0, Qt::UserRole, QVariant().fromValue(subNode));
        item->setText(0, subNode->getTitle());
        item->setIcon(0, itemIcon);
        item->ConnNodeIsMod(subNode);

        loadNode(item, subNode);
    }
}
