#include "NotePanel.h"

#include <QWidget>

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
        QVBoxLayout *mainLayout = new QVBoxLayout(this);

        QScrollArea *scrollArea = new QScrollArea(this);
        scrollArea->setWidgetResizable(true);

        contentWidget = new QWidget;

        contentLayout = new QVBoxLayout(contentWidget);
        scrollArea->setWidget(contentWidget);

        mainLayout->addWidget(scrollArea);

        QPushButton *addButton = new QPushButton("Add Note Block", this);
        mainLayout->addWidget(addButton);

        connect(addButton, &QPushButton::clicked, this, &NoteComponent::addNoteBlock);

        // 添加初始行
        addNewRow();
}

void NotePanel::addNoteBlock() {
        // 弹出对话框选择笔记块类型
        QStringList items;
        items << "Markdown" << "PlainText" << "RichText" << "Drawing";
        bool ok;
        QString item = QInputDialog::getItem(this, tr("Select Note Block Type"),
                                             tr("Type:"), items, 0, false, &ok);
        if (ok && !item.isEmpty()) {
            std::shared_ptr<NoteBlock> block;
            if (item == "Markdown") {
                block = std::make_shared<MarkdownBlock>();
            } else if (item == "PlainText") {
                block = std::make_shared<PlainTextBlock>();
            } else if (item == "RichText") {
                block = std::make_shared<RichTextBlock>();
            } else if (item == "Drawing") {
                block = std::make_shared<DrawingBlock>();
            }

            if (block) {
                noteBlocks.push_back(block);
                QWidget *editor = block->getEditor();
                contentLayout->addWidget(editor);
            }
        }
}

NotePanel::~NotePanel() {
    qDebug() << "~NodePanel" << Qt::endl;
}