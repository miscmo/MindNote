#ifndef BASE_H
#define BASE_H

#include <QString>
#include <QCoreApplication>
#include <QDir>

namespace gnote {
class Base {
public:
    static QString getAppDirPath() {
        return QCoreApplication::applicationDirPath();
    }

    static QString getAppFilePath() {
        return QCoreApplication::applicationFilePath();
    }
};

};

#endif // BASE_H
