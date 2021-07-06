#include "NotebookManager.h"

#include <Utils/Utils.h>
#include <Config/AppState.h>
#include <Notebook/Notebook.h>

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

NotebookManager::~NotebookManager() {
    qDebug() << "~NotebookManager" << endl;
}

}
