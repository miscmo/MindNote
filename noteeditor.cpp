#include "noteeditor.h"

#include <utils.h>
#include <MainWindow.h>

#include <QWidget>
#include <QTextEdit>
#include <QTreeWidgetItem>
#include <QVBoxLayout>

namespace gnote {

NoteEditor *NoteEditor::getInstance() {
   static NoteEditor noteEditor(MainWindow::getInstance());
   return &noteEditor;
}

NoteEditor::NoteEditor(QWidget *parent)
    : QWidget(parent) {
    initUi();

    setupSignal();
}

NoteEditor::~NoteEditor() {
    delete m_pTextEdit;
}

void NoteEditor::initUi() {
    m_pMainLayout = new QVBoxLayout(this);
    m_pMainLayout->setContentsMargins(0, 0, 0, 0);

    m_pTextEdit = new QTextEdit(this);

    m_pMainLayout->addWidget(m_pTextEdit);
}

void NoteEditor::setupUi() {
    //setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //m_pTextEdit->setGeometry(0, 0, this->width(), this->height());
}

void NoteEditor::setupSignal() {
}

void NoteEditor::handleItemClicked(QTreeWidgetItem *item, int column) {
    QString path = item->text(0) + "/" + "defnote.md";

    QByteArray ctx = Utils::File::read(path);

    m_pTextEdit->setText(QString(ctx));
}

}
