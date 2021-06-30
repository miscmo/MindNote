#include "ViewArea.h"

#include <NoteEditor.h>
#include <MainWindow.h>
#include <Utils.h>

#include <QVBoxLayout>
#include <QDebug>

namespace gnote {

ViewArea *ViewArea::m_pInstance = nullptr;
ViewArea *ViewArea::getInstance() {
    if (m_pInstance == nullptr) {
        m_pInstance = new ViewArea(MainWindow::getInstance());

    }

    return m_pInstance;
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
    qDebug() << "~ViewArea" << endl;
}

}
