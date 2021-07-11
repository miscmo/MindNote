#ifndef NOTEEXPLORERITEM_H
#define NOTEEXPLORERITEM_H

#include <QTreeWidgetItem>

class QTreeWidget;
class QTreeWidgetItem;

namespace MyNote {

class Node;

class NoteExplorerItem : public QTreeWidgetItem {
public:
    NoteExplorerItem(QTreeWidget *parent);
    NoteExplorerItem(QTreeWidgetItem *parent = nullptr);
    ~NoteExplorerItem();

    void setNode(Node *node);
    Node *getNode() { return m_pNode; }

    void init();
    void initUi();

private:
    Node *m_pNode;

};

}

#endif // NOTEEXPLORERITEM_H
