#include "NodeFactory.h"

#include "Node.h"
#include "Utils/Utils.h"

namespace MyNote {

Node *NodeFactory::createNode(const QString &path) {
    Node *node = new Node(path);
    if (!node->init()) {
        SAFE_DELETE(node);
        return nullptr;
    }

    return node;
}

}
