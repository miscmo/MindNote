#include "FileExplorer.h"

#include <MainWindow.h>

#include <QWidget>
#include <QDebug>

namespace gnote {

FileExplorer *FileExplorer::m_pInstance = nullptr;

FileExplorer *FileExplorer::getInstance() {
    if (m_pInstance == nullptr) {
        m_pInstance = new FileExplorer(MainWindow::getInstance());
    }
    return m_pInstance;
}

FileExplorer::FileExplorer(QWidget *parent)
    :QWidget(parent) {

}

FileExplorer::~FileExplorer() {
    qDebug() << "~FileExplorer" << endl;
}

}
