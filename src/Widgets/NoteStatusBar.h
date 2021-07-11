#ifndef NOTESTATUSBAR_H
#define NOTESTATUSBAR_H

#include <QStatusBar>

namespace MyNote {

class NoteStatusBar : public QStatusBar {
    Q_OBJECT
public:
    static NoteStatusBar *getInstance();
    ~NoteStatusBar();

    void initUi();

private:
    NoteStatusBar(QWidget *parent = nullptr);

private:
    static NoteStatusBar *m_pInstance;
};

}

#endif // NOTESTATUSBAR_H
