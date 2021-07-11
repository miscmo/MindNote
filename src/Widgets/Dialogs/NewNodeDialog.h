#ifndef NEWNODEDLG_H
#define NEWNODEDLG_H

#include "ScrollDialog.h"

class QComboBox;
class QFormLayout;
class QLineEdit;

namespace MyNote {

class NodeInfoWidget;
class Node;

class NewNoteDialog : public ScrollDialog
{
    Q_OBJECT
public:
    NewNoteDialog(Node *parent, int index, QWidget *p_parent = nullptr);

    void setupUI();

    void setupCentralWidget();

    Node *getNewNode() { return m_pNewNode; }

protected:
    void acceptedButtonClicked() Q_DECL_OVERRIDE;

private:
    bool CreateNewNode();

private slots:
    void onNameEdited(const QString &name);

private:
    QWidget *m_pNodeInfoWidget;
    QFormLayout *m_pMainLayout;
    QComboBox *m_pNodeType;
    QLineEdit *m_pNameLineEdit;
    Node *m_pParentNode;
    Node *m_pNewNode;
    int m_nIndex;
};

}

#endif // NEWNODEDLG_H
