#ifndef MARKDOWNEDITOR_H
#define MARKDOWNEDITOR_H

#include <QTextEdit>
#include <Widgets/NotePanel/NoteEditor.h>

namespace MyNote {

class Block;

class MarkdownEditor : public QTextEdit, public NoteEditor {
    Q_OBJECT

public:
    MarkdownEditor(QWidget *parent, Block *block);
    ~MarkdownEditor();

    void initUi();
    void setupSignal();

    virtual int autoAdjustHeight() override;
    virtual Error save() override;

private:
};

}

#endif // MARKDOWNEDITOR_H
