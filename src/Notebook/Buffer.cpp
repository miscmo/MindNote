#include "Buffer.h"

#include <Utils/Utils.h>

#include <QDebug>
#include <QFileInfo>

namespace MyNote {

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

    QFile *file = openFile();
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
    QFile *file = openFile();
    if (nullptr == file) {
        qDebug() << "write failed, notebook " << m_sPath << "cannot open." << Qt::endl;
        return ;
    }

    file->resize(0);

    QTextStream out(file);
    out.setEncoding(QStringConverter::Utf8);
    QString outContent = QString::fromUtf8(ctx);

    out << QString::fromUtf8(ctx);

    m_dContent = ctx;

    file->close();

    return ;
}

QString Buffer::getName() {
    return m_sPath;
}

QFile *Buffer::openFile() {
    QFile *file = new QFile(m_sPath);

    QDir dir;

    // 获取文件的目录路径
    QString dirPath = QFileInfo(*file).path();

    // 检查目录是否存在，如果不存在则创建
    if (!dir.exists(dirPath)) {
        if (!dir.mkpath(dirPath)) {
            qWarning() << "Failed to create directory:" << dirPath;
            return nullptr;
        }
    }

    if (!file->open(QIODevice::ReadWrite)) {
        qCritical() << "file open failed, file: " << m_sPath << "error: " << file->errorString() << Qt::endl;
        SAFE_DELETE(file);
    }

    return file;
}


}
