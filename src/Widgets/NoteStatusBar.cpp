#include "NoteStatusBar.h"

#include <Widgets/MainWindow.h>
#include <MyNote.h>

#include <QLabel>

using namespace MyNote;

NoteStatusBar *NoteStatusBar::m_pInstance = nullptr;

NoteStatusBar *NoteStatusBar::getInstance() {
    if (!m_pInstance) {
        m_pInstance = new NoteStatusBar(MyNote::getInstance()->GetMainWindow());
    }

    return m_pInstance;
}

NoteStatusBar::NoteStatusBar(QWidget *parent)
    : QStatusBar(parent) {
    initUi();
}

NoteStatusBar::~NoteStatusBar() {
}

void NoteStatusBar::initUi() {
    QLabel *labelRight = new QLabel("right tip", this);

    addWidget(labelRight);

    QLabel *labelLeft = new QLabel("left tip", this);

    addPermanentWidget(labelLeft);
}
