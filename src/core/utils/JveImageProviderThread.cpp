

#include "JveImageProviderThread.h"


JveImageProviderThread::JveImageProviderThread(void)
    : QThread(nullptr),
        mp_imageProvider()
{
    // move image provider to thread
    mp_imageProvider.moveToThread(this);
}

JveImageProviderThread::~JveImageProviderThread(void)
{
}


