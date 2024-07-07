#include "LeftPanel.h"

#include <QMouseEvent>
#include <QMenu>
#include <QMessageBox>

using namespace MyNote;

LeftPanel::LeftPanel(QWidget *parent)
    : QWidget(parent) {
    setAttribute(Qt::WA_StyledBackground);
    setStyleSheet("background-color: lightblue;");
    setFixedHeight(50);
    setMouseTracking(true);

    m_pAddBtn = new QPushButton(tr("+"), this);
    m_pAddBtn->setGeometry(10, 10, 30, 30);
    m_pAddBtn->hide();

    // 实现点击addButton之后，弹出菜单选择笔记块类型
    connect(m_pAddBtn, &QPushButton::clicked, this, &LeftPanel::onShowBlockSelectMenu);
}

LeftPanel::~LeftPanel() {
}

void LeftPanel::mouseMoveEvent(QMouseEvent *event) {
    if (event->pos().x() < width()) {
        m_pAddBtn->move(10, event->pos().y() - m_pAddBtn->height() / 2);
        m_pAddBtn->show();
    } else {
        m_pAddBtn->hide();
    }
}

void LeftPanel::onShowBlockSelectMenu() {
    // Create a menu and add actions
    QMenu addMenu(this);
    QAction *textBlockAction = addMenu.addAction(tr("plain text block"));
    QAction *mdBlockAction = addMenu.addAction("markdown block");
    QAction *flowChartAction = addMenu.addAction("flow chart block");

    connect(&addMenu, &QMenu::triggered, this, &LeftPanel::onAddBlock);

    // Get the position of the button and show the menu there
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) {
        QPoint pos = button->mapToGlobal(QPoint(0, button->height()));
        addMenu.exec(pos);
    }

}

void LeftPanel::onAddBlock(QAction *action) {
    // addNoteBlock();
    QMessageBox::information(nullptr, tr("Menu Action"), action->text());
}
