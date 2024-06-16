#ifndef NOTEBOOKMANAGER_H
#define NOTEBOOKMANAGER_H

#include <QObject>
#include <QHash>
#include <QTreeWidgetItem>
#include <QDebug>
#include <Utils/Errors.h>

namespace MyNote {

class Note;
class Node;

using NOTEBOOK_HASH_TYPE = QHash<QString, Note *>;

class NoteMgr : public QObject {
    Q_OBJECT
public:
    static NoteMgr *GetInstance();
    ~NoteMgr();

    void InitSignal();

    Note *GetCurNote() { return m_pCurNote; }
    void SetCurNote(const QString &path);

    bool DeleteNode(Node *node);

    void SetCurNode(Node *node);
    void SaveCurNode();

    int SaveNote();

    void TextChanged();

    Error createNewNote(QString path, QString name);
    Error openNote(QString path);

public slots:
    void OnItemChanged(QTreeWidgetItem *item, int column) {
        qDebug() << "itemChanged" << Qt::endl;
    }

private:
    Note *getNote(const QString &path);

signals:
    void signalCurNodeChanged(Node *node);
    void signalNoteChanged();
    void signalOpenNote(Note *note);
    void signalCloseNote(Note *note);
    void signalDelNote(Note *note);

private:
    NoteMgr();

private:
    NOTEBOOK_HASH_TYPE m_hNoteList;
    Note *m_pCurNote;
};

}

#endif // NOTEBOOKMANAGER_H
