#ifndef NOTEBOOKFACTORY_H
#define NOTEBOOKFACTORY_H

#include <QString>

namespace MyNote {

class Node;

class NotebookFactory {
public:
    static Node *createNode(const QString &path, Node *parentNode);

private:
    NotebookFactory() = delete;
};

}

#endif // NOTEBOOKFACTORY_H
