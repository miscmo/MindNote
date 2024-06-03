#include <Config/Config.h>
#include <Widgets/MainWindow.h>

#include <QApplication>
#include <QTranslator>

using namespace MyNote;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;

    if (translator.load(":/cn.qm")) {
        qDebug() << "translator load succ\n";
    } else {
        qWarning() << "translator load failed\n";
    }
    a.installTranslator(&translator);

    MainWindow mainWindow;
    mainWindow.init();
    mainWindow.show();


    return a.exec();
}
