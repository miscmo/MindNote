#ifndef BUFFERMANAGER_H
#define BUFFERMANAGER_H

#include <QHash>
#include <QString>

namespace gnote {

class Buffer;

using BUFFER_HASH_TYPE = QHash<QString, Buffer *>;

class BufferManager {
public:
    static BufferManager *getInstance();
    ~BufferManager();

    Buffer *getBuffer(const QString &path);

private:
    BufferManager();

private:
    BUFFER_HASH_TYPE *m_pBufferHash;
    QString m_sCurrentBuffer;
};

}

#endif // BUFFERMANAGER_H
