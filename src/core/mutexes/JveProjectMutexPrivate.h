

#ifndef JVEPROJECTMUTEXPRIVATE_H
#define JVEPROJECTMUTEXPRIVATE_H


#include <QMutex>


class JveProjectMutexPrivate : public QMutex
{
    public:
        explicit  JveProjectMutexPrivate(void);
        virtual  ~JveProjectMutexPrivate(void);
};


#endif // JVEPROJECTMUTEXPRIVATE_H


