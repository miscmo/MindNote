#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QByteArray>
#include <QStringList>

namespace gnote {

#define NODE_MD_NAME "README.md"
#define NODE_IMG_DIR "gnote_img"

class Utils {
public:
    class File {
    public:
        static QByteArray read(QString filename);
        static void write(QString filename, QByteArray ctx);
    };
    static QStringList listNode(const QString &path);
};

}


#endif // UTILS_H
