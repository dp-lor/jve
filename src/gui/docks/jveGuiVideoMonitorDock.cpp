

#include "jveGuiVideoMonitorDock.h"


#include <QEvent>
#include <QAction>


#include "../windows/jveGuiVideoMonitorWindow.h"


jveGuiVideoMonitorDock::jveGuiVideoMonitorDock(QMainWindow *parent)
    : jveGuiWindowableDock(
        parent,
        new jveGuiVideoMonitorWindow(parent)
    ),
        mp_view(this)
{
    // properties
    setObjectName("video-monitor-dock");

    // view
    setView(&mp_view);

    // initial translate
    updateTranslations();
}

jveGuiVideoMonitorDock::~jveGuiVideoMonitorDock(void)
{
}

void
jveGuiVideoMonitorDock::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    }
    jveGuiWindowableDock::changeEvent(event);
}

void
jveGuiVideoMonitorDock::updateTranslations(void)
{
    // title
    setWindowTitle(tr("gui_video_monitor_dock_title"));

    // toggle view action
    mp_toggleViewAction->setText(
        tr("gui_video_monitor_dock_toggle_view_action_text")
    );
    mp_toggleViewAction->setStatusTip(
        tr("gui_video_monitor_dock_toggle_view_action_status_tip")
    );
}


