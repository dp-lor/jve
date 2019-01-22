

#ifndef JVEIMAGEPROVIDER_H
#define JVEIMAGEPROVIDER_H


#include <QObject>


class JveImageProvider : public QObject
{
    Q_OBJECT
    public:
        explicit  JveImageProvider(void);
        virtual  ~JveImageProvider(void);
};


#endif // JVEIMAGEPROVIDER_H


