

#include "JveGuiProjectSettingsWindow.h"


#include <QEvent>
#include <QAction>


#include "../../core/definitions/JveDefines.h"
#include "../definitions/JveGuiWindowsSettingsDefines.h"


JveGuiProjectSettingsWindow::JveGuiProjectSettingsWindow(QWidget *parent)
    : JveGuiDockableWindow(
        parent,
        JVE_GUI_SETTINGS_PROJECT_SETTINGS_WINDOW_VISIBLE,
        JVE_GUI_SETTINGS_PROJECT_SETTINGS_WINDOW_GEOMETRY,
        JVE_GUI_SETTINGS_PROJECT_SETTINGS_WINDOW_EXTRA
    )
{
    // initial translate
    updateTranslations();
}

JveGuiProjectSettingsWindow::~JveGuiProjectSettingsWindow(void)
{
}

void
JveGuiProjectSettingsWindow::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    }
    JveGuiDockableWindow::changeEvent(event);
}

void
JveGuiProjectSettingsWindow::updateTranslations(void)
{
    // title
    setWindowTitle(
        tr("gui_project_settings_window_title")
            .append(" - ")
            .append(JVE_NAME_STRING)
    );

    // toggle action
    mp_toggleAction->setText(
        tr("gui_project_settings_window_toggle_window_action_text")
    );
    mp_toggleAction->setStatusTip(
        tr("gui_project_settings_window_toggle_window_action_status_tip")
    );
}


