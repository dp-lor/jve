

#ifndef JVETHREADPOOL_H
#define JVETHREADPOOL_H

#include "JveApplicationThread.h"
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
        JveApplicationThread mp_appThread;
        JveEngineThread      mp_engineThread;
};


#endif // JVETHREADPOOL_H


