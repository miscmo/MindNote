#ifndef WIDGETMGR_H
#define WIDGETMGR_H

#include <QObject>

namespace MyNote {

class NoteToolBar;

class WidgetMgr : public QObject {
    Q_OBJECT

public:
    static WidgetMgr *GetInstance();

    ~WidgetMgr();


    void TodoDialog();
    QString ImgOpenDialog(QWidget *parent);
};

}

#endif // WIDGETMGR_H
