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
#include <Widgets/Highlighter/NoteHighlighter.h>
#include <Widgets/Highlighter/StyleParser.h>

#include <QWidget>
#include <QTextEdit>
#include <QTreeWidgetItem>
#include <QVBoxLayout>
#include <QPainter>
#include <QTextBlock>
#include <QShortcut>
#include <QScrollBar>

#include <QDebug>

using namespace MyNote;

NoteEditor *NoteEditor::m_pInstance = nullptr;

NoteEditor *NoteEditor::getInstance() {
    if (m_pInstance == nullptr) {
        m_pInstance = new NoteEditor(MyNote::getInstance()->GetMainWindow());
    }

    return m_pInstance;
}

NoteEditor::NoteEditor(QWidget *parent)
    : QPlainTextEdit(parent) {

    initUi();

    setupSignal();
}

NoteEditor::~NoteEditor() {
    qDebug() << "~NodeEditor" << Qt::endl;
    Config::getInstance()->set(CONF_FONT_KEY, QVariant(getCurFont().toString()));
}

QString NoteEditor::getText() {
    return toPlainText();
}

void NoteEditor::initUi() {
    m_pHighlighter = new NoteHighlighter(this->document());

    //loadStyleFromStylesheet(":/Res/markdown.css");
    loadStyleFromStylesheet("D:\\Code\\cloose-CuteMarkEd\\cloose-CuteMarkEd-64915b4\\app\\scripts\\highlight.js\\highlight.pack.js");
    //loadStyleFromStylesheet(":/Res/default.style");
    //loadStyleFromStylesheet(":/Res/solarized-light.style");
    loadStyleFromStylesheet(":/Res/solarized-dark-subtle.style");


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


    // 初始化快捷键
    // ctrl-s 保存
    QShortcut *saveShortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_S), this);
    connect(saveShortcut, &QShortcut::activated, NoteMgr::GetInstance(), &NoteMgr::SaveCurNode);


    // 高亮
    //NoteHighlighter *highlighter = new NoteHighlighter(document());

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

void NoteEditor::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Tab) {
        // 插入 4 个空格
        // 设置tab键为4个空格的距离
        insertPlainText("    ");
        return;  // 防止进一步处理 Tab 键
    } else if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        // 处理回车键
        QTextCursor cursor = textCursor();
        cursor.insertBlock();

        // 获取前一行的内容
        cursor.movePosition(QTextCursor::PreviousBlock);
        QString previousLineText = cursor.block().text();

        // 找到前一行开头的空白字符
        int leadingSpaces = 0;
        while (leadingSpaces < previousLineText.length() && previousLineText[leadingSpaces].isSpace()) {
            ++leadingSpaces;
        }

        // 插入相同数量的空白字符到新行
        cursor.movePosition(QTextCursor::NextBlock);
        cursor.insertText(previousLineText.left(leadingSpaces));
        setTextCursor(cursor);

        return;  // 防止进一步处理回车键
    }

    QPlainTextEdit::keyPressEvent(event);
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
    connect(NoteMgr::GetInstance(), &NoteMgr::signalCurNodeChanged,
            this, &NoteEditor::onCurrentNodeChanged);

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));
    connect(this, SIGNAL(textChanged()), this, SLOT(onTextChanged()));
    //connect(this, SIGNAL(modificationChanged(bool)), this, SLOT(onTextModify(bool)));
}


void NoteEditor::onCurrentNodeChanged(Node *node) {
    // 切换笔记前先断联笔记修改检测，防止将笔记切换误认为是用户修改内容
    disconnect(this, SIGNAL(textChanged()), this, SLOT(onTextChanged()));

    QString nodeContent = QString::fromUtf8(node->read());

    setPlainText(nodeContent);

    QTextCursor cursor = textCursor();
    cursor.setPosition(node->getLastEditPos());
    setTextCursor(cursor);

    verticalScrollBar()->setValue(node->getLastVScrollPos());
    horizontalScrollBar()->setValue(node->getLastHScrollPos());
    setFocus();

    connect(this, SIGNAL(textChanged()), this, SLOT(onTextChanged()));
}

void NoteEditor::onTextChanged() {
    qDebug() << "text changed\n";
    NoteMgr::GetInstance()->TextChanged();
}

void NoteEditor::onTextModify(bool isMod) {
    qDebug() << "text modify: " << isMod << Qt::endl;
   // NoteMgr::GetInstance()->TextChanged();
}

void NoteEditor::resetHighlighting() {
    m_pHighlighter->reset();
}

void NoteEditor::loadStyleFromStylesheet(const QString &fileName) {

    QFile f(fileName);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream ts(&f);
    QString input = ts.readAll();

    // parse the stylesheet
    StyleParser parser(input);
    QVector<HighlightingStyle> styles = parser.highlightingStyles(this->font());

    // set new style & rehighlight markdown document
    m_pHighlighter->setStyles(styles);
    m_pHighlighter->rehighlight();

    // update color palette
    this->setPalette(parser.editorPalette());
    this->viewport()->setPalette(this->palette());
}
