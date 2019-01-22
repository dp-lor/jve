

#ifndef JVEENGINETHREAD_H
#define JVEENGINETHREAD_H


#include <QThread>


#include "JveEngine.h"


class JveEngineThread : public QThread
{
    Q_OBJECT
    public:
        explicit  JveEngineThread(void);
        virtual  ~JveEngineThread(void);
    private:
        // members
        JveEngine mp_engine;
};


#endif // JVEENGINETHREAD_H


