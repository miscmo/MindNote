#include "TextEditor.h"

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
#include <Widgets/MainWindow.h>

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

TextEditor::TextEditor(QWidget *parent, Block *block)
    : QPlainTextEdit(parent)
    , m_pBlock(block) {

    initUi();

    setupSignal();
}

TextEditor::~TextEditor() {
    qDebug() << "~NodeEditor" << Qt::endl;
    //Config::getInstance()->set(CONF_FONT_KEY, QVariant(getCurFont().toString()));
}

QString TextEditor::getText() {
    return toPlainText();
}

void TextEditor::initUi() {
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_pHighlighter = new NoteHighlighter(this->document());

    loadStyleFromStylesheet(":/Res/solarized-dark.style");

    QFont defFont("Courier New", 12);
    QString fontString = Config::getInstance()->get(CONF_FONT_KEY, QVariant(defFont.toString())).toString();
    QFont initFont;
    bool init = initFont.fromString(fontString);
    if (init) {
        setCurFont(initFont);
    } else {
        setCurFont(defFont);
    }

    disconnect(this, SIGNAL(textChanged()), this, SLOT(onTextChanged()));

    setMinimumHeight(200); // 设置一个合理的最小高度，以便内容可以完全展示
    if (m_pBlock != nullptr) {
        setPlainText(m_pBlock->getContent());
        adjustHeight();
    }

    connect(this, SIGNAL(textChanged()), this, SLOT(onTextChanged()));

    highlightCurrentLine();
}

void TextEditor::setupSignal() {
    // 暂时不显示行号
    //connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    //connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));
    connect(this, SIGNAL(textChanged()), this, SLOT(onTextChanged()));
    //connect(this, SIGNAL(modificationChanged(bool)), this, SLOT(onTextModify(bool)));
}

void TextEditor::setCurFont(const QFont &font) {
    setFont(font);
}

const QFont &TextEditor::getCurFont() {
    return font();
}

void TextEditor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    // todo:行号暂不显示
    // QRect cr = contentsRect();
    // m_pLineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void TextEditor::keyPressEvent(QKeyEvent *event) {
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

void TextEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(Qt::black).lighter(140);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void TextEditor::onTextChanged() {
    qDebug() << "text changed\n";
    //NoteMgr::GetInstance()->TextChanged();

    m_pBlock->setContent(toPlainText(), m_pBlock->getContentType());
    m_pBlock->ContentChanged();

    // 自适应大小
    adjustHeight();
}

void TextEditor::adjustHeight() {
    // 自适应大小
    // 获取文本文档
    QTextDocument *doc = document();

    // 计算文本内容的高度
    int contentHeight = 0;
    for (QTextBlock block = doc->begin(); block != doc->end(); block = block.next()) {
        // 获取当前文本块的高度
        QRectF rect = doc->documentLayout()->blockBoundingRect(block);
        contentHeight += rect.height();
    }

    // 获取当前的固定高度
    int currentHeight = height();

    // 计算新的高度
    int newHeight = contentHeight + 10;  // 10 是一个合理的边距，用于显示文本光标

    // 仅在高度需要改变时才进行调整
    if (currentHeight != newHeight) {
        setFixedHeight(newHeight);
        // 更新滚动区域的总高度
        //updateScrollAreaHeight();
        emit signalHeightChanged();
    }
}

int TextEditor::GetHeight() {
    return height();
}

void TextEditor::onTextModify(bool isMod) {
    qDebug() << "text modify: " << isMod << Qt::endl;
   // NoteMgr::GetInstance()->TextChanged();
}

void TextEditor::resetHighlighting() {
    m_pHighlighter->reset();
}

void TextEditor::loadStyleFromStylesheet(const QString &fileName) {

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
