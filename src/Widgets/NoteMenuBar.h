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
    void initMenuNotebook();
    void initMenuEdit();
    void initMenuImport();
    void initMenuTools();
    void initMenuView();
    void initMenuAbout();
    void initRecentlyFileList(QMenu *menuFile);

private slots:
    void openNotebook();
    void saveNote();
    void exitApp();

private:
    NoteMenuBar(QWidget *parent = nullptr);

private:
    static NoteMenuBar *m_pInstance;
};

}

#endif // NOTEMENUBAR_H
