

#include "jveLocalizationMutexPrivate.h"


jveLocalizationMutexPrivate jveLocalizationMutex;


jveLocalizationMutexPrivate::jveLocalizationMutexPrivate(void)
    : QMutex(QMutex::NonRecursive)
{
}

jveLocalizationMutexPrivate::~jveLocalizationMutexPrivate(void)
{
}


