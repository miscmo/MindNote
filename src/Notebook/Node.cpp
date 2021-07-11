#include "Node.h"

#include <QDebug>
#include <QDir>
#include <Notebook/Buffer.h>
#include <Notebook/BufferManager.h>

using namespace MyNote;

Node::Node(const QString &dir, Node *parentNode)
    : m_sNodeDir(dir)
    , m_pParentNode(parentNode) {
}

Node::~Node() {
    qDebug() << "~Node" << endl;
}

bool Node::init() {
    QDir dir(m_sNodeDir);
    if (!dir.exists() && !dir.mkpath(dir.path())) {
        return false;
    }

    return true;
}

void Node::addChild(Node *node, int index) {
    if (index < 0 || index > m_vChilds.size()) {
        m_vChilds.append(node);
    } else {
        m_vChilds.insert(index, node);
    }
}

Node *Node::addChildByName(const QString &name, int index) {
    Node *node = new Node(m_sNodeDir + '/' + name, this);
    if (node && node->init()) {
        addChild(node, index);
        return node;
    }

    return nullptr;
}

bool Node::deleteDir() {
    for (auto childs : m_vChilds) {
        childs->deleteDir();
    }

    m_vChilds.erase(m_vChilds.begin(), m_vChilds.end());

    QDir dir(m_sNodeDir);
    return dir.removeRecursively();
}

bool Node::deleteChild(Node *node) {
    int index = m_vChilds.indexOf(node);
    if (-1 == index) {
        return false;
    }

    node->deleteDir();

    m_vChilds.removeAt(index);

    return true;
}

bool Node::hasChildName(const QString &name) {
    for (auto child : m_vChilds) {
        if (child->getName() == name) {
            return true;
        }
    }
    return false;
}


QString Node::getName() {
    QDir dir(m_sNodeDir);
    return dir.dirName();
}

Buffer *Node::getBuffer() {
    return BufferManager::getInstance()->getBuffer(m_sNodeDir);
}

QByteArray Node::read() {
    return getBuffer()->read();
}

void Node::write(const QByteArray &ctx) {
    getBuffer()->write(ctx);
}
