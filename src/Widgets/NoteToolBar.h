#ifndef NOTETOOLSBAR_H
#define NOTETOOLSBAR_H

#include <QToolBar>

namespace MyNote {

class NoteToolBar : public QToolBar {
    Q_OBJECT
public:
    static NoteToolBar *getInstance();
    ~NoteToolBar();

    void initUi();
    void initNotebookManage();

private:
    NoteToolBar(QWidget *parent = nullptr);

private:
    static NoteToolBar *m_pInstance;
};

}

#endif // NOTETOOLSBAR_H
