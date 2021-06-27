#include "noteexplorer.h"

#include <Notebook.h>
#include <noteeditor.h>
#include <mainwindow.h>
#include <NotebookManager.h>

namespace gnote {

NoteExplorer *NoteExplorer::getInstance() {
    static NoteExplorer noteExplorer(MainWindow::getInstance());
    return &noteExplorer;
}

NoteExplorer::NoteExplorer(QWidget *p_parent)
    : QTreeWidget(p_parent) {
    setHeaderLabel("notebook");

    initUi();

    //setupSignal();
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
}

void NoteExplorer::initUi() {
    //setGeometry(0, 0, this->width(), this->height());
    //setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void NoteExplorer::setupSignal() {
    //connect(m_noteExplorer, &QTreeWidget::itemClicked, this, &NoteExplorer::onItemClicked);
    connect(this, &QTreeWidget::itemClicked, m_pNoteEditor, &NoteEditor::handleItemClicked);
    connect(NotebookManager::getInstance(), &NotebookManager::signalNotebookChanged,
            this, &NoteExplorer::resetNote);
}

void NoteExplorer::onItemClicked(QTreeWidgetItem *p_item, int column) {
    QString itemText = p_item->text(0);
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

void NoteExplorer::registerEditor(NoteEditor *editor) {
    m_pNoteEditor = editor;
}

}
