

#include "JveThreadPool.h"


JveThreadPool::JveThreadPool(void)
    : mp_appThread()
{
}

JveThreadPool::~JveThreadPool(void)
{
}

void
JveThreadPool::startThreads(void)
{
    mp_appThread.start(QThread::HighPriority);
}

void
JveThreadPool::stopThreads(void)
{
    mp_appThread.quit();
    mp_appThread.wait();
}


