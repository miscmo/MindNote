#ifndef NOTEINFODIALOG_H
#define NOTEINFODIALOG_H

#include "ScrollDialog.h"

class QFormLayout;
class QLineEdit;

namespace MyNote {

class NoteInfoDialog : public ScrollDialog {
    Q_OBJECT

public:
    NoteInfoDialog(QWidget *p_parent, int type = 0);

    void setupUI();

protected:
    void acceptedButtonClicked() Q_DECL_OVERRIDE;

private slots:
    void onNoteInfoEdited(const QString &path);

private:
    QWidget *m_pNoteInfoWidget;
    QFormLayout *m_pMainLayout;
    QLineEdit *m_pNotePath;
    QLineEdit *m_pNoteName;
    QLineEdit *m_pPasswd;
    QLineEdit *m_pRetryPasswd;
    int m_bType;

};

}

#endif // NOTEINFODIALOG_H
