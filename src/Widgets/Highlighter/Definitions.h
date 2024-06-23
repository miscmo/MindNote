#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include "peg-markdown-highlight/pmh_definitions.h"
#include <QtGui/QTextCharFormat>

namespace MyNote {


struct HighlightingStyle
{
    pmh_element_type type;
    QTextCharFormat format;
};

}

#endif // DEFINITIONS_H
