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

    void resetNote();


    void onItemClicked(QTreeWidgetItem *p_item, int column);
    void onPopMenuRequest(const QPoint& point);

public slots:
    void onAddSub();
    void onAddPre();
    void onAddPost();
    void onDelete();

private:
    void initUi();
    void setupSignal();

    void clearAllNote();
    void loadNode(NoteExplorerItem *parent_item, Node *node);


private:
    NoteExplorer(QWidget *p_parent);

private:
    static NoteExplorer* m_pInstance;
};

}

#endif // NOTEEXPLORER_H
