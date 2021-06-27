#ifndef VIEWAREA_H
#define VIEWAREA_H

#include <QWidget>

class QVBoxLayout;

namespace gnote {

class NoteEditor;

class ViewArea : public QWidget {
    Q_OBJECT
public:
    static ViewArea *getInstance();
    ~ViewArea();

    void initUi();

private:
    ViewArea(QWidget *parent = nullptr);

private:
    NoteEditor *m_pNoteEditor;
    QVBoxLayout *m_pMainLayout;
};

}

#endif // VIEWAREA_H
