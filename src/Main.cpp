#include <Config/Config.h>
#include <Widgets/MainWindow.h>
#include <Model/DBMgr.h>

#include <QApplication>
#include <QTranslator>
#include <QSqlDatabase>

using namespace MyNote;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/Res/mindnote_icon.png"));

    QStringList drivers = QSqlDatabase::drivers();
    foreach (QString d, drivers) {
        qDebug() << d;
    }

    DBMgr *db = DBMgr::GetInstance();
    db->InitDB();
    db->Open();

    User user;
    user.Name = "miscom";
    user.Passwd = "142995";
    user.Avatar = "todo";

    int addret = db->UserAdd(&user);
    if (addret == -1) {
        qDebug() << "user add failed" << user.Name << Qt::endl;
    }

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
