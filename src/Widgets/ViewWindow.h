#ifndef VIEWWINDOW_H
#define VIEWWINDOW_H

#include <QWidget>

namespace MyNote {

class ViewWindow : public QWidget {
    Q_OBJECT
public:
    ViewWindow(QWidget *parent);
    ~ViewWindow();

};

}


#endif // VIEWWINDOW_H
