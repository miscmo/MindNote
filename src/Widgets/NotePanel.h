#ifndef NOTEPANEL_H
#define NOTEPANEL_H

namespace MyNote {

class NotePanel : public QWidget {
    Q_OBJECT

public:
    static NotePanel *getInstance();
    ~NotePanel();
    addNoteBlock();

private:
    NotePanel(QWidget *parent);

private:
    static NotePanel *m_pInstance;
    QWidget *contentWidget;
    vector<NoteBlock> noteBlocks;
};



};

#endif // NOTEPANEL_H
