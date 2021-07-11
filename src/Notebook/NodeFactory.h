#ifndef NODEFACTORY_H
#define NODEFACTORY_H

#include <QString>

namespace MyNote {

class Node;

class NodeFactory {
public:
    ~NodeFactory() {}
    static Node *createNode(const QString &path);

private:
    NodeFactory() {}
};

}

#endif // NODEFACTORY_H
