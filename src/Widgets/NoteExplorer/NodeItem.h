#ifndef NODEITEM_H
#define NODEITEM_H

#include <QObject>
#include <QTreeWidgetItem>


namespace MyNote {

class Node;

class NodeItem : public QObject, public QTreeWidgetItem {
    Q_OBJECT
public:
    NodeItem(QTreeWidgetItem *parent);
    NodeItem(QTreeWidget *parent);

    void init();

    //NodeItem(const QTreeWidget &other);

    // 将QTreeWidgetItem赋值给NodeItem时，要调用拷贝构造函数
    ~NodeItem();

    void ConnNodeIsMod(Node *node);

public slots:
    void HandleNodeIsMod(Node *node);

private:
};

}

#endif // NODEITEM_H
