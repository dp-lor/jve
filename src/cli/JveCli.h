

#ifndef JVECLI_H
#define JVECLI_H


#include <QObject>


#include "../core/application/JveReport.h"


class JveCli : public QObject
{
    Q_OBJECT
    public:
        explicit  JveCli(void);
        virtual  ~JveCli(void);
    private slots:
        void slotQuitAccepted(void);
        void slotStateChanged(const int state);
        void slotShowReport(const JveReport &report);
};


#endif // JVECLI_H


