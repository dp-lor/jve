

#include "JveGuiVideoMonitorWindow.h"


#include <QEvent>
#include <QAction>


#include "../../core/definitions/JveDefines.h"
#include "../definitions/JveGuiWindowsSettingsDefines.h"


JveGuiVideoMonitorWindow::JveGuiVideoMonitorWindow(QWidget *parent)
    : JveGuiDockableWindow(
        parent,
        JVE_GUI_SETTINGS_VIDEO_MONITOR_WINDOW_VISIBLE,
        JVE_GUI_SETTINGS_VIDEO_MONITOR_WINDOW_GEOMETRY,
        JVE_GUI_SETTINGS_VIDEO_MONITOR_WINDOW_EXTRA
    )
{
    // initial translate
    updateTranslations();
}

JveGuiVideoMonitorWindow::~JveGuiVideoMonitorWindow(void)
{
}

void
JveGuiVideoMonitorWindow::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    }
    JveGuiDockableWindow::changeEvent(event);
}

void
JveGuiVideoMonitorWindow::updateTranslations(void)
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


