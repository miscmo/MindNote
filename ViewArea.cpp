#include "ViewArea.h"

#include <noteeditor.h>
#include <MainWindow.h>

#include <QVBoxLayout>

namespace gnote {

ViewArea *ViewArea::getInstance() {
    static ViewArea viewArea(MainWindow::getInstance());
    return &viewArea;
}

ViewArea::ViewArea(QWidget *parent)
    :QWidget(parent) {
    initUi();
}

void ViewArea::initUi() {
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_pMainLayout = new QVBoxLayout(this);
    m_pMainLayout->setContentsMargins(0, 0, 0, 0);

    m_pNoteEditor = NoteEditor::getInstance();
    m_pMainLayout->addWidget(m_pNoteEditor);
}

ViewArea::~ViewArea() {
    delete m_pMainLayout;
}

}
