#ifndef NOTEEXPLORER_H
#define NOTEEXPLORER_H

#include <QWidget>
#include <QTreeWidget>
#include <QSharedPointer>

namespace MyNote {

class Notebook;
class Node;
class Note;
class NoteEditor;

class NoteExplorer : public QTreeWidget {
    Q_OBJECT
public:
    static NoteExplorer *getInstance();
    ~NoteExplorer();

    void resetNote();

    void openNote(Note *note);
    void closeNote(Note *note);
    void delNote(Note *note);

    void onItemClicked(QTreeWidgetItem *p_item, int column);
    void onPopMenuRequest(const QPoint& point);
    void onCurrentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

signals:
    void signalCurrentNodeChanged(Node *node);

public slots:
    void onAddSub();
    void onAddPre();
    void onAddPost();
    void onDelete();

private:
    void initUi();
    void setupSignal();

    void clearAllNote();
    void loadNode(QTreeWidgetItem *parent_item, Node *node);


private:
    NoteExplorer(QWidget *p_parent);

private:
    static NoteExplorer* m_pInstance;

};

}

#endif // NOTEEXPLORER_H
