#include "NewNodeDialog.h"

#include "NodeInfoWidget.h"

#include <Notebook/NotebookManager.h>
#include <Notebook/Notebook.h>
#include <Notebook/Node.h>
#include <Widgets/WidgetFactory.h>

#include <QWidget>
#include <QFormLayout>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QDebug>

using namespace MyNote;

NewNoteDialog::NewNoteDialog(Node *parent, int index, QWidget *p_parent)
    : ScrollDialog(p_parent)
    , m_pParentNode(parent)
    , m_nIndex(index)
{
    setupUI();

    m_pNameLineEdit->setFocus();
}

void NewNoteDialog::setupUI() {
    setupCentralWidget();

    setDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    setButtonEnabled(QDialogButtonBox::Ok, false);

    setWindowTitle(tr("New Note"));
}

void NewNoteDialog::setupCentralWidget() {
    m_pNodeInfoWidget = new QWidget(this);

    m_pMainLayout = WidgetFactory::createFormLayout(m_pNodeInfoWidget);

    QString notebookName = NotebookManager::getInstance()->getCurNotebook()->getName();

    m_pMainLayout->addRow(tr("Notebook:"),
                          new QLabel(notebookName, m_pNodeInfoWidget));
    m_pMainLayout->addRow(tr("ParentNode:"),
                          new QLabel(m_pParentNode->getName(), m_pNodeInfoWidget));

    m_pNodeType = new QComboBox(m_pNodeInfoWidget);
    m_pNodeType->addItem("Markdown");
    m_pMainLayout->addRow(tr("NodeType:"), m_pNodeType);

    m_pNameLineEdit = new QLineEdit(m_pNodeInfoWidget);
    m_pMainLayout->addRow(tr("NoteName:"), m_pNameLineEdit);

    connect(m_pNameLineEdit, &QLineEdit::textEdited, this, &NewNoteDialog::onNameEdited);

    setCentralWidget(m_pNodeInfoWidget);
}

void NewNoteDialog::onNameEdited(const QString &name) {
    qDebug() << name << endl;
    if (name.isEmpty() || m_pParentNode->hasChildName(name)) {
        setButtonEnabled(QDialogButtonBox::Ok, false);
        return ;
    }

    setButtonEnabled(QDialogButtonBox::Ok, true);
}

void NewNoteDialog::acceptedButtonClicked() {
    if (CreateNewNode()) {
        accept();
    }
}

bool NewNoteDialog::CreateNewNode() {
    m_pNewNode = m_pParentNode->addChildByName(m_pNameLineEdit->text(), m_nIndex);
    return m_pNewNode != nullptr;
}
