#ifndef NOTEBOOK_H
#define NOTEBOOK_H

#include <QVector>
#include <QObject>

namespace MyNote {

class Node;

class Notebook : public QObject {
    Q_OBJECT
public:
    Notebook(const QString &path = QString());
    ~Notebook();

    void initNote();

    Node *getRootNode() const {return m_pRoot;}
    bool setCurrentNode(Node *node);
    Node *getCurrentNode() { return m_pCurrentNode; }

    bool deleteNode(Node *node);

    QString getPath() const {return m_sPath;}
    QString getName();

private:
    void loadNode(Node *node, const QString &path);

private:
    Node *m_pRoot;
    Node *m_pCurrentNode;
    QString m_sPath;
};

}

#endif // NOTEBOOK_H
