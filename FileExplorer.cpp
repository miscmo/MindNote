#include "FileExplorer.h"

#include <MainWindow.h>

#include <QWidget>

namespace gnote {

FileExplorer *FileExplorer::getInstance() {
    static FileExplorer fileExplorer(MainWindow::getInstance());
    return &fileExplorer;
}

FileExplorer::FileExplorer(QWidget *parent)
    :QWidget(parent) {

}

FileExplorer::~FileExplorer() {

}

}
