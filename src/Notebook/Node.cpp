#include "Node.h"

#include <QDebug>
#include <QDir>
#include <QJsonArray>
#include <QJsonDocument>

#include <Notebook/Buffer.h>
#include <Notebook/BufferManager.h>
#include <Notebook/Block.h>
#include <Widgets/NotePanel/NoteEditor.h>
#include <Notebook/Notebook.h>
#include <Utils/Utils.h>

using namespace MyNote;

Node::Node(Note *note, Node *parent)
    : m_pNote(note)
    , m_pParentNode(parent)
    , m_bIsMod(false)
    , m_bIsDel(false) {
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

bool Node::init(QString title) {
    m_sID = Utils::GetUUID();
    m_sTitle = title;
    m_sPath = DEF_NODE_FILE;
    m_sCreateAt = QDateTime::currentDateTime().toString(DATETIME_FORMAT);
    m_sUpdateAt = QDateTime::currentDateTime().toString(DATETIME_FORMAT);
}

void Node::addChild(Node *node, int index) {
    if (index < 0 || index > m_vChilds.size()) {
        m_vChilds.append(node);
    } else {
        m_vChilds.insert(index, node);
    }
}

Node *Node::addChildByName(const QString &name, int index) {
    Node *node = new Node(getNote(), this);
    if (node && node->init(name)) {
        addChild(node, index);
        return node;
    }

    return nullptr;
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
    return BufferManager::getInstance()->getBuffer(getNodeFullPath());
}

QByteArray Node::read() {
    return getBuffer()->read();
}

/* 
read返回的是一个json,格式如下:

    "node": {
        "config": "",
        "font": "",
        "bgStyle": "",
        "fgStyle": "",
        "layout": [
            [
                {"type": "Markdown", "content":""},
                {"type": "PlainText", "content":""}
            ],
            [],
            []
        ] 
    }
    
    
    "type": "PlainText",   // Markdown、RichText、Drawing
    "content": "",    // file
    "content_type": "", // text，file
    "site": "",
}

将json中node.layout中的每一个元素解析成一个Block对象，然后将Block对象放入QVector中，最后将QVector放入QVector中返回
*/
Error Node::buildBlocks(const QJsonArray &blockArr, QVector<QVector<Block *> > &blocks) {

    for (const QJsonValueRef layoutItem : blockArr) {
        QVector<Block *> inBlocks;
        QJsonArray blockArr = layoutItem.toArray();

        for (const QJsonValueRef blockItem : blockArr) {
            QString type = blockItem.toObject()["type"].toString(BLOCK_TYPE_TEXT);
            QString content = blockItem.toObject()["content"].toString("");
            QString contentType = blockItem.toObject()["content_type"].toString(BLOCK_CONTENT_TYPE_TEXT);
            Block *block = new Block(type, content, contentType);

            inBlocks.append(block);
        }

        blocks.append(inBlocks);
    }


    return Error::success();
}

Error Node::buildNode() {
    // todo 如果已经构建并且未修改过，直接返回，不需要重新构建
    QByteArray ctx = read();
    if (ctx.isNull() || ctx.isEmpty()) {
        return {ErrorCode::CONTENT_IS_EMPTY, "read  is empty"};
    }

    // blocks非空说明已经构建过，不需要重复构建，重复构建使用reBuild
    if (!m_vBlocks.empty()) {
        // 非空暂时清空，重复构建
        for (auto blocks : m_vBlocks) {
            for (auto block : blocks) {
                delete block;
            }
        }
        m_vBlocks.clear();
    }

    // 先判断ctx是否为json
    QJsonParseError jsonErr;
    QJsonDocument jsonObj = QJsonDocument::fromJson(ctx, &jsonErr);
    if (jsonErr.error != QJsonParseError::NoError) {
        // 非json格式，默认以text文本格式展示
        QVector<Block *> inBlcok;
        QString type = BLOCK_TYPE_TEXT;
        QString content = QString::fromUtf8(ctx);
        QString contentType = BLOCK_CONTENT_TYPE_TEXT;
        Block *block = new Block(type, content, contentType);
        inBlcok.append(block);

        m_vBlocks.append(inBlcok);
        return Error::success();
    }

    QJsonArray blockArr = jsonObj["blocks"].toArray(QJsonArray());
    // 检查是否有blocks
    if (blockArr.isEmpty()) {
        return {ErrorCode::CONTENT_IS_EMPTY, "blocks is empty"};
    }

    // todo 这里要错误处理
    Error err = buildBlocks(blockArr, m_vBlocks);
    if (!err.isSuccess()) {
        qDebug() << "build blocks error: " << err.message << Qt::endl;
    }

    return Error::success();
}

void Node::write(const QByteArray &ctx) {
    getBuffer()->write(ctx);
}

QString Node::getNodeFullPath() {
    QString nodePath = QDir(m_pNote->GetPath()).filePath(m_sID);
    QString filePath = QDir(nodePath).filePath(DEF_NODE_FILE);
    return filePath;
}


int Node::Save() {
    // 这里不应该依赖NoteEditor
    // 暂时先这样写
    if (NeedSave()) {
        //QByteArray editorByteArr = QByteArray().append(NoteEditor::getInstance()->getText().toUtf8());
        //QString editorStr = QString::fromUtf8(editorByteArr);
        //write(editorByteArr);
        saveAllBlocks();
        // qDebug() << "save succ, node: " << this->getPath() << "\n";
        m_bIsMod = false;
        emit signalModStatusChanged(this);
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

// 将所有的block保存到json中
Error Node::saveAllBlocks() {
    QJsonArray blockArr;
    for (auto blocks : m_vBlocks) {
        QJsonArray blockItem;
        for (auto block : blocks) {
            QJsonObject blockObj;
            blockObj["type"] = block->getType();
            blockObj["content"] = block->getContent();
            blockObj["content_type"] = block->getContentType();
            blockItem.append(blockObj);
        }

        blockArr.append(blockItem);
    }

    QJsonObject jsonObj;
    jsonObj["blocks"] = blockArr;

    QJsonDocument jsonDoc(jsonObj);
    QByteArray ctx = jsonDoc.toJson();

    write(ctx);

    return Error::success();
}


bool Node::NeedSave() {
    return m_bIsMod;
}


void Node::TextChanged() {
    if (m_bIsMod == false) {
        m_bIsMod = true;
        emit signalModStatusChanged(this);
    }
}

Note *Node::getNote() {
    return m_pNote;
}

QJsonObject Node::toJson() const {
    QJsonObject jsonObj;
    jsonObj["id"] = m_sID;
    jsonObj["title"] = m_sTitle;
    jsonObj["path"] = m_sPath;
    jsonObj["create_at"] = m_sCreateAt;
    jsonObj["update_at"] = m_sCreateAt;
    jsonObj["delete_at"] = m_sDeleteAt;
    jsonObj["style"] = m_sSytle;
    jsonObj["is_del"] = m_bIsDel;

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
    m_sSytle = obj["style"].toString("");
    m_bIsDel = obj["is_del"].toBool(false);
    m_sCreateAt = obj["create_at"].toString("");
    m_sUpdateAt = obj["update_at"].toString("");
    m_sDeleteAt = obj["delete_at"].toString("");

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

void Node::setDel(bool isDel) {
    m_bIsDel = isDel;
    if (m_bIsDel) {
        m_sDeleteAt = QDateTime::currentDateTime().toString(DATETIME_FORMAT);
    }
}
