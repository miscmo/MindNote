#include "NotebookFactory.h"

#include <Notebook/Node.h>
#include <Utils/Utils.h>

using namespace MyNote;

Node *NotebookFactory::createNode(const QString &path, Node *parentNode) {
    Node *node = new Node(path, parentNode);
    if (!node->init()) {
        SAFE_DELETE(node);
        return nullptr;
    }

    return node;
}
