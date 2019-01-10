

#ifndef JVECLI_H
#define JVECLI_H


#include <QObject>


#include "../core/application/jveReport.h"


class jveCli : public QObject
{
    Q_OBJECT
    public:
        explicit  jveCli(void);
        virtual  ~jveCli(void);
    private slots:
        void slotQuitAccepted(void);
        void slotStateChanged(const int state);
        void slotShowReport(const jveReport &report);
};


#endif // JVECLI_H


