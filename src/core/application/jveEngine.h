

#ifndef JVEENGINE_H
#define JVEENGINE_H


#include <QObject>


class jveEngine : public QObject
{
    Q_OBJECT
    public:
        explicit  jveEngine(QObject *parent);
        virtual  ~jveEngine(void);
    public:
        void process(void);
};


#endif // JVEENGINE_H


