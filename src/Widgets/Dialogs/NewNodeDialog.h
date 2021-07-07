#ifndef NEWNODEDLG_H
#define NEWNODEDLG_H

#include "ScrollDialog.h"

namespace MyNote {

class NewNoteDialog : public ScrollDialog
{
    Q_OBJECT
public:
    NewNoteDialog(QWidget *p_parent = nullptr);

    void setupUI();
};

}

#endif // NEWNODEDLG_H
