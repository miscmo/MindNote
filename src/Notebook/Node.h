#ifndef NODE_H
#define NODE_H

#include <QVector>
#include <QSharedPointer>
#include <QString>
#include <QByteArray>

namespace MyNote {

class Buffer;

class Node : public QObject {
    Q_OBJECT
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

    // 只保存当前结点内容
    int Save();
    // 保存当前结点和所有子结点
    int SaveAll();

    bool NeedSave();

    void TextChanged();

signals:
    void SignalModStatusChanged(Node *node);

private:
    QString m_sNodeDir;
    QVector<Node *> m_vChilds;
    Node *m_pParentNode;
    bool m_bIsMod;
};

}

#endif // NODE_H
