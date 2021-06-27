#include "Notebook.h"
#include <utils.h>

namespace gnote {

Notebook::Notebook()
    : m_pRoot(nullptr)
    , m_sPath("") {
}

Notebook::~Notebook() {}

void Notebook::resetDir(const QString &path) {
    if (path == m_sPath)
        return ;

    QSharedPointer<Node> tempRoot(new Node(path));
    loadNode(tempRoot, path);

    m_pRoot.swap(tempRoot);
    m_sPath = path;
}

void Notebook::initNote() {
    loadNode(m_pRoot, m_sPath);
}

void Notebook::loadNode(QSharedPointer<Node> node, const QString &path) {
    QStringList dirlist = Utils::listNode(path);

    if (dirlist.empty())
        return ;

    for (auto dir : dirlist) {
        QString fullpath = path + '/' + dir;
        auto newNode = QSharedPointer<Node>(new Node(fullpath));
        loadNode(newNode, fullpath);
        node->addChild(newNode);
    }
}

}
