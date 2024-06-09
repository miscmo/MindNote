#include "Notebook.h"

#include <Utils/Utils.h>
#include <Notebook/NotebookFactory.h>
#include <Notebook/Node.h>


#include <QDebug>
#include <QDir>

using namespace MyNote;

Note::Note(const QString &path)
    : m_pRoot(nullptr)
    , m_sPath(path) {
}

Note::~Note() {
    qDebug() << "~Notebook" << Qt::endl;
    SAFE_DELETE(m_pRoot);
}

void Note::InitNote() {
    QDir dir(m_sPath);
    Q_ASSERT(dir.exists());

    m_pRoot = NotebookFactory::createNode(m_sPath, nullptr);

    loadNode(m_pRoot, m_sPath);
    SetCurrentNode(m_pRoot);
}

void Note::loadNode(Node *node, const QString &path) {
    QStringList dirlist = Utils::listNode(path);

    if (dirlist.empty())
        return ;

    for (auto &dir : dirlist) {
        QString fullpath = path + '/' + dir;
        Node *newNode = NotebookFactory::createNode(fullpath, node);
        loadNode(newNode, fullpath);
        node->addChild(newNode);
    }
}

bool Note::SetCurrentNode(Node *node) {
    if (m_pCurrentNode == node)
        return false;

    m_pCurrentNode = node;
    return true;
}

bool Note::DeleteNode(Node *node) {
    Node *parentNode = node->getParentNode();

    Q_ASSERT(nullptr != parentNode);

    return parentNode->deleteChild(node);
}

const QString Note::GetName() {
    QDir dir(m_sPath);

    return dir.dirName();
}

int Note::SaveNote() {
    if (m_pRoot == nullptr)	{
        return 0;
    }

    return m_pRoot->SaveAll();
}

void Note::TextChanged() {
    if (m_pCurrentNode == nullptr)  {
        return;
    }

    m_pCurrentNode->TextChanged();
}
