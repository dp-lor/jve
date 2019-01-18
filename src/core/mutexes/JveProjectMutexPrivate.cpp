

#include "JveProjectMutexPrivate.h"


JveProjectMutexPrivate JveProjectMutex;


JveProjectMutexPrivate::JveProjectMutexPrivate(void)
    : QMutex(QMutex::NonRecursive)
{
}

JveProjectMutexPrivate::~JveProjectMutexPrivate(void)
{
}


