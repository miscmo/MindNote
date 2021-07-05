#ifndef NOTEEXPLORERITEM_H
#define NOTEEXPLORERITEM_H

#include <QTreeWidgetItem>

class QTreeWidget;
class QTreeWidgetItem;

namespace MyNote {

class NoteExplorerItem : public QTreeWidgetItem {
public:
    NoteExplorerItem(QTreeWidget *parent = nullptr);
    NoteExplorerItem(QTreeWidgetItem *parent = nullptr);
    ~NoteExplorerItem();

    void initUi();

};

}

#endif // NOTEEXPLORERITEM_H
