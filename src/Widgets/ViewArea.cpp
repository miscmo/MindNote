#include "ViewArea.h"

#include "NoteEditor.h"
#include "MainWindow.h"

#include <MyNote.h>
#include <Utils/Utils.h>

#include <QVBoxLayout>
#include <QDebug>

namespace MyNote {

ViewArea *ViewArea::m_pInstance = nullptr;
ViewArea *ViewArea::getInstance() {
    if (m_pInstance == nullptr) {
        m_pInstance = new ViewArea(MyNote::getInstance()->GetMainWindow());

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
    qDebug() << "~ViewArea" << Qt::endl;
    SAFE_DELETE(m_pMainLayout);
}

}
