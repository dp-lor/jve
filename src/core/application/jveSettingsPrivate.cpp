

#include "jveSettingsPrivate.h"


#include "../definitions/jveDefines.h"


jveSettingsPrivate jveSettings;


jveSettingsPrivate::jveSettingsPrivate(void)
    : QSettings(
        QSettings::IniFormat,
        QSettings::UserScope,
        JVE_ORG_NAME,
        JVE_VERSION_STRING
    ),
        mp_mutex(QMutex::NonRecursive)
{
}

jveSettingsPrivate::~jveSettingsPrivate(void)
{
}

void
jveSettingsPrivate::lock(void)
{
    mp_mutex.lock();
}

void
jveSettingsPrivate::unlock(void)
{
    mp_mutex.unlock();
}


