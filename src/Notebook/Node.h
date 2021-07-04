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
    void addChild(QSharedPointer<Node> node);
    QVector<QSharedPointer<Node>> getChilds() { return m_pChilds; }
    QString getName() { return m_sNodeDir; }

private:
    QString m_sNodeDir;
    QVector<QSharedPointer<Node>> m_pChilds;
};

}

#endif // NODE_H
