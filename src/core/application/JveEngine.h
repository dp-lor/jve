

#ifndef JVEENGINE_H
#define JVEENGINE_H


#include <QObject>


class JveEngine : public QObject
{
    Q_OBJECT
    public:
        explicit  JveEngine(QObject *parent);
        virtual  ~JveEngine(void);
    public:
        void process(void);
};


#endif // JVEENGINE_H


