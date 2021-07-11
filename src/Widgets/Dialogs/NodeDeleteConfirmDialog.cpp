#include "NodeDeleteConfirmDialog.h"

#include <Notebook/NotebookManager.h>

#include <QLabel>

using namespace MyNote;

NodeDeleteConfirmDialog::NodeDeleteConfirmDialog(Node *node, QWidget *parent)
    : ScrollDialog(parent)
    , m_pNode(node) {
    setupUi();
}

NodeDeleteConfirmDialog::~NodeDeleteConfirmDialog() {
}

void NodeDeleteConfirmDialog::setupUi() {
    setDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    setWindowTitle(tr("Delete Confirm?"));

    QLabel *confirmLabel = new QLabel(tr("ensure delete?"), this);

    setCentralWidget(confirmLabel);
}

void NodeDeleteConfirmDialog::acceptedButtonClicked() {
    if (confirmDeleteNode()) {
        accept();
    }
}

bool NodeDeleteConfirmDialog::confirmDeleteNode() {
    if (!m_pNode)
        return true;

    return NotebookManager::getInstance()->deleteNode(m_pNode);
}


