#include "Buffer.h"

#include <Utils/Utils.h>

#include <QDebug>

namespace MyNote {

#define MD_FILE "defnote.md"

Buffer::Buffer(const QString &path) {
    Q_ASSERT(!path.isEmpty());

    m_sPath = path;
}

Buffer::~Buffer() {
    qDebug() << "~Buffer" << Qt::endl;
}

QByteArray Buffer::read() {
    if (!m_dContent.isEmpty()) {
        return m_dContent;
    }

    QFile *file = openMD();
    if (nullptr == file) {
        return QByteArray("");
    }

    QTextStream in(file);
    in.setEncoding(QStringConverter::Utf8);

    // 避免直接readAll，文件太大时会出问题
    m_dContent = QByteArray().append(in.readAll().toUtf8());

    file->close();

    return m_dContent;
}

void Buffer::write(const QByteArray &ctx) {
    QFile *file = openMD();
    if (nullptr == file) {
        qDebug() << "write failed, notebook " << m_sPath << "cannot open." << Qt::endl;
        return ;
    }

    QTextStream out(file);
    out.setEncoding(QStringConverter::Utf8);

    out << ctx;
    m_dContent = ctx;

    file->close();

    return ;
}

QString Buffer::getName() {
    return m_sPath;
}

QFile *Buffer::openMD() {
    QFile *file = new QFile(m_sPath + "/" + MD_FILE);
    if (file && file->open(QIODevice::ReadWrite)) {
        return file;
    }

    SAFE_DELETE(file);
    return nullptr;
}


}
