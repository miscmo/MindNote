#ifndef NOTEEDITOR_H
#define NOTEEDITOR_H

#include <QWidget>

class QTextEdit;
class QTreeWidgetItem;
class QVBoxLayout;

namespace gnote {

class Buffer;

class NoteEditor : public QWidget {
    Q_OBJECT
public:
    static NoteEditor *getInstance();
    ~NoteEditor();

    void initUi();
    void setupSignal();
    void setupUi();

    QString getText();

    void onCurBufferChanged(Buffer* buffer);

private:
    NoteEditor(QWidget *parent);

private:
    QTextEdit *m_pTextEdit;
    QVBoxLayout *m_pMainLayout;
    static NoteEditor *m_pInstance;
};

}

#endif // NOTEEDITOR_H
