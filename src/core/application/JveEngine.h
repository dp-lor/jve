

#ifndef JVEENGINE_H
#define JVEENGINE_H


#include <QObject>


class JveEngine : public QObject
{
    Q_OBJECT
    public:
        explicit  JveEngine(void);
        virtual  ~JveEngine(void);
    public slots:
        void slotWakeUp(void);
};


#endif // JVEENGINE_H


