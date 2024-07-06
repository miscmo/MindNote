#include "Block.h"

using namespace MyNote;

Block::Block(QString type, QString content, QString contentType)
    : m_bNeedSave(false)
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
