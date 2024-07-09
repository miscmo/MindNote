#ifndef NOTEPANEL_H
#define NOTEPANEL_H

#include <QWidget>
#include <Notebook/Node.h>
#include <QGridLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QToolBar>

namespace MyNote {

class LeftPanel;
class RightPanel;

class NotePanel : public QWidget {
    Q_OBJECT

public:
    static NotePanel *getInstance();
    ~NotePanel();
    void addNoteBlock();
    void setupSignal();
    void setupUI();
    void clear();
    void reload();

protected:

private slots:
    void onCurrentNodeChanged(Node *node);
    void onAddBlock(QAction *action);
    void onShowBlockSelectMenu();
    void onRefreshLayout();
    void onSave();

private:
    NotePanel(QWidget *parent);

private:
    static NotePanel *m_pInstance;
    QWidget *m_pContentWidget;
    QVBoxLayout *m_pMainLayout;
    QVBoxLayout *m_pScrollLayout;
    Node *m_pNode;
    LeftPanel *m_pLeftPanel;
    // todo 这里可以考虑使用QTabWidget实现多窗口选项卡
    RightPanel *m_pRightPanel;
    QToolBar *m_pToolBar;
};



}

#endif // NOTEPANEL_H
