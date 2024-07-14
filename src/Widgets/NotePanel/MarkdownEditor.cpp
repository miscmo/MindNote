#include "MarkdownEditor.h"


using namespace MyNote;

MarkdownEditor::MarkdownEditor(QWidget *parent, Block *block)
    : QTextEdit(parent) {
    //initUi();
    //setupSignal();
}

MarkdownEditor::~MarkdownEditor() {
}

void MarkdownEditor::init() {
    initUi();
    setupSignal();
}

void MarkdownEditor::initUi() {
    setFrameStyle(QFrame::NoFrame);

}

void MarkdownEditor::setupSignal() {

}



int MarkdownEditor::adjustHeight() {
    // 自适应大小
    // 获取文本文档
    QTextDocument *doc = document();

    int contentHeight = doc->size().toSize().height();

    // 计算新的高度
    int newHeight = contentHeight + 10;  // 10 是一个合理的边距，用于显示文本光标

    int currentHeight = getHeight();

    // 仅在高度需要改变时才进行调整
    if (currentHeight != newHeight) {
        QTextEdit::setFixedHeight(newHeight);
        // 更新滚动区域的总高度
        //updateScrollAreaHeight();
        emit signalHeightChanged(newHeight);
    }

    return newHeight;
}

int MarkdownEditor::getHeight() {
    return height();
}

Error MarkdownEditor::save() {
    return Error::success();
}
