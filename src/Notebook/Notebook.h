#ifndef NOTEBOOK_H
#define NOTEBOOK_H

#include <QVector>

namespace MyNote {

class Node;

class Notebook {
public:
    Notebook(const QString &path = QString());
    ~Notebook();

    void initNote();

    Node *getRootNode() const {return m_pRoot;}

    QString getPath() const {return m_sPath;}

private:
    void loadNode(Node *node, const QString &path);

private:
    Node *m_pRoot;
    QString m_sPath;
};

}

#endif // NOTEBOOK_H
