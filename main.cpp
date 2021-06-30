#include "MainWindow.h"
#include <Config.h>

#include <QApplication>

using namespace gnote;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow * mainWindow = MainWindow::getInstance();
    mainWindow->init();
    mainWindow->show();

    return a.exec();
}
