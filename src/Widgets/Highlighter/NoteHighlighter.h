#ifndef NOTEHIGHLIGHTER_H
#define NOTEHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QRegularExpression>

#include <Widgets/Highlighter/Definitions.h>
#include <Widgets/Highlighter/peg-markdown-highlight/pmh_definitions.h>
#include <Widgets/Highlighter/HighlighterThread.h>

namespace MyNote {

class NoteHighlighter : public QSyntaxHighlighter {
    Q_OBJECT

public:
    NoteHighlighter(QTextDocument *document = nullptr);
    ~NoteHighlighter();

    void reset();
    void setStyles(const QVector<HighlightingStyle> &styles);

protected:
    void highlightBlock(const QString &text) override;

private slots:
    void onResultReady(pmh_element **elements, unsigned long base_offset);

private:
    void applyFormat(unsigned long pos, unsigned long end, QTextCharFormat format, bool merge);

private:
    HighlighterThread *m_pWorkThread;

    QVector<HighlightingStyle> m_vStyles;
    QString m_sPrevText;


};

}

#endif // NOTEHIGHLIGHTER_H
