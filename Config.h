#ifndef CONFIGMGR_H
#define CONFIGMGR_H

#include <QObject>
#include <base.h>

#define CONF_FILE_NAME "gnote.ini"

class QSettings;

namespace gnote {
    class Config : public QObject {
        Q_OBJECT

    public:
        ~Config();

        static Config *Instance() {
            static Config config;
            return &config;
        }

        void set(const QString &key, const QVariant &value);
        QVariant get(const QString &key);

    private:
        Config();


    private:
        QString m_sConfigFilePath;
        QSettings *m_pSettings;
    };
};

#endif // CONFIGMGR_H
