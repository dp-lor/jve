

#ifndef JVEGUIWINDOWABLEDOCK_H
#define JVEGUIWINDOWABLEDOCK_H


#include "jveGuiDock.h"


#include <QVBoxLayout>


class jveGuiDockableWindow;


class jveGuiWindowableDock : public jveGuiDock
{
    Q_OBJECT
    public:
        explicit jveGuiWindowableDock(
            QMainWindow          *parent,
            jveGuiDockableWindow *window
        );
        virtual ~jveGuiWindowableDock(void);
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
        jveGuiDockableWindow *mp_window;
        QAction              *mp_toggleWindowAction;
};


#endif // JVEGUIWINDOWABLEDOCK_H


