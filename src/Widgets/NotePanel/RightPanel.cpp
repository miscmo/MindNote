#include "RightPanel.h"

#include <QScrollArea>
#include <QMenu>
#include <QMessageBox>
#include <QTextEdit>

#include <Utils/Utils.h>
#include <Widgets/NotePanel/TextEditor.h>

using namespace MyNote;


RightPanel::RightPanel(QWidget *parent)
    : QWidget(parent)
    , m_pMainLayout(nullptr)
    , m_pToolBar(nullptr)
    , m_pNode(nullptr) {
    //setAttribute(Qt::WA_StyledBackground);
    //setStyleSheet("background-color: gray;");
    setupUI();
    setupSignal();
}

RightPanel::~RightPanel() {
    qDebug() << "~RightPanel" << Qt::endl;
    SAFE_DELETE(m_pMainLayout);
}

void RightPanel::setupUI() {
    m_pMainLayout = new QVBoxLayout(this);
    m_pMainLayout->setContentsMargins(0, 0, 0, 0);
    m_pMainLayout->setAlignment(Qt::AlignTop);

    setLayout(m_pMainLayout);
}

void RightPanel::setupSignal() {
}

void RightPanel::clear() {
    QLayoutItem *item;
    while ((item = m_pMainLayout->takeAt(0)) != nullptr) {
        delete item->widget(); // 删除组件
        delete item; // 删除布局项
    }
}

void RightPanel::buildLayout(Node *node) {
    if (node == nullptr) {
        return;
    }

    // 根据Node中block的类型，创建对应的Widget

    auto blocks = node->getBlocks();
    m_pNode = node;

    for (auto block : blocks) {
        if (block.empty()) {
            continue ;
        }

        Block *b = block[0];
        if (b == nullptr) {
            continue ;
        }

        NoteEditor *editor = new NoteEditor(this, b);
        connect(editor, &NoteEditor::signalHeightChanged, this, &RightPanel::onAdjustHeight);
        m_pMainLayout->addWidget(editor);
        onAdjustHeight();
    }

}

void RightPanel::Save() {
    m_pNode->Save();
}

void RightPanel::onAdjustHeight() {

    int panelNewHeight = 0;
    int panelCurrHeight = height();

    for (int i = 0; i < m_pMainLayout->count(); ++i) {
        QLayoutItem *item = m_pMainLayout->itemAt(i);

        if (item->widget()) {
            QWidget *widget = item->widget();
            NoteEditor *editor = qobject_cast<NoteEditor*>(widget);
            panelNewHeight += editor->getHeight();
        }
    }

    if (panelNewHeight != panelCurrHeight) {
        setFixedHeight(panelNewHeight);
    }
}
