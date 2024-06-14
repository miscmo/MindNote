#include "NoteExplorerPopMenu.h"

#include <Widgets/NoteExplorer.h>
#include <QMessageBox>

namespace MyNote {

NoteExplorerPopMenu::NoteExplorerPopMenu(QWidget *parent)
    :QMenu(parent) {
    initUi();

    initSignal();
}

NoteExplorerPopMenu::~NoteExplorerPopMenu() {
}

void NoteExplorerPopMenu::initUi() {
    QAction *addSub = addAction(tr("addSub"));
    QAction *addPre = addAction(tr("addPre"));
    QAction *addPost = addAction(tr("addPost"));

    QAction *delItem = addAction(tr("delete"));

    QAction *renameItem = addAction(tr("rename"));

    QAction *iconItem = addAction(tr("editIcon"));

    auto todoMsgBox = [=](bool checked) {
        // 创建消息框并设置标题和文本内容
        QMessageBox messageBox;
        messageBox.setWindowTitle("功能开发中");
        messageBox.setText("该功能正在开发中，敬请期待！");
        messageBox.setIcon(QMessageBox::Information);

        // 显示消息框
        messageBox.exec();
    };

    connect(addSub, &QAction::triggered, NoteExplorer::getInstance(), &NoteExplorer::onAddSub);
    connect(addPre, &QAction::triggered, NoteExplorer::getInstance(), &NoteExplorer::onAddPre);
    connect(addPost, &QAction::triggered, NoteExplorer::getInstance(), &NoteExplorer::onAddPost);
    connect(delItem, &QAction::triggered, todoMsgBox);
    connect(renameItem, &QAction::triggered, todoMsgBox);
    connect(iconItem, &QAction::triggered, todoMsgBox);
}

void NoteExplorerPopMenu::initSignal() {
}

}
