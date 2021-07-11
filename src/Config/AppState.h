#ifndef APPSTATE_H
#define APPSTATE_H

#include <Utils/Noncopyable.h>

#include <QStringList>

namespace MyNote {

class AppState : public Noncopyable {
public:
    ~AppState();

    static AppState *getInstance() {
        static AppState state;
        return &state;
    }

    void restoreAppState(const QStringList &recentlyDir);
    QStringList saveAppState() { return m_sRecentlyDirList; }

    void addRecentlyDir(const QString &dir);
    QStringList getRecentlyDirList();

private:
    explicit AppState();
    QStringList m_sRecentlyDirList;
};

}

#endif // APPSTATE_H
