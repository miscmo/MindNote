#ifndef NOTEEXPLORER_H
#define NOTEEXPLORER_H

#include <QWidget>
#include <QTreeWidget>
#include <QSharedPointer>

namespace gnote {

class Notebook;
class Node;
class NoteEditor;

class NoteExplorer : public QTreeWidget {
    Q_OBJECT
public:
    static NoteExplorer *getInstance();
    ~NoteExplorer();

    void resetNote(const Notebook &note);

    void loadNode(QTreeWidgetItem *parent_item, QSharedPointer<Node> node);

    void initUi();
    void setupSignal();

    void onItemClicked(QTreeWidgetItem *p_item, int column);
    void registerEditor(NoteEditor *editor);

private:
    NoteExplorer(QWidget *p_parent);

private:
    NoteEditor *m_pNoteEditor;
};

}

#endif // NOTEEXPLORER_H
