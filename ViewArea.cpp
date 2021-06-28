#include "ViewArea.h"

#include <noteeditor.h>
#include <MainWindow.h>
#include <utils.h>

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

    auto noteEditor = NoteEditor::getInstance();
    m_pMainLayout->addWidget(noteEditor);
}

ViewArea::~ViewArea() {
    //SAFE_DELETE(m_pMainLayout);
}

}
