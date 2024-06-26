#include "WidgetMgr.h"

#include <QMessageBox>


namespace MyNote {

WidgetMgr* WidgetMgr::GetInstance() {
    static WidgetMgr mgr;
    return &mgr;
}

WidgetMgr::~WidgetMgr() {}

void WidgetMgr::TodoDialog() {
    // 创建消息框并设置标题和文本内容
    QMessageBox messageBox;
    messageBox.setWindowTitle("功能开发中");
    messageBox.setText("该功能正在开发中，敬请期待！");
    messageBox.setIcon(QMessageBox::Information);

    // 显示消息框
    messageBox.exec();
}

}
