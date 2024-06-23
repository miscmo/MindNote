#include "NoteHighlighter.h"

#include <QTextCharFormat>
#include <QRegularExpression>
#include <QTextDocument>
#include <QTextLayout>

#include <Widgets/Highlighter/peg-markdown-highlight/pmh_parser.h>.h>


using namespace MyNote;


NoteHighlighter::NoteHighlighter(QTextDocument *document)
: QSyntaxHighlighter(document)
    , m_pWorkThread(new HighlighterThread(this)){

    connect(m_pWorkThread, &HighlighterThread::signalResultReady,
            this, &NoteHighlighter::onResultReady);

    m_pWorkThread->start();
}

NoteHighlighter::~NoteHighlighter()
{
    // stop background worker thread
    m_pWorkThread->enqueue(QString());
    m_pWorkThread->wait();
    delete m_pWorkThread;
}

void NoteHighlighter::reset()
{
    m_sPrevText.clear();
}

void NoteHighlighter::setStyles(const QVector<HighlightingStyle> &styles)
{
    m_vStyles = styles;
    reset();
}


void NoteHighlighter::highlightBlock(const QString &textBlock) {
    if (document()->isEmpty()) {
        return;
    }

    QString text = document()->toPlainText();

    // document changed since last call?
    if (text == m_sPrevText) {
        return;
    }

    unsigned long offset = 0;

    m_pWorkThread->enqueue(text, offset);

    m_sPrevText = text;

}

void NoteHighlighter::applyFormat(unsigned long pos, unsigned long end,
                                      QTextCharFormat format, bool merge)
{
    // The QTextDocument contains an additional single paragraph separator (unicode 0x2029).
    // https://bugreports.qt-project.org/browse/QTBUG-4841
    unsigned long max_offset = document()->characterCount() - 1;

    if (end <= pos || max_offset < pos) {
        return;
    }

    if (max_offset < end) {
        end = max_offset;
    }

    // "The QTextLayout object can only be modified from the
    // documentChanged implementation of a QAbstractTextDocumentLayout
    // subclass. Any changes applied from the outside cause undefined
    // behavior." -- we are breaking this rule here. There might be
    // a better (more correct) way to do this.

    int startBlockNum = document()->findBlock(pos).blockNumber();
    int endBlockNum = document()->findBlock(end).blockNumber();
    for (int j = startBlockNum; j <= endBlockNum; j++)
    {
        QTextBlock block = document()->findBlockByNumber(j);

        QTextLayout *layout = block.layout();
        int blockpos = block.position();
        QTextLayout::FormatRange r;
        r.format = format;
        QList<QTextLayout::FormatRange> list;
        if (merge) {
            list = layout->formats();
        }

        if (j == startBlockNum) {
            r.start = pos - blockpos;
            r.length = (startBlockNum == endBlockNum)
                        ? end - pos
                        : block.length() - r.start;
        } else if (j == endBlockNum) {
            r.start = 0;
            r.length = end - blockpos;
        } else {
            r.start = 0;
            r.length = block.length();
        }

        list.append(r);
        layout->setFormats(list);
    }
}


void NoteHighlighter::onResultReady(pmh_element **elements, unsigned long base_offset)
{
    if (!elements) {
        qDebug() << "elements is null";
        return;
    }

    // clear any format before base_offset
    if (base_offset > 0) {
        applyFormat(0, base_offset - 1, QTextCharFormat(), false);
    }

    // apply highlight results
    for (int i = 0; i < m_vStyles.size(); i++) {
        HighlightingStyle style = m_vStyles.at(i);
        pmh_element *elem_cursor = elements[style.type];
        while (elem_cursor != NULL) {
            unsigned long pos = elem_cursor->pos + base_offset;
            unsigned long end = elem_cursor->end + base_offset;

            QTextCharFormat format = style.format;
            if (/*_makeLinksClickable
                &&*/ (elem_cursor->type == pmh_LINK
                    || elem_cursor->type == pmh_AUTO_LINK_URL
                    || elem_cursor->type == pmh_AUTO_LINK_EMAIL
                    || elem_cursor->type == pmh_REFERENCE)
                && elem_cursor->address != NULL)
            {
                QString address(elem_cursor->address);
                if (elem_cursor->type == pmh_AUTO_LINK_EMAIL && !address.startsWith("mailto:"))
                    address = "mailto:" + address;
                format.setAnchor(true);
                format.setAnchorHref(address);
                format.setToolTip(address);
            }
            applyFormat(pos, end, format, true);

            elem_cursor = elem_cursor->next;
        }
    }

    // mark complete document as dirty
    document()->markContentsDirty(0, document()->characterCount());

    // free highlighting elements
    pmh_free_elements(elements);
}
