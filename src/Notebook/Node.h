#ifndef NODE_H
#define NODE_H

#include <QVector>
#include <QSharedPointer>
#include <QString>

namespace MyNote {

class Node {
public:
    Node(const QString &dir);
    ~Node();

    bool init();

    void addChild(Node *node);
    QVector<Node *> getChilds() { return m_vChilds; }
    QString getName() { return m_sNodeDir; }

private:
    QString m_sNodeDir;
    QVector<Node *> m_vChilds;
};

}

#endif // NODE_H
