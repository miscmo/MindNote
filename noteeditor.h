#ifndef NOTEEDITOR_H
#define NOTEEDITOR_H

#include <QWidget>

class QTextEdit;
class QTreeWidgetItem;
class QVBoxLayout;

namespace gnote {

class NoteEditor : public QWidget {
    Q_OBJECT
public:
    static NoteEditor *getInstance();
    ~NoteEditor();

    void initUi();
    void setupSignal();
    void setupUi();
    void handleItemClicked(QTreeWidgetItem *item, int colum);

private:
    NoteEditor(QWidget *parent);

private:
    QTextEdit *m_pTextEdit;
    QVBoxLayout *m_pMainLayout;
};

}

#endif // NOTEEDITOR_H
