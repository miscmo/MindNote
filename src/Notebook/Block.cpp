#include "Block.h"

using namespace MyNote;

Block::Block() {

}

Block::~Block() {


}

void Block::setType(QString type) {
    m_sType = type;
}

void Block::setContent(QString content) {
    m_sContent = content;
}