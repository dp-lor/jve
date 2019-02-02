

#ifndef JVEMAINTHREAD_H
#define JVEMAINTHREAD_H


#include <QThread>


#include "JveMainController.h"


class JveMainThread : public QThread
{
    Q_OBJECT
    public:
        explicit  JveMainThread(void);
        virtual  ~JveMainThread(void);
    private slots:
        void slotRun(void);
    private:
        // members
        JveMainController mp_controller;
};


#endif // JVEMAINTHREAD_H


