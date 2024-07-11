#ifndef NOTEEDITOR_H
#define NOTEEDITOR_H

#include <QWidget>
#include <Utils/Errors.h>

namespace MyNote {

class Block;

class NoteEditor : public virtual QWidget {
    Q_OBJECT

public:
    NoteEditor(QWidget *parent, Block *block);
    ~NoteEditor();

    void initUi();
    void setupSignal();

    virtual int getHeight();
    virtual int autoAdjustHeight();

    virtual Error save();

signals:
    void signalHeightChanged(int height);

public slots:



private:
    Block *m_pBlock;
};

}

#endif // NOTEEDITOR_H
