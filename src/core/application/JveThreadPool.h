

#ifndef JVETHREADPOOL_H
#define JVETHREADPOOL_H

#include "JveMainThread.h"
#include "JveEngineThread.h"


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
        JveMainThread   mp_mainThread;
        JveEngineThread mp_engineThread;
};


#endif // JVETHREADPOOL_H


