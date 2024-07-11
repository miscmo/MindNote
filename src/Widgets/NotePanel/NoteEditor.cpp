#include "NoteEditor.h"

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

}

void NoteEditor::setupSignal() {

    // todo 订阅block的信号

}

int NoteEditor::getHeight() {
    return height();
}

int NoteEditor::autoAdjustHeight() {
    return height();
}

Error NoteEditor::save() {
    return Error::success();
}
