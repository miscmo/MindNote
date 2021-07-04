#include "Utils.h"

#include <QFile>
#include <QDir>

namespace MyNote {
QByteArray Utils::File::read(QString filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        return QByteArray();
    }

    QByteArray ctx =  file.readAll();
    file.close();
    return ctx;
}

void Utils::File::write(QString filename, QByteArray ctx) {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        return ;
    }

    file.write(ctx);
    file.close();
}

QStringList Utils::listNode(const QString &path) {
    QDir dir(path);
    QStringList nameFilter = { ".", "..", NODE_IMG_DIR };
    QDir::Filters filter = QDir::AllDirs | QDir::NoDotAndDotDot | QDir::NoSymLinks;
    return dir.entryList(nameFilter, filter);
}
}
