#include "Node.h"

#include <QDebug>
#include <QDir>
#include <QJsonArray>

#include <Notebook/Buffer.h>
#include <Notebook/BufferManager.h>
#include <Widgets/NoteEditor.h>

using namespace MyNote;

Node::Node(Note *note, Node *parent)
    : m_pNote(note)
    , m_pParentNode(parent)
    , m_bIsMod(false){

}

Node::~Node() {
    qDebug() << "~Node" << Qt::endl;

    if (m_vChilds.empty()) {
        return ;
    }

    for (auto node : m_vChilds) {
        if (node != nullptr) {
            delete node;
        }
    }

    m_vChilds.clear();
}

bool Node::init() {
    // QDir dir(m_sNodeDir);
    // if (!dir.exists() && !dir.mkpath(dir.path())) {
    //     return false;
    // }

    // return true;
}

void Node::addChild(Node *node, int index) {
    if (index < 0 || index > m_vChilds.size()) {
        m_vChilds.append(node);
    } else {
        m_vChilds.insert(index, node);
    }
}

Node *Node::addChildByName(const QString &name, int index) {
    // Node *node = new Node(m_sNodeDir + '/' + name, this);
    // if (node && node->init()) {
    //     addChild(node, index);
    //     return node;
    // }

    // return nullptr;
}

bool Node::deleteDir() {
    // for (auto childs : m_vChilds) {
    //     childs->deleteDir();
    // }

    // m_vChilds.erase(m_vChilds.begin(), m_vChilds.end());

    // QDir dir(m_sNodeDir);
    // return dir.removeRecursively();
}

// todo 重新写
bool Node::deleteChild(Node *node) {
    // int index = m_vChilds.indexOf(node);
    // if (-1 == index) {
    //     return false;
    // }

    // node->deleteDir();

    // m_vChilds.removeAt(index);

    // return true;
}

bool Node::hasChild(const QString &ID) {
    for (auto child : m_vChilds) {
        if (child->getID() == ID) {
            return true;
        }
    }
    return false;
}

QString Node::getID() {
    return m_sID;
}

QString Node::getTitle() {
    return m_sTitle;
}

Buffer *Node::getBuffer() {
    // return BufferManager::getInstance()->getBuffer(m_sNodeDir);
}

QByteArray Node::read() {
    //return getBuffer()->read();
    return "test";
}

void Node::write(const QByteArray &ctx) {
    getBuffer()->write(ctx);
}


int Node::Save() {
    // 这里不应该依赖NoteEditor
    // 暂时先这样写
    if (NeedSave()) {
        write(QByteArray().append(NoteEditor::getInstance()->getText().toUtf8()));
        // qDebug() << "save succ, node: " << this->getPath() << "\n";
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

QJsonObject Node::toJson() const {
    QJsonObject jsonObj;
    jsonObj["id"] = m_sID;
    jsonObj["title"] = m_sTitle;
    jsonObj["path"] = m_sPath;
    jsonObj["create_at"] = m_sCreateAt;
    jsonObj["update_at"] = m_sCreateAt;
    jsonObj["style"] = m_sSytle;


    QJsonArray subNode;
    for (const Node *node : m_vChilds) {
        subNode.append(node->toJson());
    }

    jsonObj["subnodes"] = subNode;

    return jsonObj;
}

Error Node::fromJson(QJsonObject obj) {
    QJsonArray subNodes = obj["subnodes"].toArray();

    QVector<Node *> childNodes;

    for (const QJsonValueRef nodeObj : subNodes) {

        std::unique_ptr<Node> childNode = std::make_unique<Node>(m_pNote, this);

        Error err = childNode->fromJson(nodeObj.toObject());

        if (!err.isSuccess()) {
            return err;
        }

        childNodes.append(childNode.release());
    }

    for (auto child : m_vChilds) {
        delete child;
    }

    m_vChilds = childNodes;

    m_sID = obj["id"].toString("");
    m_sTitle = obj["title"].toString("");
    m_sPath = obj["path"].toString("");
    m_sCreateAt = obj["create_at"].toString("");
    m_sUpdateAt = obj["update_at"].toString("");
    m_sSytle = obj["style"].toString("");

    return Error::success();
}

Node *Node::clone() {
    Node *newNode = new Node(m_pNote, m_pParentNode);

    newNode->m_sID = m_sID;
    newNode->m_sTitle = m_sTitle;
    newNode->m_sPath = m_sPath;

    newNode->m_sCreateAt = m_sCreateAt;
    newNode->m_sUpdateAt = m_sUpdateAt;

    newNode->m_sSytle  = m_sSytle;
    // newNode->m_sNodeDir = m_sNodeDir;

    for (auto node : m_vChilds) {
        newNode->m_vChilds.append(node->clone());
    }
}

Error Node::copy(Node *node) {
    if (node == nullptr) {
        return {ErrorCode::INVALID_ARGUMENT, ""};
    }

    for (auto node : m_vChilds) {
        delete node;
    }

    m_vChilds = QVector<Node *>();

    m_sID = node->m_sID;
    m_sTitle = node->m_sTitle;
    m_sPath = node->m_sPath;

    m_sCreateAt = node->m_sCreateAt;
    m_sUpdateAt = node->m_sUpdateAt;

    m_sSytle = node->m_sSytle;
    m_pNote = node->m_pNote;
    m_pParentNode = node->m_pParentNode;
    // m_sNodeDir = node->m_sNodeDir;


    for (auto node : m_vChilds) {
        m_vChilds.append(node->clone());
    }
}
