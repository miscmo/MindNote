#ifndef BLOCK_H
#define BLOCK_H

#include <QString>

namespace MyNote {

// Block 类型
#define BLOCK_TYPE_TEXT "text"
#define BLOCK_TYPE_MARKDOWN  "markdown"
#define BLOCK_TYPE_HTML "html"
#define BLOCK_TYPE_FLOWCHART "flowchart"
#define BLOCK_TYPE_IMG "image"
#define BLOCK_TYPE_AUDIO "audio"
#define BLOCK_TYPE_VIDEO "video"

// Block 内容类型
#define BLOCK_CONTENT_TYPE_TEXT "text"
#define BLOCK_CONTENT_TYPE_LOCALFILE "localfile"
#define BLOCK_CONTENT_TYPE_URL "url"

class Node;

class Block {

public:
    Block(Node *node, QString type, QString content, QString contentType);
    ~Block();

    // getter and setter
    void setType(QString type);
    void setContent(QString content, QString contentType);
    void setContentType(QString contentType) { m_sContentType = contentType; }

    Node *getNode() { return m_pNode; }
    QString getType() { return m_sType; }
    QString getContent() { return m_sContent; }
    QString getContentType() { return m_sContentType; }

    void ContentChanged();

signals:
    void signalContentChanged();
    void signalSaveStatusChanged();

private:
    bool m_bNeedSave;
    Node *m_pNode;
    QString m_sType;
    QString m_sContent;
    QString m_sContentType;
};

};

#endif // BLOCK_H
