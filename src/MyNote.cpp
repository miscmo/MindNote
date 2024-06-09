#include "MyNote.h"

#include <Widgets/MainWindow.h>
#include <Widgets/NoteEditor.h>
#include <Widgets/NoteExplorer.h>
#include <Widgets/FileExplorer.h>

namespace MyNote {

MyNote::MyNote(QObject *parent)
    : QObject(parent)
    , m_pMainWindow(nullptr) {
}

MyNote::~MyNote() {
    m_pMainWindow = nullptr;
}

void MyNote::SetMainWindow(MainWindow *mainWindow) {
    if (!m_pMainWindow)	{
        m_pMainWindow = mainWindow;
    }
}

}
