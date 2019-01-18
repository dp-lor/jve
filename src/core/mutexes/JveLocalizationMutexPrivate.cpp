

#include "JveLocalizationMutexPrivate.h"


JveLocalizationMutexPrivate JveLocalizationMutex;


JveLocalizationMutexPrivate::JveLocalizationMutexPrivate(void)
    : QMutex(QMutex::NonRecursive)
{
}

JveLocalizationMutexPrivate::~JveLocalizationMutexPrivate(void)
{
}


