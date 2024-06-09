#ifndef NOTEBOOK_H
#define NOTEBOOK_H

#include <QVector>
#include <QObject>

namespace MyNote {

class Node;

class Note : public QObject {
    Q_OBJECT
public:
    Note(const QString &path = QString());
    ~Note();

    void InitNote();

    //笔记操作

    // 保存笔记
    int SaveNote();

    const QString& GetPath() const {return m_sPath;}
    const QString GetName();

    // 结点操作
    Node *GetRootNode() const {return m_pRoot;}
    bool SetCurrentNode(Node *node);
    Node *GetCurrentNode() { return m_pCurrentNode; }

    bool DeleteNode(Node *node);

    void TextChanged();

private:
    void loadNode(Node *node, const QString &path);

private:
    Node *m_pRoot;
    Node *m_pCurrentNode;
    QString m_sPath;
};

}

#endif // NOTEBOOK_H
