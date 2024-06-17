#include "Utils.h"

#include <QFile>
#include <QDir>
#include <QDebug>
#include <QUuid>

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

// 返回文件夹下所有的文件和目录名列表
QStringList Utils::listNode(const QString &path) {
    QDir dir(path);
    QStringList nameFilter = { ".", "..", NODE_IMG_DIR };
    QDir::Filters filter = QDir::AllDirs | QDir::NoDotAndDotDot | QDir::NoSymLinks;
    return dir.entryList(nameFilter, filter);
}

QString Utils::GetUUID() {
    // 生成一个新的 UUID
    QUuid uuid = QUuid::createUuid();

    // 将 UUID 转换为不带大括号的字符串
    QString uniqueStr = uuid.toString(QUuid::WithoutBraces);

    // 去掉连字符
    uniqueStr.remove('-');

    return uniqueStr;
}
}
