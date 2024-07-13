#include "NoteEditor.h"

#include <Notebook/Block.h>
#include <Widgets/NotePanel/TextEditor.h>
#include <Widgets/NotePanel/MarkdownEditor.h>>

#include <QVBoxLayout>

using namespace MyNote;


NoteEditor::NoteEditor(QWidget *parent, Block *block)
    : QWidget(parent)
    , m_pBlock(block) {
    initUi();
    setupSignal();
}

NoteEditor::~NoteEditor() {

}

void NoteEditor::initUi() {

    if (m_pBlock == nullptr) {
        return ;
    }

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // todo 这里后面改成工厂模式
    if (m_pBlock->getType() == BLOCK_TYPE_TEXT) {
        TextEditor *editor = new TextEditor(this, m_pBlock);
        connect(editor, &TextEditor::signalHeightChanged, this, &NoteEditor::signalHeightChanged);
        mainLayout->addWidget(editor);
        m_pEditor = editor;
    } else if (m_pBlock->getType() == BLOCK_TYPE_MARKDOWN) {
        MarkdownEditor *editor = new MarkdownEditor(this, m_pBlock);
        connect(editor, &MarkdownEditor::signalHeightChanged, this, &NoteEditor::signalHeightChanged);
        mainLayout->addWidget(editor);
        m_pEditor = editor;
    } else {
        qDebug() << "NoteEditor::initUi: unknown block type";
    }

    setLayout(mainLayout);
}

void NoteEditor::setupSignal() {

    // todo 订阅block的信号
}

int NoteEditor::getHeight() {
    return m_pEditor->getHeight();
}

Error NoteEditor::save() {
    return m_pEditor->save();
}
