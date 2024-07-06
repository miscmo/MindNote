#ifndef NOTEPANEL_H
#define NOTEPANEL_H

#include <QWidget>
#include <Notebook/Node.h>
#include <QGridLayout>

namespace MyNote {

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


private slots:
    void onCurrentNodeChanged(Node *node);
    void showBlockSelectMenu();

private:
    NotePanel(QWidget *parent);

private:
    static NotePanel *m_pInstance;
    QWidget *m_pContentWidget;
    QGridLayout *m_pMainLayout;
    Node *m_pNode;
};



};

#endif // NOTEPANEL_H
