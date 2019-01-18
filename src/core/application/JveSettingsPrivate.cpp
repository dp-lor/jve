

#include "JveSettingsPrivate.h"


#include "../definitions/JveDefines.h"


JveSettingsPrivate JveSettings;


JveSettingsPrivate::JveSettingsPrivate(void)
    : QSettings(
        QSettings::IniFormat,
        QSettings::UserScope,
        JVE_ORG_NAME,
        JVE_VERSION_STRING
    ),
        mp_mutex(QMutex::NonRecursive)
{
}

JveSettingsPrivate::~JveSettingsPrivate(void)
{
}

void
JveSettingsPrivate::lock(void)
{
    mp_mutex.lock();
}

void
JveSettingsPrivate::unlock(void)
{
    mp_mutex.unlock();
}


