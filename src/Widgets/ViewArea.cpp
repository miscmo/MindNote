#include "ViewArea.h"

#include "NoteEditor.h"
#include "MainWindow.h"

#include <MyNote.h>
#include <Utils/Utils.h>
#include <Widgets/NotePanel.h>

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
    : QWidget(parent)
    , m_pMainLayout(nullptr) {
    initUi();
}

void ViewArea::initUi() {
    //setStyleSheet("background-color: blue;");

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_pMainLayout = new QVBoxLayout(this);
    m_pMainLayout->setContentsMargins(0, 0, 0, 0);

    //auto noteEditor = NoteEditor::getInstance();
    //m_pMainLayout->addWidget(noteEditor);

    auto notePanel = NotePanel::getInstance();
    m_pMainLayout->addWidget(notePanel);
}

ViewArea::~ViewArea() {
    qDebug() << "~ViewArea" << Qt::endl;
    SAFE_DELETE(m_pMainLayout);
}

}
