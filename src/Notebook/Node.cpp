#include "Node.h"

#include <QDebug>
#include <QDir>

namespace MyNote {

Node::Node(const QString &dir)
    : m_sNodeDir(dir) {
}

Node::~Node() {
    qDebug() << "~Node" << endl;
}

bool Node::init() {
    QDir dir(m_sNodeDir);
    if (!dir.exists() && !dir.mkpath(dir.path())) {
        return false;
    }

    return true;
}

void Node::addChild(Node *node) {
    m_vChilds.append(node);
}

}
