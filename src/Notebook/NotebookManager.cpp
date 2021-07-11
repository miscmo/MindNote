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

NotebookManager *NotebookManager::getInstance() {
    static NotebookManager manager;
    return &manager;
}

NotebookManager::NotebookManager()
    : QObject()
    , m_pCurNotebook(nullptr) {
    initSignal();
}

void NotebookManager::initSignal() {
}

void NotebookManager::setCurNotebook(const QString &path) {
    if (path.isEmpty() || path == m_sCurNotebook)
        return ;

    QDir dir(path);
    Q_ASSERT(dir.exists());

    m_pCurNotebook = getNotebook(path);

    Q_ASSERT(m_pCurNotebook != nullptr);

    m_sCurNotebook = path;

    AppState::getInstance()->addRecentlyDir(path);

    emit signalNotebookChanged();
}

Notebook *NotebookManager::getNotebook(const QString &path) {
    NOTEBOOK_HASH_TYPE::const_iterator it = m_hNotebookHash.find(path);
    if (m_hNotebookHash.end() == it) {
        Notebook *newNotebook = new Notebook(path);
        newNotebook->initNote();
        m_hNotebookHash.insert(path, newNotebook);
        return newNotebook;
    }

    return it.value();
}

void NotebookManager::setCurrentNode(Node *node) {
    bool ret = m_pCurNotebook->setCurrentNode(node);
    if (!ret)
        return ;

    emit signalCurrentNodeChanged(node);
}

void NotebookManager::saveCurrentNode() {
    Node *node = m_pCurNotebook->getCurrentNode();
    if (!node)
        return ;

    node->write(QByteArray().append(NoteEditor::getInstance()->getText()));
}

NotebookManager::~NotebookManager() {
    qDebug() << "~NotebookManager" << endl;
}

}
