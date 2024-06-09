#include "NotebookManager.h"

#include <Utils/Utils.h>
#include <Config/AppState.h>
#include <Notebook/Notebook.h>
#include <Notebook/Node.h>
#include <Widgets/NoteExplorer.h>
#include <Widgets/NoteEditor.h>

#include <QDebug>
#include <QDir>

namespace MyNote {

 NoteMgr* NoteMgr::GetInstance() {
    static NoteMgr mgr;
    return &mgr;
}

NoteMgr::NoteMgr()
    : QObject()
    , m_pCurNote(nullptr) {
    InitSignal();
}

void NoteMgr::InitSignal() {
}

void NoteMgr::SetCurNote(const QString &path) {
    if (path.isEmpty()) {
        qWarning() << "open note path is emtpy\n";
        return ;
    }

    QDir dir(path);
    Q_ASSERT(dir.exists());

    if (m_pCurNote != nullptr && m_pCurNote->GetPath() == path) {
        qDebug() << "open note same with cur note\n";
        return ;
    }

    m_pCurNote = getNote(path);

    Q_ASSERT(m_pCurNote != nullptr);

    AppState::getInstance()->addRecentlyDir(path);

    // 截至目前，底层数据已经构建好了，要基于这些数据构建用户界面

    qDebug() << "cur note is: " << m_pCurNote->GetPath() << "\n";
    qDebug() << "cur node is: " << m_pCurNote->GetCurrentNode()->getPath() << "\n";

    emit signalNoteChanged();
    emit signalCurNodeChanged(m_pCurNote->GetCurrentNode());
}

Note *NoteMgr::getNote(const QString &path) {
    NOTEBOOK_HASH_TYPE::const_iterator it = m_hNoteList.find(path);
    if (m_hNoteList.end() == it) {
        qDebug() << "create new note\n";
        Note *newNote = new Note(path);
        newNote->InitNote();
        m_hNoteList.insert(path, newNote);
        return newNote;
    }

    qDebug() << "open already created note\n";

    return it.value();
}

void NoteMgr::SetCurNode(Node *node) {
    bool ret = m_pCurNote->SetCurrentNode(node);
    if (!ret)
        return ;

    emit signalCurNodeChanged(node);
}

void NoteMgr::SaveCurNode() {
    Node *node = m_pCurNote->GetCurrentNode();
    if (!node)
        return ;

    if (node->NeedSave()) {
        //node->write(QByteArray().append(NoteEditor::getInstance()->getText().toUtf8()));
        node->Save();
    }
}

int NoteMgr::SaveNote() {
    if (m_pCurNote == nullptr) {
        return 0;
    }

    return m_pCurNote->SaveNote();
}

bool NoteMgr::DeleteNode(Node *node) {
    return GetCurNote()->DeleteNode(node);
}

void NoteMgr::TextChanged() {
    GetCurNote()->TextChanged();
}

NoteMgr::~NoteMgr() {
    qDebug() << "~NotebookManager" << Qt::endl;
}


}
