#ifndef NOTEEXPLORERCONTEXTMENU_H
#define NOTEEXPLORERCONTEXTMENU_H

#include <QMenu>

namespace MyNote {

class NoteExplorerPopMenu : public QMenu {
    Q_OBJECT
public:
    NoteExplorerPopMenu(QWidget *parent = nullptr);
    ~NoteExplorerPopMenu();

    void initUi();
    void initSignal();


};

}

#endif // NOTEEXPLORERCONTEXTMENU_H
