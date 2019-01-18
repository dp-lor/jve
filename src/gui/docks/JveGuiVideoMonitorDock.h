

#ifndef JVEGUIVIDEOMONITORDOCK_H
#define JVEGUIVIDEOMONITORDOCK_H


#include "JveGuiWindowableDock.h"


#include "../views/JveGuiVideoMonitorView.h"


class QEvent;


class JveGuiVideoMonitorDock : public JveGuiWindowableDock
{
    Q_OBJECT
    public:
        explicit  JveGuiVideoMonitorDock(QMainWindow *parent);
        virtual  ~JveGuiVideoMonitorDock(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateTranslations(void);
    private:
        // members
        JveGuiVideoMonitorView mp_view;
};


#endif // JVEGUIVIDEOMONITORDOCK_H


