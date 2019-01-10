

#ifndef JVEGUIVIDEOMONITORWINDOW_H
#define JVEGUIVIDEOMONITORWINDOW_H


#include "jveGuiDockableWindow.h"


class QEvent;


class jveGuiVideoMonitorWindow : public jveGuiDockableWindow
{
    Q_OBJECT
    public:
        explicit  jveGuiVideoMonitorWindow(QWidget *parent);
        virtual  ~jveGuiVideoMonitorWindow(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateTranslations(void);
};


#endif // JVEGUIVIDEOMONITORWINDOW_H


