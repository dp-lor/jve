

#ifndef JVELOADINGPROJECTMUTEXPRIVATE_H
#define JVELOADINGPROJECTMUTEXPRIVATE_H


#include <QMutex>


class JveLoadingProjectMutexPrivate : public QMutex
{
    public:
        explicit  JveLoadingProjectMutexPrivate(void);
        virtual  ~JveLoadingProjectMutexPrivate(void);
};


#endif // JVELOADINGPROJECTMUTEXPRIVATE_H


