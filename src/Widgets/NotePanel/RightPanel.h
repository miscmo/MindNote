#ifndef RIGHTPANEL_H
#define RIGHTPANEL_H

#include <QWidget>
#include <QVBoxLayout>
#include <QToolBar>
#include <QPushButton>

#include <Notebook/Node.h>

namespace MyNote {

class TextEditor;

class RightPanel : public QWidget {
    Q_OBJECT

public:
    RightPanel(QWidget *parent);
    ~RightPanel();

    void setupUI();
    void setupSignal();

    void clear();

    void buildLayout(Node *node);

    void Save();

private slots:
    void onAdjustHeight();

private:
    QVBoxLayout *m_pMainLayout;
    QToolBar *m_pToolBar;
    Node *m_pNode;
    // todo 暂时使用NoteEditor，后续需要考虑多种类型的编辑器
    TextEditor *m_pEditor;
};

}

#endif // RIGHTPANEL_H
