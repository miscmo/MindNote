#ifndef NODEDELETECONFIRMDIALOG_H
#define NODEDELETECONFIRMDIALOG_H

#include "ScrollDialog.h"

namespace MyNote {

class Node;

class NodeDeleteConfirmDialog : public ScrollDialog {
    Q_OBJECT
public:
    NodeDeleteConfirmDialog(Node *node, QWidget *parent = nullptr);
    ~NodeDeleteConfirmDialog();

    void setupUi();

    bool confirmDeleteNode();

protected:
    void acceptedButtonClicked() Q_DECL_OVERRIDE;

private:
    Node *m_pNode;
};

}

#endif // NODEDELETECONFIRMDIALOG_H
