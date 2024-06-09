#ifndef WIDGETFACTORY_H
#define WIDGETFACTORY_H

class QFormLayout;
class QWidget;
class QTreeWidgetItem;
class QTreeWidget;

namespace MyNote {

class NodeItem;
class WidgetFactory {
public:
    WidgetFactory() = delete;

    static QFormLayout *createFormLayout(QWidget *parent = nullptr);

    static NodeItem *CreateNodeItem(QTreeWidget *parent);

    static NodeItem *CreateNodeItem(QTreeWidgetItem *parent);
};

}

#endif // WIDGETFACTORY_H
