#ifndef NOTEEXPLORER_H
#define NOTEEXPLORER_H

#include <QWidget>
#include <QTreeWidget>
#include <QSharedPointer>

namespace MyNote {

class Notebook;
class Node;
class NoteEditor;
class NoteExplorerItem;

class NoteExplorer : public QTreeWidget {
    Q_OBJECT
public:
    static NoteExplorer *getInstance();
    ~NoteExplorer();

    void resetNote(const Notebook &note);

    void loadNode(NoteExplorerItem *parent_item, QSharedPointer<Node> node);

    void initUi();
    void setupSignal();

    void onAddSub();
    void onAddPre();
    void onAddPost();
    void onDelete();

    void onItemClicked(QTreeWidgetItem *p_item, int column);
    void onPopMenuRequest(const QPoint& point);

private:
    NoteExplorer(QWidget *p_parent);

private:
    static NoteExplorer* m_pInstance;
};

}

#endif // NOTEEXPLORER_H
