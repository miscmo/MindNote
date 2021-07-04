#ifndef NOTEMENUBAR_H
#define NOTEMENUBAR_H

#include <QMenuBar>

class QSignalMapper;

namespace MyNote {

class NoteMenuBar : public QMenuBar {
    Q_OBJECT
public:
    static NoteMenuBar *getInstance();
    ~NoteMenuBar();

    void initUi();
    void initRecentlyFileList(QMenu *menuFile);

private:
    NoteMenuBar(QWidget *parent = nullptr);

private:
    static NoteMenuBar *m_pInstance;
    QSignalMapper *m_pSignalMapper;
};

}

#endif // NOTEMENUBAR_H
