

#include "jveGuiDock.h"


#include <QAction>
#include <QList>


jveGuiDock::jveGuiDock(QMainWindow *parent)
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

jveGuiDock::~jveGuiDock(void)
{
}

void
jveGuiDock::toggleTabifiedMode(const bool toTabified)
{
    mp_titleBar.toggleTabifiedMode(toTabified);
}

void
jveGuiDock::slotCatchDockLocationChanged(Qt::DockWidgetArea area)
{
    Q_UNUSED(area);

    QList<jveGuiDock *> docks
        = mp_mainWindow->findChildren<jveGuiDock *>();

    for (int i = 0; i < docks.size(); i += 1) {
        jveGuiDock *dock = docks.at(i);
        dock->toggleTabifiedMode(
            0 < mp_mainWindow->tabifiedDockWidgets(dock).size()
        );
    }
}


