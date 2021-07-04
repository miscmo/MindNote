#include "AppState.h"

#include "Config.h"

#include <QVariant>

namespace MyNote {

#define MAX_RECENTLY_FILE 5

AppState::AppState() {
     m_sRecentlyDirList = Config::getInstance()->get(CONF_RECENTLY_FILE_KEY, QStringList()).toStringList();
}

AppState::~AppState() {
    Config::getInstance()->set(CONF_RECENTLY_FILE_KEY, this->m_sRecentlyDirList);
}

void AppState::addRecentlyDir(const QString &dir) {
    Q_ASSERT(!dir.isEmpty());

    int idx = m_sRecentlyDirList.indexOf(dir);
    if (-1 != idx) {
        m_sRecentlyDirList.removeAt(idx);
    }

    m_sRecentlyDirList.push_front(dir);

    if (m_sRecentlyDirList.size() > 5) {
        m_sRecentlyDirList.pop_back();
    }
}

QStringList AppState::getRecentlyDirList() {
    return m_sRecentlyDirList;
}

void AppState::restoreAppState(const QStringList &recentlyDir) {
    m_sRecentlyDirList = recentlyDir;
}

}
