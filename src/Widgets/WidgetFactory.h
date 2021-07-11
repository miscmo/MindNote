#ifndef WIDGETFACTORY_H
#define WIDGETFACTORY_H

class QFormLayout;
class QWidget;
class QTreeWidgetItem;
class QTreeWidget;

namespace MyNote {

class WidgetFactory {
public:
    WidgetFactory() = delete;

    static QFormLayout *createFormLayout(QWidget *parent = nullptr);

    static QTreeWidgetItem *createNoteExplorerItem(QTreeWidget *parent);

    static QTreeWidgetItem *createNoteExplorerItem(QTreeWidgetItem *parent);
};

}

#endif // WIDGETFACTORY_H
