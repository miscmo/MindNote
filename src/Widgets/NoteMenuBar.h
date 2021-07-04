#ifndef NOTEMENUBAR_H
#define NOTEMENUBAR_H

#include <QMenuBar>

namespace MyNote {

class NoteMenuBar : public QMenuBar {
    Q_OBJECT
public:
    static NoteMenuBar *getInstance();
    ~NoteMenuBar();

    void initUi();

private:
    NoteMenuBar(QWidget *parent);
    static NoteMenuBar *m_pInstance;
};

}

#endif // NOTEMENUBAR_H
