#include "NotePanel.h"

#include <MyNote.h>
#include <Widgets/MainWindow.h>
#include <Notebook/NotebookManager.h>
#include <Widgets/NoteEditor.h>

#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QInputDialog>
#include <QMenu>
#include <QMessageBox>

using namespace MyNote;


NotePanel *NotePanel::m_pInstance = nullptr;

NotePanel *NotePanel::getInstance() {
    if (m_pInstance == nullptr) {
        m_pInstance = new NotePanel(MyNote::getInstance()->GetMainWindow());
    }

    return m_pInstance;
}

NotePanel::NotePanel(QWidget *parent)
    : QWidget(parent) {
        m_pMainLayout = new QGridLayout(this);

        QScrollArea *scrollArea = new QScrollArea(this);
        scrollArea->setWidgetResizable(true);

        m_pContentWidget = NoteEditor::getInstance();

        //contentLayout = new QVBoxLayout(m_pContentWidget);
        scrollArea->setWidget(m_pContentWidget);

        m_pMainLayout->addWidget(scrollArea);

        QPushButton *addButton = new QPushButton("Add Note Block", this);
        m_pMainLayout->addWidget(addButton);

        // 实现点击addButton之后，弹出菜单选择笔记块类型
        connect(addButton, &QPushButton::clicked, this, &NotePanel::showBlockSelectMenu);


}

NotePanel::~NotePanel() {
    qDebug() << "~NodePanel" << Qt::endl;
}

void NotePanel::setupSignal() {

    connect(NoteMgr::GetInstance(), &NoteMgr::signalCurNodeChanged,
            this, &NotePanel::onCurrentNodeChanged);
}

void NotePanel::setupUI() {

}

void NotePanel::onCurrentNodeChanged(Node *node) {
    // 清空当前所有的noteblock块
    if (m_pNode == node) {
        return ;
    }

    clear();

    m_pNode = node;

    reload();
}

// 清空当前panel中所有的已绘制的块
void NotePanel::clear() {

}

// 重新加载Node笔记
void NotePanel::reload() {

}

void NotePanel::showBlockSelectMenu() {
    // Create a menu and add actions
    QMenu menu(this);
    QAction *textBlockAction = menu.addAction(tr("plain text block"));
    QAction *mdBlockAction = menu.addAction("markdown block");
    QAction *flowChartAction = menu.addAction("flow chart block");

    // Connect the actions to slots
    connect(textBlockAction, &QAction::triggered, this, []() {
        QMessageBox::information(nullptr, "Menu Action", "plain text block selected");
    });
    connect(mdBlockAction, &QAction::triggered, this, []() {
        QMessageBox::information(nullptr, "Menu Action", "markdown block selected");
    });
    connect(flowChartAction, &QAction::triggered, this, []() {
        QMessageBox::information(nullptr, "Menu Action", "flow chart block selected");
    });

    // Get the position of the button and show the menu there
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) {
        QPoint pos = button->mapToGlobal(QPoint(0, button->height()));
        menu.exec(pos);
    }

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

