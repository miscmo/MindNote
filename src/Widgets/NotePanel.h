#ifndef NOTEPANEL_H
#define NOTEPANEL_H

#include <QWidget>

namespace MyNote {

class NotePanel : public QWidget {
    Q_OBJECT

public:
    static NotePanel *getInstance();
    ~NotePanel();
    void addNoteBlock();

private:
    NotePanel(QWidget *parent);

private:
    static NotePanel *m_pInstance;
    QWidget *m_pContentWidget;
    //vector<NoteBlock> noteBlocks;
};



};

#endif // NOTEPANEL_H
