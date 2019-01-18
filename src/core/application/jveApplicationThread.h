

#ifndef JVEAPPLICATIONTHREAD_H
#define JVEAPPLICATIONTHREAD_H


#include <QThread>


#include "jveApplication.h"


class jveApplicationThread : public QThread
{
    Q_OBJECT
    public:
        explicit  jveApplicationThread(void);
        virtual  ~jveApplicationThread(void);
    public:
        void runApplication(void);
    private slots:
        void slotRunByOptions(void);
    private:
        // members
        jveApplication mp_app;
};


#endif // JVEAPPLICATIONTHREAD_H


