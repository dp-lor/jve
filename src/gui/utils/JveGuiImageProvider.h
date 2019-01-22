

#ifndef JVEGUIIMAGEPROVIDER_H
#define JVEGUIIMAGEPROVIDER_H


#include <QObject>


class JveGuiImageProvider : public QObject
{
    Q_OBJECT
    public:
        explicit  JveGuiImageProvider(void);
        virtual  ~JveGuiImageProvider(void);
};


#endif // JVEGUIIMAGEPROVIDER_H


