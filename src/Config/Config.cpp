#include "Config.h"

#include <Utils/Base.h>

#include <QByteArray>
#include <QSettings>

namespace MyNote {
Config::Config() {
    m_sConfigFilePath = Base::getAppDirPath() + '/' + CONF_FILE_NAME;
    m_pSettings = new QSettings(m_sConfigFilePath, QSettings::IniFormat);
}

Config::~Config() {
    delete m_pSettings;
}

void Config::set(const QString &key, const QVariant &value) {
    m_pSettings->setValue(key, value);
}

QVariant Config::get(const QString &key, const QVariant &defValue) {
    return m_pSettings->value(key, defValue);
}
};
