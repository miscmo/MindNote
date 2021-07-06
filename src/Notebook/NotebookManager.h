#ifndef NOTEBOOKMANAGER_H
#define NOTEBOOKMANAGER_H

#include <QObject>
#include <QHash>

namespace MyNote {

class Notebook;

using NOTEBOOK_HASH_TYPE = QHash<QString, Notebook *>;

class NotebookManager : public QObject {
    Q_OBJECT
public:
    static NotebookManager *getInstance();
    ~NotebookManager();

    Notebook *getCurNotebook() { return m_pCurNotebook; }
    void setCurNotebook(const QString &path);

private:
    Notebook *getNotebook(const QString &path);

signals:
    void signalNotebookChanged();

private:
    NotebookManager();

private:
    NOTEBOOK_HASH_TYPE m_hNotebookHash;
    Notebook *m_pCurNotebook;
    QString m_sCurNotebook;
};

}

#endif // NOTEBOOKMANAGER_H
