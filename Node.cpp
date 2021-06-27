#include "Node.h"

namespace gnote {

Node::Node(const QString &dir)
    : m_sNodeDir(dir) {
}
Node::~Node() {}

void Node::addChild(QSharedPointer<Node> node) {
    m_pChilds.append(node);
}

}
