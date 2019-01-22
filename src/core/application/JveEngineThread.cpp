

#include "JveEngineThread.h"


JveEngineThread::JveEngineThread(void)
    : QThread(nullptr),
        mp_engine()
{
    // move engine to thread
    mp_engine.moveToThread(this);

    // connect for self started
    connect(
        this,
        SIGNAL(started()),
        &mp_engine,
        SLOT(slotWakeUp()),
        Qt::QueuedConnection
    );
}

JveEngineThread::~JveEngineThread(void)
{
}


