#ifndef NOTEFONTSETTING_H
#define NOTEFONTSETTING_H

#include <QFontDialog>

namespace MyNote {

class NoteFontSetting : public QFontDialog {
    Q_OBJECT
public:
    NoteFontSetting(QWidget *parent = nullptr);
    ~NoteFontSetting();

    void initUi();
};

}

#endif // NOTEFONTSETTING_H
