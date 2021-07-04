#ifndef BUFFERMANAGER_H
#define BUFFERMANAGER_H

#include <QHash>
#include <QString>
#include <QObject>

namespace MyNote {

class Buffer;

using BUFFER_HASH_TYPE = QHash<QString, Buffer *>;

class BufferManager : public QObject {
    Q_OBJECT
public:
    static BufferManager *getInstance();
    ~BufferManager();

    Buffer *getBuffer(const QString &path);
    void saveBuffer();

    void setCurrentBuffer(const QString &path);

signals:
    void currentBufferChanged(Buffer *buffer);

private:
    BufferManager();

private:
    BUFFER_HASH_TYPE *m_pBufferHash;
    Buffer *m_pCurrentBuffer;
};

}

#endif // BUFFERMANAGER_H
