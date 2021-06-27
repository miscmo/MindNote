#include "NotebookManager.h"

#include <Notebook.h>

namespace gnote {

NotebookManager *NotebookManager::getInstance() {
    static NotebookManager manager;
    return &manager;
}

NotebookManager::NotebookManager()
    : QObject() {
    m_pNotebook = new Notebook();
}

void NotebookManager::resetNote(const QString &path) {
    m_pNotebook->resetDir(path);

    emit signalNotebookChanged(*m_pNotebook);
}

NotebookManager::~NotebookManager() {

}

}
