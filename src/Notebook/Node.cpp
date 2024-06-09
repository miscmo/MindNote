#include "Node.h"

#include <QDebug>
#include <QDir>
#include <Notebook/Buffer.h>
#include <Notebook/BufferManager.h>
#include <Widgets/NoteEditor.h>

using namespace MyNote;

Node::Node(const QString &dir, Node *parentNode)
    : m_sNodeDir(dir)
    , m_pParentNode(parentNode)
    , m_bIsMod(0){
}

Node::~Node() {
    qDebug() << "~Node" << Qt::endl;
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


int Node::Save() {
    // 这里不应该依赖NoteEditor
    // 暂时先这样写
    if (NeedSave()) {
        write(QByteArray().append(NoteEditor::getInstance()->getText().toUtf8()));
        qDebug() << "save succ, node: " << this->getPath() << "\n";
        m_bIsMod = false;
        emit SignalModStatusChanged(this);
    }
}

int Node::SaveAll() {
    int ret = 0;
    for (auto child : m_vChilds) {
        if (child->NeedSave()) {
            if (child->Save() != 1) {
                // 有node保存失败
                ret = -1;
            }
        }
    }

    return ret;
}


bool Node::NeedSave() {
    return m_bIsMod;
}


void Node::TextChanged() {
    if (m_bIsMod == false) {
        m_bIsMod = true;
        emit SignalModStatusChanged(this);
    }
}
