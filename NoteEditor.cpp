#include "NoteEditor.h"

#include <Utils.h>
#include <MainWindow.h>
#include <BufferManager.h>
#include <Buffer.h>

#include <QWidget>
#include <QTextEdit>
#include <QTreeWidgetItem>
#include <QVBoxLayout>

#include <QDebug>

namespace gnote {

NoteEditor *NoteEditor::m_pInstance = nullptr;

NoteEditor *NoteEditor::getInstance() {
    if (m_pInstance == nullptr) {
        m_pInstance = new NoteEditor(MainWindow::getInstance());
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
