#include "NotebookManager.h"

#include "Notebook.h"
#include <Utils/Utils.h>
#include <Config/AppState.h>

#include <QDebug>

namespace MyNote {

NotebookManager *NotebookManager::getInstance() {
    static NotebookManager manager;
    return &manager;
}

NotebookManager::NotebookManager()
    : QObject() {
    m_pNotebook = new Notebook();
}

void NotebookManager::resetNote(const QString &path) {
    if (path.isEmpty() || path == m_pNotebook->getPath())
        return ;

    m_pNotebook->resetDir(path);

    AppState::getInstance()->addRecentlyDir(path);

    emit signalNotebookChanged(*m_pNotebook);
}

NotebookManager::~NotebookManager() {
    qDebug() << "~NotebookManager" << endl;
    SAFE_DELETE(m_pNotebook);
}

}
