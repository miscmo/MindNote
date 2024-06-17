#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QByteArray>
#include <QStringList>

#define SAFE_DELETE(p) if (p) { delete p; p = nullptr; }
#define SAFE_DELETE_ARR(p) if (p) { delete [] p; p = nullptr; }


namespace MyNote {

#define NODE_MD_NAME "README.md"
#define NODE_IMG_DIR "gnote_img"

#define DEF_NODE_FILE "defnote.mind"

#define NOTE_DEF_JSON "mindnote.json"

#define DATETIME_FORMAT "yyyy-MM-dd hh:mm:ss"

class Utils {
public:
    class File {
    public:
        static QByteArray read(QString filename);
        static void write(QString filename, QByteArray ctx);
    };
    static QStringList listNode(const QString &path);
    static QString GetUUID();
};


}


#endif // UTILS_H
