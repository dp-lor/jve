

#ifndef JVEAPPLICATIONTHREAD_H
#define JVEAPPLICATIONTHREAD_H


#include <QThread>


#include "JveApplication.h"


class JveApplicationThread : public QThread
{
    Q_OBJECT
    public:
        explicit  JveApplicationThread(void);
        virtual  ~JveApplicationThread(void);
    public:
        void runApplication(void);
    private slots:
        void slotRunByOptions(void);
    private:
        // members
        JveApplication mp_app;
};


#endif // JVEAPPLICATIONTHREAD_H


