#include "NoteToolBar.h"

#include <MyNote.h>
#include <Widgets/MainWindow.h>

using namespace MyNote;

NoteToolBar *NoteToolBar::m_pInstance = nullptr;

NoteToolBar *NoteToolBar::getInstance() {
    if (!m_pInstance) {
        m_pInstance = new NoteToolBar(MyNote::getInstance()->getMainWindow());
    }

    return m_pInstance;
}

NoteToolBar::NoteToolBar(QWidget *parent)
    : QToolBar(parent) {
    initUi();
}

NoteToolBar::~NoteToolBar() {
}

void NoteToolBar::initUi() {
    setAllowedAreas(Qt::TopToolBarArea);
    setFloatable(false);
    setMovable(false);

    initNotebookManage();

    addSeparator();

    initNoteEdit();
}

void NoteToolBar::initNotebookManage() {
    QAction *actionNewNotebook = new QAction("newNotebook", this);

    addAction(actionNewNotebook);
}

void NoteToolBar::initNoteEdit() {
    QAction *actionSave = new QAction("Save", this);

    addAction(actionSave);
}
