#ifndef BUFFER_H
#define BUFFER_H

#include <QFile>
#include <QDir>

namespace gnote {

class Buffer {
public:
    Buffer(const QString &path);
    ~Buffer();

    QByteArray read();
    void write(const QByteArray &ctx);

    QString getName();

private:
    QFile *m_pFile;
    QDir *m_pDir;
    QByteArray m_dContent;
};

}

#endif // BUFFER_H
