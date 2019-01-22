

#ifndef JVEIMAGEPROVIDERTHREAD_H
#define JVEIMAGEPROVIDERTHREAD_H


#include <QThread>


#include "JveImageProvider.h"


class JveImageProviderThread : public QThread
{
    Q_OBJECT
    public:
        explicit  JveImageProviderThread(void);
        virtual  ~JveImageProviderThread(void);
    private:
        // members
        JveImageProvider mp_imageProvider;
};


#endif // JVEIMAGEPROVIDERTHREAD_H


