#ifndef NOTEWIDGET_H
#define NOTEWIDGET_H

#include <QWidget>
#include <Notebook/Block.h>

namespace MyNote {

class NoteWidget : public QWidget {
    Q_OBJECT

public:
    NoteWidget(QWidget *parent);
    ~NoteWidget();

    void initUI();
    void initSignal();


private slots:
    //void onCurrentBlockChanged(Block *block);
    void onBlockChanged();


private:
    Block *m_pBlock;
};

};

#endif // NOTEWIDGET_H
