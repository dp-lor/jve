

#ifndef JVEGUIVIDEOMONITORWINDOW_H
#define JVEGUIVIDEOMONITORWINDOW_H


#include "JveGuiDockableWindow.h"


class QEvent;


class JveGuiVideoMonitorWindow : public JveGuiDockableWindow
{
    Q_OBJECT
    public:
        explicit  JveGuiVideoMonitorWindow(QWidget *parent);
        virtual  ~JveGuiVideoMonitorWindow(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateTranslations(void);
};


#endif // JVEGUIVIDEOMONITORWINDOW_H


