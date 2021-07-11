#include "Notebook.h"

#include <Utils/Utils.h>
#include <Notebook/NotebookFactory.h>
#include <Notebook/Node.h>


#include <QDebug>
#include <QDir>

using namespace MyNote;

Notebook::Notebook(const QString &path)
    : m_pRoot(nullptr)
    , m_sPath(path) {
}

Notebook::~Notebook() {
    qDebug() << "~Notebook" << endl;
    SAFE_DELETE(m_pRoot);
}

void Notebook::initNote() {
    QDir dir(m_sPath);
    Q_ASSERT(dir.exists());

    m_pRoot = NotebookFactory::createNode(m_sPath, nullptr);

    loadNode(m_pRoot, m_sPath);
}

void Notebook::loadNode(Node *node, const QString &path) {
    QStringList dirlist = Utils::listNode(path);

    if (dirlist.empty())
        return ;

    for (auto dir : dirlist) {
        QString fullpath = path + '/' + dir;
        Node *newNode = NotebookFactory::createNode(fullpath, node);
        loadNode(newNode, fullpath);
        node->addChild(newNode);
    }
}

bool Notebook::setCurrentNode(Node *node) {
    if (m_pCurrentNode == node)
        return false;

    m_pCurrentNode = node;
    return true;
}

bool Notebook::deleteNode(Node *node) {
    Node *parentNode = node->getParentNode();

    Q_ASSERT(nullptr != parentNode);

    return parentNode->deleteChild(node);
}

QString Notebook::getName() {
    QDir dir(m_sPath);

    return dir.dirName();
}
