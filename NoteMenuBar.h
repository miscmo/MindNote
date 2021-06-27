#ifndef NOTEMENUBAR_H
#define NOTEMENUBAR_H

#include <QMenuBar>

namespace gnote {

class NoteMenuBar : public QMenuBar {
    Q_OBJECT
public:
    static NoteMenuBar *getInstance();
    ~NoteMenuBar();

    void initUi();

private:
    NoteMenuBar(QWidget *parent);
};

}

#endif // NOTEMENUBAR_H
