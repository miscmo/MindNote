#include "Buffer.h"

#include <QDebug>

namespace MyNote {

#define MD_FILE "defnote.md"

Buffer::Buffer(const QString &path) {
    m_pDir = new QDir(path);
    m_pFile = new QFile(path + "/" + MD_FILE);
    if (!m_pFile->open(QIODevice::ReadWrite | QIODevice::ExistingOnly)) {
        return ;
    }
}

Buffer::~Buffer() {
    qDebug() << "~Buffer" << endl;
    m_pFile->close();
    m_pFile = nullptr;
}

QByteArray Buffer::read() {
    if (m_dContent.isEmpty() && m_pFile) {
        m_dContent = m_pFile->readAll();
    }

    return m_dContent;
}

QString Buffer::getName() {
    return m_pDir->dirName();
}

void Buffer::write(const QByteArray &ctx) {
    m_dContent = ctx;

    m_pFile->write(m_dContent);
}

}
