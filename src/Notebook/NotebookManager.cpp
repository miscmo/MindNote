#include "NotebookManager.h"


#include <Utils/Utils.h>
#include <Config/AppState.h>
#include <Notebook/Notebook.h>
#include <Notebook/Node.h>
#include <Notebook/Block.h>
#include <Widgets/NoteExplorer/NoteExplorer.h>
#include <Widgets/NotePanel/TextEditor.h>


#include <QDebug>
#include <QDir>
#include <QDateTime>
#include <QJsonDocument>
#include <QMessageBox>

namespace MyNote {

NoteMgr* NoteMgr::GetInstance() {
    static NoteMgr mgr;
    return &mgr;
}

NoteMgr::NoteMgr()
    : QObject()
    , m_pCurNode(nullptr) {
    InitSignal();
}

void NoteMgr::InitSignal() {
}

// void NoteMgr::SetCurNote(const QString &path) {
//     if (path.isEmpty()) {
//         qWarning() << "open note path is emtpy\n";
//         return ;
//     }

//     QDir dir(path);
//     Q_ASSERT(dir.exists());

//     if (m_pCurNote != nullptr && m_pCurNote->GetPath() == path) {
//         qDebug() << "open note same with cur note\n";
//         return ;
//     }

//     m_pCurNote = getNote(path);

//     Q_ASSERT(m_pCurNote != nullptr);

//     AppState::getInstance()->addRecentlyDir(path);

//     // 截至目前，底层数据已经构建好了，要基于这些数据构建用户界面

//     qDebug() << "cur note is: " << m_pCurNote->GetPath() << "\n";
//     //qDebug() << "cur node is: " << m_pCurNote->GetCurrentNode()->getPath() << "\n";

//     emit signalNoteChanged();
//     emit signalCurNodeChanged(m_pCurNote->GetCurrentNode());
// }

void NoteMgr::SetCurNode(Node *node) {
    m_pCurNode = node;
    emit signalCurNodeChanged(node);
}

void NoteMgr::SaveCurNode() {
    if (!m_pCurNode)
        return ;

    if (m_pCurNode->NeedSave()) {
        //node->write(QByteArray().append(NoteEditor::getInstance()->getText().toUtf8()));
        m_pCurNode->Save();
    }
}

int NoteMgr::SaveNote(Note *note) {
    // 将Note的结构保存下来
    note->saveNote();
}

bool NoteMgr::DeleteNode(Node *node) {
    if (!m_pCurNode) {
        return false;
    }
    Note *curNote = m_pCurNode->getNote();
    if (curNote == nullptr) {
        return false;
    }

    return curNote->DeleteNode(node);
}

void NoteMgr::TextChanged() {
    if (m_pCurNode == nullptr) {
        return ;
    }

    m_pCurNode->TextChanged();
}

Error NoteMgr::createNewNote(QString path, QString name) {
    // 参数校验
    if (path.isEmpty() || name.isEmpty()) {
        return {ErrorCode::INVALID_ARGUMENT, "path or name is empty"};
    }

    QDir notePath(path);

    if (!notePath.exists()) {
        return {ErrorCode::INVALID_ARGUMENT, "path: " + path + "not exists"};
    }

    QString fullPath = notePath.filePath(name);
    QDir noteFullPath(fullPath);
    if (noteFullPath.exists()) {
        return {ErrorCode::INVALID_ARGUMENT, "note full path alreay exists, path: " + fullPath};
    }

    // 创建笔记目录
    if (!noteFullPath.mkdir(fullPath)) {
        return {ErrorCode::CREATE_FILE_FAILED, "create dir failed, dir: " + fullPath};
    }

    // 创建mindnote.json
    QJsonObject noteJson;
    noteJson["id"] = Utils::GetUUID();
    noteJson["title"] = name;
    noteJson["path"] = DEF_NODE_FILE;
    noteJson["is_del"] = false;
    noteJson["create_at"] = QDateTime::currentDateTime().toString(DATETIME_FORMAT);
    noteJson["update_at"] = QDateTime::currentDateTime().toString(DATETIME_FORMAT);
    noteJson["delete_at"] = "";
    noteJson["style"] = "";
    noteJson["subnotes"] = "[]";


    // 将 JSON 对象封装进 JSON 文档
    QJsonDocument jsonDoc(noteJson);

    QString jsonPath = QDir(fullPath).filePath("mindnote.json");

    // 将 JSON 文档写入文件
    QFile file(jsonPath);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Couldn't open file for writing:" << file.errorString();
        return {ErrorCode::WRITE_FILE_FAILED, "write file failed, file: " + jsonPath};
    }

    file.write(jsonDoc.toJson());
    file.close();

    openNote(fullPath);

    // 到这里已经成功初始化完了一个新笔记本
    return Error::success();
}

Error NoteMgr::openNote(QString path) {

    Error err;

    for (auto note : m_vNoteList) {
        if (note->GetPath() == path) {
            // 笔记已经打开了
            qDebug() << "note has been opened, note: " << path << Qt::endl;
            return Error::success();
        }
    }

    qDebug() << "create new note\n";

    Note *openNote = new Note(path);
    err = openNote->open();
    if (!err.isSuccess()) {
        return err;
    }

    m_vNoteList.append(openNote);

    // 刷新explorer
    //addNoteToExplorer();

    AppState::getInstance()->addRecentlyDir(path);

    emit signalOpenNote(openNote);

    return Error::success();
}

void NoteMgr::OnItemChanged(QTreeWidgetItem *item, int column) {

    // item初始化时也会触发这里信号，这里暂时用item是否被用户选中过滤一下
    // 后面要考虑更好的实现方式
    if (!item->isSelected()) {
        return ;
    }

    qDebug() << "itemChanged" << Qt::endl;

    Node *curNode = item->data(0, Qt::UserRole).value<Node *>();

    if (item->text(0).isEmpty()) {
        QMessageBox::warning(NoteExplorer::getInstance(), tr("Invalid Name"), tr("Name cannot be empty"));
        item->setText(0, curNode->getTitle());
        return;
    }

    if (item->text(0) == curNode->getTitle()) {
        return;
    }

    curNode->setTitle(item->text(0));
    curNode->getNote()->saveNote();
}

QVector<QString> NoteMgr::getOpenNotes() {
    QStringList noteList;

    for (auto note : m_vNoteList) {
        noteList.append(note->GetPath());
    }

    return noteList;
}

void NoteMgr::openNotes(QStringList notes) {
    for (auto &path : notes) {
        Error err = openNote(path);
        if (!err.isSuccess()) {
            qDebug() << "open note failed, note: " << path << Qt::endl;
        }
    }
}

Block *NoteMgr::getNewBlock(Node *node, QString type) {
    Block *block = new Block(node, type, "", BLOCK_CONTENT_TYPE_TEXT);

    node->addBlock(block);

    return block;
}

NoteMgr::~NoteMgr() {
    qDebug() << "~NotebookManager" << Qt::endl;
}


}
