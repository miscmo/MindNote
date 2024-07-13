#include "Block.h"

#include <Notebook/Node.h>

using namespace MyNote;

Block::Block(Node *node, QString type, QString content, QString contentType)
    : m_bNeedSave(false)
    , m_pNode(node)
    , m_sType(type)
    , m_sContent(content)
    , m_sContentType(contentType) {

}

Block::~Block() {


}

void Block::setType(QString type) {
    m_sType = type;
}

void Block::setContent(QString content, QString contentType) {
    m_sContent = content;
    m_sContentType = contentType;
}

void Block::ContentChanged() {
    m_pNode->TextChanged();
}
