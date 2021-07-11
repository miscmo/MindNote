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
    qDebug() << "~Buffer" << endl;
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
    in.setCodec("UTF-8");

    m_dContent = QByteArray().append(in.readAll());

    file->close();

    return m_dContent;
}

void Buffer::write(const QByteArray &ctx) {
    QFile *file = openMD();
    if (nullptr == file) {
        qDebug() << "write failed, notebook " << m_sPath << "cannot open." << endl;
        return ;
    }

    QTextStream out(file);
    out.setCodec("UTF-8");

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
