#include "NodeInfoWidget.h"

#include <Notebook/Node.h>
#include <Notebook/Notebook.h>
#include <Notebook/NotebookManager.h>
#include <Widgets/WidgetFactory.h>

#include <QLabel>
#include <QFormLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QDebug>

using namespace MyNote;

NodeInfoWidget::NodeInfoWidget(QWidget *parent) {
}

NodeInfoWidget::~NodeInfoWidget() {
}

void NodeInfoWidget::initUi() {
    m_pMainLayout = WidgetFactory::createFormLayout(this);

    QString notebookName = NotebookManager::getInstance()->getCurNotebook()->getName();

    m_pMainLayout->addRow(tr("Notebook:"),
                          new QLabel(notebookName, this));
    m_pMainLayout->addRow(tr("ParentNode:"),
                          new QLabel(m_pParentNode->getName(), this));

    m_pNodeType = new QComboBox(this);
    m_pNodeType->addItem("Markdown");
    m_pMainLayout->addRow(tr("NodeType:"), m_pNodeType);

    initNameLineEdit();

}

void NodeInfoWidget::initNameLineEdit() {
    m_pNameLineEdit = new QLineEdit(this);
    m_pMainLayout->addRow(tr("NoteName:"), m_pNameLineEdit);

    connect(m_pNameLineEdit, &QLineEdit::textEdited, this, &NodeInfoWidget::onNameEdited);
}


void NodeInfoWidget::initNode(Node *parent, int index) {
    m_pParentNode = parent;
    m_nIndex = index;

    initUi();
}

void NodeInfoWidget::onNameEdited(const QString &name) {
    qDebug() << name << endl;
}
