

#include "JveGuiDock.h"


#include <QAction>
#include <QList>


JveGuiDock::JveGuiDock(QMainWindow *parent)
    : QDockWidget(parent),
        mp_titleBar(this),
        mp_mainWindow(parent),
        mp_toggleViewAction(toggleViewAction())
{
    // properties
    setFocusPolicy(Qt::NoFocus);
    setAllowedAreas(Qt::AllDockWidgetAreas);
    setFeatures(
        QDockWidget::NoDockWidgetFeatures
            | QDockWidget::DockWidgetClosable
            | QDockWidget::DockWidgetMovable
    );
    setContentsMargins(0, 0, 0, 0);

    // toggle action
    mp_toggleViewAction->setAutoRepeat(false);

    // title bar
    setTitleBarWidget(&mp_titleBar);

    // location changed
    connect(
        this,
        SIGNAL(dockLocationChanged(Qt::DockWidgetArea)),
        this,
        SLOT(slotCatchDockLocationChanged(Qt::DockWidgetArea)),
        Qt::DirectConnection
    );
}

JveGuiDock::~JveGuiDock(void)
{
}

void
JveGuiDock::toggleTabifiedMode(const bool toTabified)
{
    mp_titleBar.toggleTabifiedMode(toTabified);
}

void
JveGuiDock::slotCatchDockLocationChanged(Qt::DockWidgetArea area)
{
    Q_UNUSED(area);

    QList<JveGuiDock *> docks
        = mp_mainWindow->findChildren<JveGuiDock *>();

    for (int i = 0; i < docks.size(); i++) {
        JveGuiDock *dock = docks.at(i);
        dock->toggleTabifiedMode(
            0 < mp_mainWindow->tabifiedDockWidgets(dock).size()
        );
    }
}


