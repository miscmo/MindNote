#include "NotePanel.h"

#include <MyNote.h>
#include <Widgets/MainWindow.h>
#include <Notebook/NotebookManager.h>
#include <Widgets/NotePanel/NoteEditor.h>
#include <Widgets/NotePanel/NoteWidget.h>
#include <Widgets/NotePanel/LeftPanel.h>
#include <Widgets/NotePanel/RightPanel.h>
#include <Utils/Utils.h>

#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QInputDialog>
#include <QMenu>
#include <QMessageBox>
#include <QSplitter>

using namespace MyNote;


NotePanel *NotePanel::m_pInstance = nullptr;

NotePanel *NotePanel::getInstance() {
    if (m_pInstance == nullptr) {
        m_pInstance = new NotePanel(nullptr);
    }

    return m_pInstance;
}

NotePanel::NotePanel(QWidget *parent)
    : QWidget(parent) {
    //setFixedSize(300, 400);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //setAttribute(Qt::WA_StyledBackground);
    //setStyleSheet("background-color: blue;");

    QPushButton *addBtn = new QPushButton(tr("+"), this);

    setupUI();

    setupSignal();
}

NotePanel::~NotePanel() {
    qDebug() << "~NodePanel" << Qt::endl;
}

void NotePanel::setupUI() {
    m_pMainLayout = new QVBoxLayout(this);
    m_pMainLayout->setContentsMargins(0, 0, 0, 0);

    // 创建工具栏
    m_pToolBar = new QToolBar(this);
    auto addBlockAction = new QAction(tr("Add Block"), this);
    auto refreshAction = new QAction(tr("Refresh"), this);
    m_pToolBar->addAction(addBlockAction);
    m_pToolBar->addAction(refreshAction);
    connect(addBlockAction, &QAction::triggered, this, &NotePanel::onShowBlockSelectMenu);
    connect(refreshAction, &QAction::triggered, this, &NotePanel::onRefreshLayout);

    // 将工具栏添加到 RightPanel 中，而不是布局中
    this->layout()->setMenuBar(m_pToolBar);


    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);

    //m_pLeftPanel = new LeftPanel(this);
    m_pRightPanel = new RightPanel(this);
    //m_pLeftPanel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_pRightPanel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_pRightPanel->setMinimumHeight(3000);


    scrollArea->setWidget(m_pRightPanel);

    m_pMainLayout->addWidget(scrollArea);

    setLayout(m_pMainLayout);
}

void NotePanel::setupSignal() {

    connect(NoteMgr::GetInstance(), &NoteMgr::signalCurNodeChanged,
            this, &NotePanel::onCurrentNodeChanged);
}

void NotePanel::onCurrentNodeChanged(Node *node) {
    // 清空当前所有的noteblock块
    if (m_pNode == node) {
        return ;
    }

    Error err = node->buildNode();
    if (!err.isSuccess()) {
        switch (err.code) {
        case ErrorCode::CONTENT_IS_EMPTY:
            //QMessageBox.warning(this, "笔记内容为空", err.message);
            break;
        default:
            break;
        }
    }

    clear();

    m_pNode = node;

    //reload();
    m_pRightPanel->buildLayout(m_pNode);
}

// 清空当前panel中所有的已绘制的块
void NotePanel::clear() {
    m_pRightPanel->clear();

}

// 重新加载Node笔记
void NotePanel::reload() {

}


void NotePanel::addNoteBlock() {
    // 弹出对话框选择笔记块类型
    QStringList items;
    items << "Markdown" << "PlainText" << "RichText" << "Drawing";
    bool ok;
    QString item = QInputDialog::getItem(this, tr("Select Note Block Type"),
                                         tr("Type:"), items, 0, false, &ok);
    // if (ok && !item.isEmpty()) {
    //     std::shared_ptr<NoteBlock> block;
    //     if (item == "Markdown") {
    //         block = std::make_shared<MarkdownBlock>();
    //     } else if (item == "PlainText") {
    //         block = std::make_shared<PlainTextBlock>();
    //     } else if (item == "RichText") {
    //         block = std::make_shared<RichTextBlock>();
    //     } else if (item == "Drawing") {
    //         block = std::make_shared<DrawingBlock>();
    //     }

    //     if (block) {
    //         noteBlocks.push_back(block);
    //         QWidget *editor = block->getEditor();
    //         contentLayout->addWidget(editor);
    //     }
    // }
}


void NotePanel::onShowBlockSelectMenu() {
    // Create a menu and add actions
    QMenu addMenu(this);
    QAction *textBlockAction = addMenu.addAction(tr("plain text block"));
    QAction *mdBlockAction = addMenu.addAction("markdown block");
    QAction *flowChartAction = addMenu.addAction("flow chart block");

    connect(&addMenu, &QMenu::triggered, this, &NotePanel::onAddBlock);

    // Get the position of the button and show the menu there
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) {
        QPoint pos = button->mapToGlobal(QPoint(0, button->height()));
        addMenu.exec(pos);
    }
}

void NotePanel::onAddBlock(QAction *action) {
    QMessageBox::information(nullptr, tr("Add Block"), action->text());
}

void NotePanel::onRefreshLayout() {
    //m_pRightPanel->update();
}
