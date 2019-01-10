

#ifndef JVEGUIDOCK_H
#define JVEGUIDOCK_H


#include <QDockWidget>
#include <QMainWindow>


#include "../elements/jveGuiDockTitleBar.h"


class QAction;


class jveGuiDock : public QDockWidget
{
    Q_OBJECT
    public:
        explicit  jveGuiDock(QMainWindow *parent);
        virtual  ~jveGuiDock(void);
    public:
        void toggleTabifiedMode(const bool toTabified);
    protected slots:
        void slotCatchDockLocationChanged(Qt::DockWidgetArea area);
    protected:
        // members
        jveGuiDockTitleBar  mp_titleBar;
        QMainWindow        *mp_mainWindow;
        QAction            *mp_toggleViewAction;
};


#endif // JVEGUIDOCKWIDGET_H


