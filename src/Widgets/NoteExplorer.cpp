#include "NoteExplorer.h"

#include "NoteEditor.h"
#include "MainWindow.h"

#include <MyNote.h>
#include <Notebook/Notebook.h>
#include <Notebook/NotebookManager.h>
#include <Notebook/BufferManager.h>

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
    setHeaderLabel("notebook");

    initUi();

    setupSignal();
}

void NoteExplorer::resetNote(const Notebook &note) {
    QList<QTreeWidgetItem *> items;

    QSharedPointer<Node> rootNode = note.getRootNode();

    for (auto node : rootNode->getChilds()) {
        QTreeWidgetItem *item = new QTreeWidgetItem(this);
        item->setText(0, node->getName());
        if (!node->getChilds().isEmpty()) {
            loadNode(item, node);
        }
        items.append(item);
    }

    insertTopLevelItems(0,items);
}

NoteExplorer::~NoteExplorer() {
    qDebug() << "~NoteExplorer" << endl;
}

void NoteExplorer::initUi() {
}

void NoteExplorer::setupSignal() {
    connect(this, &QTreeWidget::itemClicked, this, &NoteExplorer::onItemClicked);
    connect(NotebookManager::getInstance(), &NotebookManager::signalNotebookChanged,
            this, &NoteExplorer::resetNote);
}

void NoteExplorer::onItemClicked(QTreeWidgetItem *p_item, int column) {
    QString itemText = p_item->text(0);

    BufferManager *manager = BufferManager::getInstance();
    manager->setCurrentBuffer(itemText);
}

void NoteExplorer::loadNode(QTreeWidgetItem *parent_item, QSharedPointer<Node> node) {
    auto subNodeList = node->getChilds();

    if (subNodeList.isEmpty())
        return ;

    for (auto subNode : subNodeList) {
        QTreeWidgetItem *item = new QTreeWidgetItem(parent_item);
        item->setText(0, subNode->getName());
        loadNode(item, subNode);
    }
}

}
