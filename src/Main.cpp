#include <Config/Config.h>
#include <Widgets/MainWindow.h>

#include <QApplication>
#include <QTranslator>

using namespace MyNote;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;

    translator.load(":/cn.qm");
    a.installTranslator(&translator);

    MainWindow mainWindow;
    mainWindow.init();
    mainWindow.show();


    return a.exec();
}
