#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QPlainTextEdit>
#include <Widgets/Highlighter/NoteHighlighter.h>
#include <Widgets/NotePanel/NoteEditor.h>

#include <Notebook/Block.h>

class QTreeWidgetItem;
class QVBoxLayout;

namespace MyNote {

class Buffer;
class LineNumberArea;
class Node;

class TextEditor : public QPlainTextEdit, public EditorInterface {
    Q_OBJECT

public:
    TextEditor(QWidget *parent, Block *block);
    ~TextEditor();

    virtual void initUi() override;
    virtual void setupSignal () override;

    // 调整高度
    virtual int adjustHeight() override;
    virtual int getHeight() override;

    virtual Error save() override;

    void setCurFont(const QFont &font);
    const QFont &getCurFont();

    QString getText();

    void onCurBufferChanged(Buffer* buffer);

    //高亮
    void resetHighlighting();
    void loadStyleFromStylesheet(const QString &fileName);

signals:
    void signalHeightChanged(int height);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void highlightCurrentLine();

    void onTextChanged();

    void onTextModify(bool isMod);

private:
    NoteHighlighter *m_pHighlighter;
    Block *m_pBlock;
};

}

#endif // TEXTEDITOR_H
