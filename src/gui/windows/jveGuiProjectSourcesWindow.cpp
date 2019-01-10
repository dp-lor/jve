

#include "jveGuiProjectSourcesWindow.h"


#include <QEvent>
#include <QAction>


#include "../../core/definitions/jveDefines.h"
#include "../definitions/jveGuiWindowsSettingsDefines.h"


jveGuiProjectSourcesWindow::jveGuiProjectSourcesWindow(QWidget *parent)
    : jveGuiDockableWindow(
        parent,
        JVE_GUI_SETTINGS_PROJECT_SOURCES_WINDOW_GEOMETRY,
        JVE_GUI_SETTINGS_PROJECT_SOURCES_WINDOW_STATE,
        JVE_GUI_SETTINGS_PROJECT_SOURCES_WINDOW_EXTRA
    )
{
    // initial translate
    updateTranslations();
}

jveGuiProjectSourcesWindow::~jveGuiProjectSourcesWindow(void)
{
}

void
jveGuiProjectSourcesWindow::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    }
    jveGuiDockableWindow::changeEvent(event);
}

void
jveGuiProjectSourcesWindow::updateTranslations(void)
{
    // title
    setWindowTitle(
        tr("gui_project_sources_window_title")
            .append(" - ")
            .append(JVE_NAME_STRING)
    );

    // toggle action
    mp_toggleAction->setText(
        tr("gui_project_sources_window_toggle_window_action_text")
    );
    mp_toggleAction->setStatusTip(
        tr("gui_project_sources_window_toggle_window_action_status_tip")
    );
}


