#ifndef NOTEBOOKMANAGER_H
#define NOTEBOOKMANAGER_H

#include <QObject>

namespace gnote {

class Notebook;

class NotebookManager : public QObject {
    Q_OBJECT
public:
    static NotebookManager *getInstance();
    ~NotebookManager();

    void resetNote(const QString &path);

signals:
    void signalNotebookChanged(const Notebook &note);


private:
//public:
    NotebookManager();

private:
    Notebook *m_pNotebook;
};

}

#endif // NOTEBOOKMANAGER_H
