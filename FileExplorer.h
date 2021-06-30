#ifndef FILEEXPLORER_H
#define FILEEXPLORER_H

#include <QWidget>

namespace gnote {

class FileExplorer : public QWidget {
    Q_OBJECT
public:
    static FileExplorer *getInstance();

    ~FileExplorer();

private:
    FileExplorer(QWidget *parent);

private:
    static FileExplorer *m_pInstance;
};

}

#endif // FILEEXPLORER_H
