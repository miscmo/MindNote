#include "WidgetFactory.h"

#include "NodeItem.h"

#include <QFormLayout>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QMessageBox>>

using namespace MyNote;

QFormLayout *WidgetFactory::createFormLayout(QWidget *parent) {
    QFormLayout *layout = new QFormLayout(parent);

    return layout;
}

NodeItem *WidgetFactory::CreateNodeItem(QTreeWidget *parent) {
    NodeItem *item = new NodeItem(parent);

    return item;
}

NodeItem *WidgetFactory::CreateNodeItem(QTreeWidgetItem *parent) {
    NodeItem *item = new NodeItem(parent);

    return item;
}


auto WidgetFactory::TodoDialog() {

    auto todoMsgBox = [=](bool checked) {
        // 创建消息框并设置标题和文本内容
        QMessageBox messageBox;
        messageBox.setWindowTitle("功能开发中");
        messageBox.setText("该功能正在开发中，敬请期待！");
        messageBox.setIcon(QMessageBox::Information);

        // 显示消息框
        messageBox.exec();
    };

    return todoMsgBox;
}
