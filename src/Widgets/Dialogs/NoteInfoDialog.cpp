#include "NoteInfoDialog.h"

#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>

namespace MyNote {

NoteInfoDialog::NoteInfoDialog(QWidget *parent, int type)
    : ScrollDialog(parent), m_bType(type) {
    setupUI();
}

void NoteInfoDialog::setupUI() {

    m_pNoteInfoWidget = new QWidget(this);

    m_pMainLayout = new QFormLayout(m_pNoteInfoWidget);

    m_pNotePath = new QLineEdit(m_pNoteInfoWidget);
    m_pMainLayout->addRow(tr("NotePath:"), m_pNotePath);

    m_pNoteName = new QLineEdit(m_pNoteInfoWidget);
    m_pMainLayout->addRow(tr("NoteName:"), m_pNoteName);

    //m_pPasswd = new QLineEdit(m_pNoteInfoWidget);
    m_pMainLayout->addRow(tr("Passwd:"), new QLabel("todo", m_pNoteInfoWidget));

    //m_pRetryPasswd = new QLineEdit(m_pNoteInfoWidget);
    m_pMainLayout->addRow(tr("RetryPasswd:"), new QLabel("todo", m_pNoteInfoWidget));

    //connect(m_pNameLineEdit, &QLineEdit::textEdited, this, &NewNoteDialog::onNameEdited);

    setCentralWidget(m_pNoteInfoWidget);

    setDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    setButtonEnabled(QDialogButtonBox::Ok, false);

    setWindowTitle(tr("New Note"));

}

void NoteInfoDialog::acceptedButtonClicked() {
    if (CreateNewNote()) {
        accept();
    }
}

bool NoteInfoDialog::CreateNewNote() {
    return true;
}

}


