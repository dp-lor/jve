

#include "JveThreadPool.h"


JveThreadPool::JveThreadPool(void)
    : mp_appThread(),
        mp_engineThread()
{
}

JveThreadPool::~JveThreadPool(void)
{
}

void
JveThreadPool::startThreads(void)
{
    mp_appThread    .start( QThread::HighestPriority );
    mp_engineThread .start( QThread::NormalPriority  );
}

void
JveThreadPool::stopThreads(void)
{
    mp_engineThread.quit();
    mp_engineThread.wait();

    mp_appThread.quit();
    mp_appThread.wait();
}


