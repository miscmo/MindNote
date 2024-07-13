#ifndef MARKDOWNEDITOR_H
#define MARKDOWNEDITOR_H

#include <QTextEdit>
#include <Widgets/NotePanel/NoteEditor.h>

namespace MyNote {

class Block;

class MarkdownEditor : public QTextEdit, public EditorInterface {
    Q_OBJECT

public:
    MarkdownEditor(QWidget *parent, Block *block);
    ~MarkdownEditor();

    virtual void initUi () override;
    virtual void setupSignal () override;

    virtual int adjustHeight() override;
    virtual int getHeight() override;

    virtual Error save() override;

signals:
    void signalHeightChanged(int height);

private:
};

}

#endif // MARKDOWNEDITOR_H
