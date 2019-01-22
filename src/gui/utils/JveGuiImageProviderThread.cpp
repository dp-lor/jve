

#include "JveGuiImageProviderThread.h"


JveGuiImageProviderThread::JveGuiImageProviderThread(void)
    : QThread(nullptr),
        mp_imageProvider()
{
    // move image provider to thread
    mp_imageProvider.moveToThread(this);
}

JveGuiImageProviderThread::~JveGuiImageProviderThread(void)
{
}


