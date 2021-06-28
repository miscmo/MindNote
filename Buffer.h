#ifndef BUFFER_H
#define BUFFER_H

#include <QFile>

namespace gnote {

class Buffer {
public:
    Buffer(const QString &path);
    ~Buffer();

    QByteArray read();
    void write(const QByteArray &ctx);

private:
    QFile *m_pfile;
    QByteArray m_dContent;
};

}

#endif // BUFFER_H
