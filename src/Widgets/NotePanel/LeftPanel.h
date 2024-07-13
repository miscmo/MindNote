#ifndef LEFTPANEL_H
#define LEFTPANEL_H

#include <QWidget>
#include <QPushButton>

namespace MyNote {

class LeftPanel : public QWidget {
    Q_OBJECT

public:
    LeftPanel(QWidget *parent);
    ~LeftPanel();

private slots:
    void onShowBlockSelectMenu();
    void onAddBlock(QAction *action);

protected:
    void mouseMoveEvent(QMouseEvent *event) override;


private:
    QPushButton *m_pAddBtn;

};

}

#endif // LEFTPANEL_H
