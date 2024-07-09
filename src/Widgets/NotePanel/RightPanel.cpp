#include "RightPanel.h"

#include <QScrollArea>
#include <QMenu>
#include <QMessageBox>
#include <QTextEdit>

#include <Utils/Utils.h>
#include <Widgets/NotePanel/NoteEditor.h>

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

    // auto scrollWidget = new QWidget(this);
    // auto scrollLayout = new QVBoxLayout(scrollWidget);
    // scrollWidget->setLayout(scrollLayout);

    // scrollLayout->addWidget(NoteEditor::getInstance());
    // auto textEditor = new QTextEdit(this);
    // textEditor->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // textEditor->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // // 调整 QTextEdit 的大小策略
    // textEditor->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    // textEditor->setMinimumHeight(200); // 设置一个合理的最小高度，以便内容可以完全展示

    // scrollLayout->addWidget(textEditor);

    //auto m_pScrollArea = new QScrollArea(this);
    // m_pScrollArea->setWidget(scrollWidget);
    // m_pScrollArea->setWidgetResizable(true);

    //m_pMainLayout->addWidget(NoteEditor::getInstance());

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

        if (b->getType() == BLOCK_TYPE_TEXT) {

            auto mdBlock = new NoteEditor(this, b);
            m_pEditor = mdBlock;

            connect(mdBlock, &NoteEditor::signalHeightChanged, this, &RightPanel::onAdjustHeight);

            m_pMainLayout->addWidget(mdBlock);

            onAdjustHeight();

        } else if (b->getType() == BLOCK_TYPE_TEXT) {

                auto textBlock = new QTextEdit(this);
                textBlock->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
                textBlock->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

                // 调整 QTextEdit 的大小策略
                textBlock->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
                textBlock->setMinimumHeight(200); // 设置一个合理的最小高度，以便内容可以完全展示

                textBlock->setText(b->getContent());
                m_pMainLayout->addWidget(textBlock);

        } else {

        }
    }

}

void RightPanel::Save() {
    m_pNode->Save();
}

void RightPanel::onAdjustHeight() {
    setFixedHeight(m_pEditor->GetHeight());
}
