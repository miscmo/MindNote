#include "Buffer.h"

namespace gnote {

Buffer::Buffer(const QString &path) {
    m_pfile = new QFile(path);
    if (!m_pfile->open(QIODevice::ReadWrite | QIODevice::ExistingOnly)) {
        return ;
    }
}

Buffer::~Buffer() {
    m_pfile->close();
    m_pfile = nullptr;
}

QByteArray Buffer::read() {
    if (m_dContent.isEmpty() && m_pfile) {
        m_dContent = m_pfile->readAll();
    }

    return m_dContent;
}

void Buffer::write(const QByteArray &ctx) {
    m_dContent = ctx;

    m_pfile->write(m_dContent);
}

}
