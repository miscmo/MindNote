#ifndef WIDGETFACTORY_H
#define WIDGETFACTORY_H

class QFormLayout;
class QWidget;

namespace MyNote {

class WidgetFactory {
public:
    WidgetFactory() = delete;

    static QFormLayout *createFormLayout(QWidget *parent = nullptr);
};

}

#endif // WIDGETFACTORY_H
