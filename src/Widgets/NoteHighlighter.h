#ifndef NOTEHIGHLIGHTER_H
#define NOTEHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QRegularExpression>

namespace MyNote {

class NoteHighlighter : public QSyntaxHighlighter {
    Q_OBJECT

public:
    NoteHighlighter(QTextDocument *parent = nullptr);

protected:
    void highlightBlock(const QString &text) override;

private:
    struct HighlightingRule {
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;
};

}

#endif // NOTEHIGHLIGHTER_H
