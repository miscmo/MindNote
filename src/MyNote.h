#ifndef MYNOTE_H
#define MYNOTE_H

#include <QObject>
#include <Utils/Noncopyable.h>

namespace MyNote {

class MainWindow;
class NoteEditor;
class NoteExplorer;
class FileExplorer;

class MyNote : public QObject, public Noncopyable {
public:
    static MyNote *getInstance() {
        static MyNote _inst;
        return &_inst;
    }

    ~MyNote();

    MainWindow *GetMainWindow() { return m_pMainWindow; }
    void SetMainWindow(MainWindow *mainWindow);

private:
    explicit MyNote(QObject *parent = nullptr);


private:
    MainWindow *m_pMainWindow;
};

}

#endif // MYNOTE_H
