

#ifndef JVEGUIDOCK_H
#define JVEGUIDOCK_H


#include <QDockWidget>
#include <QMainWindow>


#include "../elements/JveGuiDockTitleBar.h"


class QAction;


class JveGuiDock : public QDockWidget
{
    Q_OBJECT
    public:
        explicit  JveGuiDock(QMainWindow *parent);
        virtual  ~JveGuiDock(void);
    public:
        void toggleTabifiedMode(const bool toTabified);
    protected slots:
        void slotCatchDockLocationChanged(Qt::DockWidgetArea area);
    protected:
        // members
        JveGuiDockTitleBar  mp_titleBar;
        QMainWindow        *mp_mainWindow;
        QAction            *mp_toggleViewAction;
};


#endif // JVEGUIDOCKWIDGET_H


