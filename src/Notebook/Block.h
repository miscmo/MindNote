#ifndef BLOCK_H
#define BLOCK_H

#include <QString>

namespace MyNote {

class Block {

public:
    Block();
    ~Block();

private:
    QString m_sType;
    QString m_sContent;
    QString m_sContentType;

};

};

#endif // BLOCK_H
