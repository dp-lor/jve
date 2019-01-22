

#ifndef JVEGUIIMAGEPROVIDERTHREAD_H
#define JVEGUIIMAGEPROVIDERTHREAD_H


#include <QThread>


#include "JveGuiImageProvider.h"


class JveGuiImageProviderThread : public QThread
{
    Q_OBJECT
    public:
        explicit  JveGuiImageProviderThread(void);
        virtual  ~JveGuiImageProviderThread(void);
    private:
        // members
        JveGuiImageProvider mp_imageProvider;
};


#endif // JVEGUIIMAGEPROVIDERTHREAD_H


