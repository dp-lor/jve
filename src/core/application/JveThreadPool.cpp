

#include "JveThreadPool.h"


JveThreadPool::JveThreadPool(void)
    : mp_mainThread(),
        mp_engineThread()
{
}

JveThreadPool::~JveThreadPool(void)
{
}

void
JveThreadPool::startThreads(void)
{
    mp_mainThread   .start( QThread::HighestPriority );
    mp_engineThread .start( QThread::NormalPriority  );
}

void
JveThreadPool::stopThreads(void)
{
    mp_engineThread.quit();
    mp_engineThread.wait();

    mp_mainThread.quit();
    mp_mainThread.wait();
}


