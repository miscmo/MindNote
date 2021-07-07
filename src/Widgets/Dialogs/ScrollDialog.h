#ifndef SCROLLDIALOG_H
#define SCROLLDIALOG_H

#include "Dialog.h"

class QScrollArea;

namespace MyNote {
    class ScrollDialog : public Dialog
    {
        Q_OBJECT
    public:
        ScrollDialog(QWidget *p_parent = nullptr, Qt::WindowFlags p_flags = Qt::WindowFlags());

        void resizeToHideScrollBarLater(bool p_vertical, bool p_horizontal);

    protected:
        void setCentralWidget(QWidget *p_widget) Q_DECL_OVERRIDE;

        void addBottomWidget(QWidget *p_widget) Q_DECL_OVERRIDE;

        void showEvent(QShowEvent *p_event) Q_DECL_OVERRIDE;

    private:
        QScrollArea *m_scrollArea = nullptr;
    };
} // ns vnotex

#endif // SCROLLDIALOG_H
