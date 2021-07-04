#ifndef BUFFER_H
#define BUFFER_H

#include <QFile>
#include <QDir>

namespace MyNote {

class Buffer {
public:
    Buffer(const QString &path);
    ~Buffer();

    QByteArray read();
    void write(const QByteArray &ctx);

    QString getName();
    QFile *openMD();

private:
    QString m_sPath;
    QByteArray m_dContent;
};

}

#endif // BUFFER_H
