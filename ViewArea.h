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
    QVBoxLayout *m_pMainLayout;

    static ViewArea *m_pInstance;
};

}

#endif // VIEWAREA_H
