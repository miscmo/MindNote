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
class Block;

class NoteMgr : public QObject {
    Q_OBJECT
public:
    static NoteMgr *GetInstance();
    ~NoteMgr();

    void InitSignal();

    Node *GetCurNode() {return m_pCurNode;}
    void SetCurNode(Node *node);

    bool DeleteNode(Node *node);

    void SaveCurNode();

    int SaveNote(Note *note);

    void TextChanged();

    Error createNewNote(QString path, QString name);
    Error openNote(QString path);

    QStringList getOpenNotes();
    void openNotes(QStringList notes);

    Block *getNewBlock(Node *node, QString type);

public slots:
    void OnItemChanged(QTreeWidgetItem *item, int column);

signals:
    void signalCurNodeChanged(Node *node);
    void signalNoteChanged();
    void signalOpenNote(Note *note);
    void signalCloseNote(Note *note);
    void signalDelNote(Note *note);

private:
    NoteMgr();

private:
    QVector<Note *> m_vNoteList;
    //Note *m_pCurNote;
    Node *m_pCurNode;
};

}

#endif // NOTEBOOKMANAGER_H
