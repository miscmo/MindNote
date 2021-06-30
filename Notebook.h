#ifndef NOTEBOOK_H
#define NOTEBOOK_H

#include <Node.h>

#include <QVector>
#include <QSharedPointer>

namespace gnote {

class Notebook {

public:
    Notebook();
    ~Notebook();

    QSharedPointer<Node> getRootNode() const {return m_pRoot;}

    void resetDir(const QString &path);

    QString getPath() const {return m_sPath;}

private:
    void initNote();
    void loadNode(QSharedPointer<Node> node, const QString &path);

private:
    QSharedPointer<Node> m_pRoot;
    QString m_sPath;
};

}

#endif // NOTEBOOK_H
