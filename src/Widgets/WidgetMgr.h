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
};

}

#endif // WIDGETMGR_H
