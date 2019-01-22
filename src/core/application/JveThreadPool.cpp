

#include "JveThreadPool.h"


JveThreadPool::JveThreadPool(void)
    : mp_imageProviderThread(),
        mp_appThread()
{
}

JveThreadPool::~JveThreadPool(void)
{
}

void
JveThreadPool::startThreads(void)
{
    mp_imageProviderThread .start(QThread::NormalPriority);
    mp_appThread           .start(QThread::HighestPriority);
}

void
JveThreadPool::stopThreads(void)
{
    mp_appThread.quit();
    mp_appThread.wait();

    mp_imageProviderThread.quit();
    mp_imageProviderThread.wait();
}


