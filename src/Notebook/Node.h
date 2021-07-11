#ifndef NODE_H
#define NODE_H

#include <QVector>
#include <QSharedPointer>
#include <QString>
#include <QByteArray>

namespace MyNote {

class Buffer;

class Node {
public:
    Node(const QString &dir, Node *parentNode);
    ~Node();

    bool init();

    void addChild(Node *node, int index = -1);
    Node *addChildByName(const QString &name, int index);

    bool deleteDir();
    bool deleteChild(Node *node);

    QVector<Node *> getChilds() { return m_vChilds; }
    QString getName();
    QString getPath() { return m_sNodeDir; }

    QByteArray read();
    void write(const QByteArray &ctx);

    bool hasChildName(const QString &name);

    Buffer *getBuffer();

    Node *getParentNode() { return m_pParentNode; }

private:
    QString m_sNodeDir;
    QVector<Node *> m_vChilds;
    Node *m_pParentNode;
};

}

#endif // NODE_H
