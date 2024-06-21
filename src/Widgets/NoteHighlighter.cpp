#include "NoteHighlighter.h"

#include <QTextCharFormat>
#include <QRegularExpression>


namespace MyNote {


NoteHighlighter::NoteHighlighter(QTextDocument *parent)
: QSyntaxHighlighter(parent)  {

    HighlightingRule rule;

    // Header format
    QTextCharFormat headerFormat;
    headerFormat.setFontWeight(QFont::Bold);
    headerFormat.setForeground(Qt::blue);
    rule.pattern = QRegularExpression("^#{1,6}\\s.*");
    rule.format = headerFormat;
    highlightingRules.append(rule);

    // Bold format
    QTextCharFormat boldFormat;
    boldFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression("\\*\\*.*\\*\\*");
    rule.format = boldFormat;
    highlightingRules.append(rule);

    // Italic format
    QTextCharFormat italicFormat;
    italicFormat.setFontItalic(true);
    rule.pattern = QRegularExpression("\\*[^*]+\\*");
    rule.format = italicFormat;
    highlightingRules.append(rule);

    // Code format
    QTextCharFormat codeFormat;
    codeFormat.setFontFamily("Courier");
    codeFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegularExpression("`[^`]+`");
    rule.format = codeFormat;
    highlightingRules.append(rule);

    // Link format
    QTextCharFormat linkFormat;
    linkFormat.setForeground(Qt::blue);
    linkFormat.setFontUnderline(true);
    rule.pattern = QRegularExpression("\\[.*\\]\\(.*\\)");
    rule.format = linkFormat;
    highlightingRules.append(rule);

}


void NoteHighlighter::highlightBlock(const QString &text) {
    for (const HighlightingRule &rule : qAsConst(highlightingRules)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}


}
