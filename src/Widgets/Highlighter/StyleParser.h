#ifndef STYLEPARSER_H
#define STYLEPARSER_H

#include "Definitions.h"
#include "peg-markdown-highlight/pmh_styleparser.h"

namespace MyNote {


class StyleParser {
public:
    explicit StyleParser(const QString& styleSheet);
    ~StyleParser();

    QVector<HighlightingStyle> highlightingStyles(QFont baseFont) const;
    QPalette editorPalette() const;

    void handleStyleParsingError(char *errorMessage, int lineNumber);

private:
    pmh_style_collection *m_pStyles;
    QList<QPair<int, QString> > m_lStyleParsingErrorList;
};

}


#endif // STYLEPARSER_H
