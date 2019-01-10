

#ifndef JVELOCALIZATIONMUTEXPRIVATE_H
#define JVELOCALIZATIONMUTEXPRIVATE_H


#include <QMutex>


class jveLocalizationMutexPrivate : public QMutex
{
    public:
        explicit  jveLocalizationMutexPrivate(void);
        virtual  ~jveLocalizationMutexPrivate(void);
};


#endif // JVELOCALIZATIONMUTEXPRIVATE_H


