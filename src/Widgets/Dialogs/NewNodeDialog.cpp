#include "NewNodeDialog.h"

#include <QtWidgets>

using namespace MyNote;

NewNoteDialog::NewNoteDialog(QWidget *p_parent)
    : ScrollDialog(p_parent)
{
    setupUI();
}

void NewNoteDialog::setupUI() {
    setDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    setButtonEnabled(QDialogButtonBox::Ok, false);

    setWindowTitle(tr("New Note"));
}
