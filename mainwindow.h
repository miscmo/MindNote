#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

class QDockWidget;

namespace gnote {

class NoteExplorer;
class FileExplorer;
class ViewArea;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    ~MainWindow();

    static MainWindow *getInstance();

    void init();

    void initUi();

    void saveStateAndGeometry();
    void loadStateAndGeometry();

    void initMenuBar();

protected:
    virtual void closeEvent(QCloseEvent *p_event) Q_DECL_OVERRIDE;

private:
    MainWindow(QWidget *parent = nullptr);

private:
    ViewArea *m_pViewArea;

    NoteExplorer *m_pNoteExplorer;
    FileExplorer *m_pFileExplorer;

    QDockWidget *m_pNotebookDock;
    QDockWidget *m_pFileDock;
};

}

#endif // MAINWINDOW_H
