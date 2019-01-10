

#ifndef JVEGUIVIDEOMONITORDOCK_H
#define JVEGUIVIDEOMONITORDOCK_H


#include "jveGuiWindowableDock.h"


#include "../views/jveGuiVideoMonitorView.h"


class QEvent;


class jveGuiVideoMonitorDock : public jveGuiWindowableDock
{
    Q_OBJECT
    public:
        explicit  jveGuiVideoMonitorDock(QMainWindow *parent);
        virtual  ~jveGuiVideoMonitorDock(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateTranslations(void);
    private:
        // members
        jveGuiVideoMonitorView mp_view;
};


#endif // JVEGUIVIDEOMONITORDOCK_H


