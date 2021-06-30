#include "NotebookManager.h"

#include <Notebook.h>
#include <Utils.h>

#include <QDebug>

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
    if (path.isEmpty() || path == m_pNotebook->getPath())
        return ;

    m_pNotebook->resetDir(path);

    emit signalNotebookChanged(*m_pNotebook);
}

NotebookManager::~NotebookManager() {
    qDebug() << "~NotebookManager" << endl;
    SAFE_DELETE(m_pNotebook);
}

}
