#ifndef CONFIGMGR_H
#define CONFIGMGR_H

#include <QObject>
#include <QVariant>

#define CONF_FILE_NAME "gnote.ini"

#define CONF_WIN_STATE_KEY "window_state"
#define CONF_WIN_GEOMETRY_KEY "window_geometry"
#define CONF_RECENTLY_FILE_KEY "Recently_File"

class QSettings;

namespace MyNote {
    class Config : public QObject {
        Q_OBJECT

    public:
        ~Config();

        static Config *getInstance() {
            static Config config;
            return &config;
        }

        void set(const QString &key, const QVariant &value);
        QVariant get(const QString &key, const QVariant &defVal = QVariant());

    private:
        Config();


    private:
        QString m_sConfigFilePath;
        QSettings *m_pSettings;
    };
};

#endif // CONFIGMGR_H
