

#ifndef JVETHREADPOOL_H
#define JVETHREADPOOL_H


#include "../utils/JveImageProviderThread.h"

#include "JveApplicationThread.h"


class JveThreadPool
{
    public:
        explicit  JveThreadPool(void);
        virtual  ~JveThreadPool(void);
    public:
        void startThreads(void);
        void stopThreads(void);
    private:
        // members
        JveImageProviderThread mp_imageProviderThread;
        JveApplicationThread   mp_appThread;
};


#endif // JVETHREADPOOL_H


