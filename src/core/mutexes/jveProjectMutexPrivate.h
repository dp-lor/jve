

#ifndef JVEPROJECTMUTEXPRIVATE_H
#define JVEPROJECTMUTEXPRIVATE_H


#include <QMutex>


class jveProjectMutexPrivate : public QMutex
{
    public:
        explicit  jveProjectMutexPrivate(void);
        virtual  ~jveProjectMutexPrivate(void);
};


#endif // JVEPROJECTMUTEXPRIVATE_H


