#include "NoteEditor.h"

#include "MainWindow.h"

#include <MyNote.h>
#include <Utils/Utils.h>
#include <Notebook/BufferManager.h>
#include <Notebook/Buffer.h>
#include <Notebook/NotebookManager.h>
#include <Notebook/Notebook.h>
#include <Notebook/Node.h>
#include <Config/Config.h>

#include <QWidget>
#include <QTextEdit>
#include <QTreeWidgetItem>
#include <QVBoxLayout>
#include <QPainter>
#include <QTextBlock>

#include <QDebug>

using namespace MyNote;

NoteEditor *NoteEditor::m_pInstance = nullptr;

NoteEditor *NoteEditor::getInstance() {
    if (m_pInstance == nullptr) {
        m_pInstance = new NoteEditor(MyNote::getInstance()->getMainWindow());
    }

    return m_pInstance;
}

NoteEditor::~NoteEditor() {
    qDebug() << "~NodeEditor" << Qt::endl;
    Config::getInstance()->set(CONF_FONT_KEY, QVariant(getCurFont().toString()));
}

NoteEditor::NoteEditor(QWidget *parent)
    : QPlainTextEdit(parent) {
    initUi();

    setupSignal();
}

QString NoteEditor::getText() {
    return toPlainText();
}

void NoteEditor::initUi() {
    QFont defFont("Courier New", 12);
    QString fontString = Config::getInstance()->get(CONF_FONT_KEY, QVariant(defFont.toString())).toString();
    QFont initFont;
    bool init = initFont.fromString(fontString);
    if (init) {
        setCurFont(initFont);
    } else {
        setCurFont(defFont);
    }

    m_pLineNumberArea = new LineNumberArea(this);

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
}

void NoteEditor::setCurFont(const QFont &font) {
    setFont(font);
}

const QFont &NoteEditor::getCurFont() {
    return font();
}

int NoteEditor::lineNumberAreaWidth() {
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

    return space;
}

void NoteEditor::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

//![slotUpdateExtraAreaWidth]

//![slotUpdateRequest]

void NoteEditor::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        m_pLineNumberArea->scroll(0, dy);
    else
        m_pLineNumberArea->update(0, rect.y(), m_pLineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

//![slotUpdateRequest]

//![resizeEvent]

void NoteEditor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    m_pLineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

//![resizeEvent]

//![cursorPositionChanged]

void NoteEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(Qt::gray).lighter(140);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

//![cursorPositionChanged]

//![extraAreaPaintEvent_0]

void NoteEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(m_pLineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);

//![extraAreaPaintEvent_0]

//![extraAreaPaintEvent_1]
    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();
//![extraAreaPaintEvent_1]

//![extraAreaPaintEvent_2]
    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, m_pLineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}

void NoteEditor::setupUi() {
}

void NoteEditor::setupSignal() {
    connect(NotebookManager::getInstance(), &NotebookManager::signalCurrentNodeChanged,
            this, &NoteEditor::onCurrentNodeChanged);

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));
}


void NoteEditor::onCurrentNodeChanged(Node *node) {
    setPlainText(node->read());
}
