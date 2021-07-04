#include "NoteEditor.h"

#include "MainWindow.h"

#include <MyNote.h>
#include <Utils/Utils.h>
#include <Notebook/BufferManager.h>
#include <Notebook/Buffer.h>

#include <QWidget>
#include <QTextEdit>
#include <QTreeWidgetItem>
#include <QVBoxLayout>

#include <QDebug>

namespace MyNote {

NoteEditor *NoteEditor::m_pInstance = nullptr;

NoteEditor *NoteEditor::getInstance() {
    if (m_pInstance == nullptr) {
        m_pInstance = new NoteEditor(MyNote::getInstance()->getMainWindow());
    }

    return m_pInstance;
}

NoteEditor::~NoteEditor() {
    qDebug() << "~NodeEditor" << endl;
}

NoteEditor::NoteEditor(QWidget *parent)
    : QWidget(parent) {

    initUi();

    setupSignal();
}

QString NoteEditor::getText() {
    return m_pTextEdit->toPlainText();
}

void NoteEditor::initUi() {
    m_pMainLayout = new QVBoxLayout(this);
    m_pMainLayout->setContentsMargins(0, 0, 0, 0);

    m_pTextEdit = new QTextEdit(this);

    m_pMainLayout->addWidget(m_pTextEdit);
}

void NoteEditor::setupUi() {
}

void NoteEditor::setupSignal() {
    connect(BufferManager::getInstance(), &BufferManager::currentBufferChanged,
            this, &NoteEditor::onCurBufferChanged);
}

void NoteEditor::onCurBufferChanged(Buffer *buffer) {
    m_pTextEdit->setText(buffer->read());
}

}
