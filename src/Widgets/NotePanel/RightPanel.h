#ifndef RIGHTPANEL_H
#define RIGHTPANEL_H

#include <QWidget>
#include <QVBoxLayout>
#include <QToolBar>
#include <QPushButton>

#include <Notebook/Node.h>

namespace MyNote {

class RightPanel : public QWidget {
    Q_OBJECT

public:
    RightPanel(QWidget *parent);
    ~RightPanel();

    void setupUI();
    void setupSignal();

    void clear();

    void buildLayout(Node *node);

private slots:

private:
    QVBoxLayout *m_pMainLayout;
    QToolBar *m_pToolBar;
};

}

#endif // RIGHTPANEL_H
