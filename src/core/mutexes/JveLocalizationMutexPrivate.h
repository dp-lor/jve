

#ifndef JVELOCALIZATIONMUTEXPRIVATE_H
#define JVELOCALIZATIONMUTEXPRIVATE_H


#include <QMutex>


class JveLocalizationMutexPrivate : public QMutex
{
    public:
        explicit  JveLocalizationMutexPrivate(void);
        virtual  ~JveLocalizationMutexPrivate(void);
};


#endif // JVELOCALIZATIONMUTEXPRIVATE_H


