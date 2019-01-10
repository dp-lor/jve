

#include "jveGuiVideoMonitorWindow.h"


#include <QEvent>
#include <QAction>


#include "../../core/definitions/jveDefines.h"
#include "../definitions/jveGuiWindowsSettingsDefines.h"


jveGuiVideoMonitorWindow::jveGuiVideoMonitorWindow(QWidget *parent)
    : jveGuiDockableWindow(
        parent,
        JVE_GUI_SETTINGS_VIDEO_MONITOR_WINDOW_GEOMETRY,
        JVE_GUI_SETTINGS_VIDEO_MONITOR_WINDOW_STATE,
        JVE_GUI_SETTINGS_VIDEO_MONITOR_WINDOW_EXTRA
    )
{
    // initial translate
    updateTranslations();
}

jveGuiVideoMonitorWindow::~jveGuiVideoMonitorWindow(void)
{
}

void
jveGuiVideoMonitorWindow::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    }
    jveGuiDockableWindow::changeEvent(event);
}

void
jveGuiVideoMonitorWindow::updateTranslations(void)
{
    // title
    setWindowTitle(
        tr("gui_video_monitor_window_title")
            .append(" - ")
            .append(JVE_NAME_STRING)
    );

    // toggle action
    mp_toggleAction->setText(
        tr("gui_video_monitor_window_toggle_window_action_text")
    );
    mp_toggleAction->setStatusTip(
        tr("gui_video_monitor_window_toggle_window_action_status_tip")
    );
}


