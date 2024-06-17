#include "Notebook.h"

#include <Utils/Utils.h>
#include <Notebook/NotebookFactory.h>
#include <Notebook/Node.h>


#include <QDebug>
#include <QDir>
#include <QFile>
#include <QJsonDocument>

using namespace MyNote;

Note::Note(const QString &path)
    : m_pRoot(nullptr)
    , m_sPath(path) {
}

Note::~Note() {
    qDebug() << "~Notebook" << Qt::endl;
    SAFE_DELETE(m_pRoot);
}

Error Note::open() {

    Error err;

    if (m_sPath.isEmpty()) {
        return {ErrorCode::INVALID_ARGUMENT, "note path is empty"};
    }

    QDir notePath(m_sPath);
    if (!notePath.exists()) {
        return {ErrorCode::INVALID_ARGUMENT, "note path not exist in disk"};
    }

    QString noteJson = notePath.filePath(NOTE_DEF_JSON);
    // 文件这里后面统一做成文件池，不用每次读写都要重新打开一次
    QFile noteJsonFile(noteJson);
    if (!noteJsonFile.open(QIODevice::ReadOnly)) {
        return {ErrorCode::OPEN_FILE_FAILED, "open file failed, file: " + noteJson};
    }

    // todo: 暂时先用readAll，后面优化
    QByteArray jsonData = noteJsonFile.readAll();
    noteJsonFile.close();

    QJsonDocument noteJsonDoc = QJsonDocument::fromJson(jsonData);
    if (noteJsonDoc.isNull()) {
        return {ErrorCode::READ_FILE_FAILED, "read json data failed"};
    }

    if (!noteJsonDoc.isObject()) {
        return {ErrorCode::READ_FILE_FAILED, "is not a json object"};
    }

    // 获取 JSON 对象
    QJsonObject noteJsonObject = noteJsonDoc.object();

    Node *root = new Node(this, nullptr);
    err = root->fromJson(noteJsonObject);
    if (!err.isSuccess()) {
        delete root;
        return err;
    }

    m_pRoot = root;

    SetCurrentNode(m_pRoot);

    return Error::success();
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

Error Note::saveNote() {
    if (m_pRoot == nullptr)	{
        return {ErrorCode::POINT_IS_NULLPTR, "note root node is null"};
    }

    QJsonObject noteJson = m_pRoot->toJson();

    // 将 JSON 对象封装进 JSON 文档
    QJsonDocument jsonDoc(noteJson);

    QString jsonPath = QDir(m_sPath).filePath("mindnote.json");

    // 将 JSON 文档写入文件
    QFile file(jsonPath);

    QString backupFilePath = jsonPath + ".bak";

    // 删除备份文件
    // 删除备份暂时放前面，因为每次保存后我想看下原来的内容，以后肯定是要放后面，当文件修改
    // 完后删除备份文件
    if (QFile::exists(backupFilePath)) {
        QFile::remove(backupFilePath);
    }

    // 备份原文件
    if (file.exists()) {
        if (!QFile::rename(jsonPath, backupFilePath)) {
            qWarning() << "Failed to backup original file:" << jsonPath;
            return {ErrorCode::HANDLE_FILE_FAILED, "rename json to bak json failed"};
        }
    }

    if (!file.open(QIODevice::WriteOnly|QIODevice::Truncate)) {
        qWarning() << "Couldn't open file for writing:" << file.errorString();
        if (QFile::exists(backupFilePath)) {
            QFile::rename(backupFilePath, jsonPath);  // 恢复备份文件
        }
        return {ErrorCode::WRITE_FILE_FAILED, "write file failed, file: " + jsonPath};
    }

    file.write(jsonDoc.toJson());
    file.close();

    return Error::success();
}

void Note::TextChanged() {
    if (m_pCurrentNode == nullptr)  {
        return;
    }

    m_pCurrentNode->TextChanged();
}
