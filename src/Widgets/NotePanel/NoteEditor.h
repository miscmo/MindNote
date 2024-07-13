#ifndef NOTEEDITOR_H
#define NOTEEDITOR_H

#include <QWidget>
#include <Utils/Errors.h>

namespace MyNote {

class Block;

class EditorInterface {
public:
    virtual void init() = 0;
    //virtual void setupSignal() = 0;
    virtual int adjustHeight() = 0;
    virtual int getHeight() = 0;
    virtual Error save() = 0;
};


class NoteEditor : public QWidget {
    Q_OBJECT

public:
    NoteEditor(QWidget *parent, Block *block);
    ~NoteEditor();

    void initUi();
    void setupSignal();

    virtual int getHeight();

    virtual Error save();

signals:
    void signalHeightChanged(int height);


private:
    Block *m_pBlock;
    EditorInterface *m_pEditor;
};

}

#endif // NOTEEDITOR_H
