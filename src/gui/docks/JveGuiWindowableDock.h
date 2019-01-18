

#ifndef JVEGUIWINDOWABLEDOCK_H
#define JVEGUIWINDOWABLEDOCK_H


#include "JveGuiDock.h"


#include <QVBoxLayout>


class JveGuiDockableWindow;


class JveGuiWindowableDock : public JveGuiDock
{
    Q_OBJECT
    public:
        explicit JveGuiWindowableDock(
            QMainWindow          *parent,
            JveGuiDockableWindow *window
        );
        virtual ~JveGuiWindowableDock(void);
    public:
        void setView(QWidget *view);
        void setUp(void);
        void upSet(void);
    public:
        QAction * toggleWindowAction(void);
    protected:
        void attachViewToSelf(void);
        void attachViewToWindow(void);
    protected slots:
        void slotViewTogglerTriggered(const bool toVisible);
        void slotWindowTogglerTriggered(const bool toVisible);
        void slotWindowClosedWithoutToggler(void);
    protected:
        // members
        QWidget               mp_protectedWrapper;
        QVBoxLayout           mp_protectedWrapperLayout;
        QWidget              *mp_protectedView;
        JveGuiDockableWindow *mp_window;
        QAction              *mp_toggleWindowAction;
};


#endif // JVEGUIWINDOWABLEDOCK_H


