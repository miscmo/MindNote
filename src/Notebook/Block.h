#ifndef BLOCK_H
#define BLOCK_H

#include <QString>

namespace MyNote {

// Block 类型
#define BLOCK_TYPE_TEXT "text"
#define BLOCK_TYPE_MARKDOWN  "markdown"
#define BLOCK_TYPE_HTML "html"
#define BLOCK_TYPE_FLOWCHART "FLOWCHART"

// Block 内容类型
#define BLOCK_CONTENT_TYPE_TEXT "text"
#define BLOCK_CONTENT_TYPE_LOCALFILE "localfile"
#define BLOCK_CONTENT_TYPE_URL "url"

class Block {

public:
    Block(QString type, QString content, QString contentType);
    ~Block();

    // getter and setter
    void setType(QString type);
    void setContent(QString content, QString contentType);

    QString getType() { return m_sType; }
    QString getContent() { return m_sContent; }
    QString getContentType() { return m_sContentType; }

signals:
    void signalContentChanged();
    void signalSaveStatusChanged();

private:
    bool m_bNeedSave;
    QString m_sType;
    QString m_sContent;
    QString m_sContentType;
};

};

#endif // BLOCK_H
