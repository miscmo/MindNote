#ifndef NODE_H
#define NODE_H

#include <QVector>
#include <QSharedPointer>
#include <QString>
#include <QByteArray>
#include <QJsonObject>
#include <Utils/Errors.h>
#include <Notebook/Block.h>

namespace MyNote {

class Buffer;
class Note;

class Node : public QObject {
    Q_OBJECT
public:
    Node(Note *note, Node *parentNode = nullptr);
    ~Node();

    // getter and setter
    Note *getNote();
    QString getID();
    QString getTitle();
    void setTitle(QString title) {m_sTitle = title;};

    bool isDel() {return m_bIsDel;};
    void setDel(bool isDel);

    void setLastEditPos(int pos) {m_bLastEditPos = pos;}
    int getLastEditPos() {return m_bLastEditPos;}

    void setLastVScrollPos(int v){ m_bLastVScrollPos = v;}
    int getLastVScrollPos() {return m_bLastVScrollPos;}

    void setLastHScrollPos(int h) {m_bLastHScrollPos = h;}
    int getLastHScrollPos() {return m_bLastHScrollPos;}

    QString getNodeFullPath();

    bool deleteDir();
    bool deleteChild(Node *node);

    // 主要逻辑函数
    // 结点初始化，初始化标题、ID、创建时间、更新时间等信息
    bool init(QString title);

    // 以当前结点为模板，克隆一个新的结点并返回
    Node *clone();

    // 以传入的结点为模板，将传入结点内容赋值给当前结点
    Error copy(Node *node);

    // 读写笔记原始内容
    QByteArray read();
    void write(const QByteArray &ctx);
    Buffer *getBuffer();
    // 只保存当前结点内容
    int Save();
    // 保存当前结点和所有子结点
    int SaveAll();

    bool NeedSave();

    void TextChanged();

    Error saveAllBlocks();

    void buildNode();
    void rebuildNode();

    // 根据json构建Block
    Error buildBlocks(const QJsonArray &blockArr, QVector<QVector<Block*> > &blocks);

    QJsonObject toJson() const;
    // 目前看可以写成static函数
    Error fromJson(QJsonObject jsonObj);

    // 子节点管理
    void addChild(Node *node, int index = -1);
    Node *addChildByName(const QString &name, int index);
    QVector<Node *> getChilds() { return m_vChilds; }
    bool hasChild(const QString &ID);

    Node *getParentNode() { return m_pParentNode; }

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

    QVector<QVector<Block*> > m_vBlocks;

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
