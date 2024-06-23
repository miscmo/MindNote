#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

class QDockWidget;

namespace MyNote {

class NoteExplorer;
class FileExplorer;
class ViewArea;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void init();

    void initUi();
    void initToolBar();
    void initMenuBar();
    void initCentralWindow();
    void initDock();
    void initStatusBar();
    void initGlobalShortcut();

    void saveStateAndGeometry();
    void loadStateAndGeometry();


protected:
    virtual void closeEvent(QCloseEvent *p_event) Q_DECL_OVERRIDE;

private:
    ViewArea *m_pViewArea;

    NoteExplorer *m_pNoteExplorer;
    FileExplorer *m_pFileExplorer;

    QDockWidget *m_pNotebookDock;
    QDockWidget *m_pFileDock;
};

}

#endif // MAINWINDOW_H
