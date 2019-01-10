

#include "jveProjectMutexPrivate.h"


jveProjectMutexPrivate jveProjectMutex;


jveProjectMutexPrivate::jveProjectMutexPrivate(void)
    : QMutex(QMutex::NonRecursive)
{
}

jveProjectMutexPrivate::~jveProjectMutexPrivate(void)
{
}


