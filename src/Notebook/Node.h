#ifndef NODE_H
#define NODE_H

#include <QVector>
#include <QSharedPointer>
#include <QString>
#include <QByteArray>
#include <QJsonObject>
#include <Utils/Errors.h>

namespace MyNote {

class Buffer;
class Note;

class Node : public QObject {
    Q_OBJECT
public:
    Node(Note *note, Node *parentNode = nullptr);
    ~Node();

    // 以当前结点为模板，克隆一个新的结点并返回
    Node *clone();

    // 以传入的结点为模板，将传入结点内容赋值给当前结点
    Error copy(Node *node);

    bool init(QString title);

    void addChild(Node *node, int index = -1);
    Node *addChildByName(const QString &name, int index);

    bool deleteDir();
    bool deleteChild(Node *node);

    bool isDel() {return m_bIsDel;};
    void setDel(bool isDel);

    QVector<Node *> getChilds() { return m_vChilds; }
    QString getID();
    QString getTitle();
    void setTitle(QString title) {m_sTitle = title;};

    Note *getNote();

    QByteArray read();
    void write(const QByteArray &ctx);

    //bool hasChildName(const QString &name);
    bool hasChild(const QString &ID);

    Buffer *getBuffer();

    Node *getParentNode() { return m_pParentNode; }

    // 只保存当前结点内容
    int Save();
    // 保存当前结点和所有子结点
    int SaveAll();

    bool NeedSave();

    void TextChanged();

    QJsonObject toJson() const;
    // 目前看可以写成static函数
    Error fromJson(QJsonObject jsonObj);

    QString getNodeFullPath();

    void setLastEditPos(int pos) {m_bLastEditPos = pos;}
    int getLastEditPos() {return m_bLastEditPos;}

    void setLastVScrollPos(int v){ m_bLastVScrollPos = v;}
    int getLastVScrollPos() {return m_bLastVScrollPos;}

    void setLastHScrollPos(int h) {m_bLastHScrollPos = h;}
    int getLastHScrollPos() {return m_bLastHScrollPos;}

signals:
    void SignalModStatusChanged(Node *node);

private:
    QString m_sID;
    QString m_sTitle;
    Note *m_pNote;		// 所属的笔记本
    QString m_sSytle;
    // todo 改成NodeFile
    QString m_sPath;
    QString m_sCreateAt;
    QString m_sUpdateAt;
    QString m_sDeleteAt;

    QVector<QVector<Block*> > m_vLayout;

    QVector<Node *> m_vChilds;
    Node *m_pParentNode;
    int m_bLastEditPos;		// 编辑位置
    int m_bLastVScrollPos;	// 编辑器竖直滚动条的位置
    int m_bLastHScrollPos;	// 编辑器水平滚动条的位置

    bool m_bIsMod;
    bool m_bIsDel;

};

}

#endif // NODE_H
