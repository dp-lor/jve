

#include "JveLoadingProjectMutexPrivate.h"


JveLoadingProjectMutexPrivate JveLoadingProjectMutex;


JveLoadingProjectMutexPrivate::JveLoadingProjectMutexPrivate(void)
    : QMutex(QMutex::NonRecursive)
{
}

JveLoadingProjectMutexPrivate::~JveLoadingProjectMutexPrivate(void)
{
}


