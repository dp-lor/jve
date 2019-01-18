

#include "JveGuiVideoMonitorDock.h"


#include <QEvent>
#include <QAction>


#include "../windows/JveGuiVideoMonitorWindow.h"


JveGuiVideoMonitorDock::JveGuiVideoMonitorDock(QMainWindow *parent)
    : JveGuiWindowableDock(
        parent,
        new JveGuiVideoMonitorWindow(parent)
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

JveGuiVideoMonitorDock::~JveGuiVideoMonitorDock(void)
{
}

void
JveGuiVideoMonitorDock::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    }
    JveGuiWindowableDock::changeEvent(event);
}

void
JveGuiVideoMonitorDock::updateTranslations(void)
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


