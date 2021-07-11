#ifndef NOTEEDITOR_H
#define NOTEEDITOR_H

#include <QPlainTextEdit>

class QTreeWidgetItem;
class QVBoxLayout;

namespace MyNote {

class Buffer;
class LineNumberArea;
class Node;

class NoteEditor : public QPlainTextEdit {
    Q_OBJECT
public:
    static NoteEditor *getInstance();
    ~NoteEditor();

    void initUi();
    void setupSignal();
    void setupUi();

    QString getText();

    void onCurBufferChanged(Buffer* buffer);

    //行号
    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);

    void onCurrentNodeChanged(Node *node);

private:
    NoteEditor(QWidget *parent);

private:
    LineNumberArea *m_pLineNumberArea;

    static NoteEditor *m_pInstance;
};

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(NoteEditor *editor) : QWidget(editor) {
        m_pNoTeEditor = editor;
    }

    QSize sizeHint() const override {
        return QSize(m_pNoTeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        m_pNoTeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    NoteEditor *m_pNoTeEditor;
};

}

#endif // NOTEEDITOR_H
