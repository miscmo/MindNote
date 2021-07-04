#include "BufferManager.h"

#include "Buffer.h"

#include <Widgets/NoteEditor.h>

#include <Utils/Utils.h>

#include <QDebug>
#include <QByteArray>

namespace MyNote {

BufferManager* BufferManager::getInstance() {
    static BufferManager bufferManager;
    return &bufferManager;
}

BufferManager::BufferManager()
    : QObject()
    , m_pBufferHash(nullptr)
    , m_pCurrentBuffer(nullptr) {
    m_pBufferHash = new QHash<QString, Buffer *>();
}

Buffer *BufferManager::getBuffer(const QString &path) {
    BUFFER_HASH_TYPE::const_iterator it = m_pBufferHash->find(path);
    if (m_pBufferHash->end() == it) {
        Buffer *newBuffer = new Buffer(path);
        m_pBufferHash->insert(path, newBuffer);
        return newBuffer;
    }

    return it.value();
}

void BufferManager::saveBuffer() {
    NoteEditor *editor = NoteEditor::getInstance();

    QString text = editor->getText();

    m_pCurrentBuffer->write(QByteArray().append(text));
}

void BufferManager::setCurrentBuffer(const QString &path) {
    m_pCurrentBuffer = getBuffer(path);

    emit currentBufferChanged(m_pCurrentBuffer);
}


BufferManager::~BufferManager() {
    qDebug() << "~BufferManager()" << endl;
    SAFE_DELETE(m_pBufferHash);
    m_pCurrentBuffer = nullptr;
}

}
