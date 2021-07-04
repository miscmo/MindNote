#include <Config/Config.h>
#include <Widgets/MainWindow.h>

#include <QApplication>

using namespace MyNote;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow mainWindow;
    mainWindow.init();
    mainWindow.show();

    return a.exec();
}
