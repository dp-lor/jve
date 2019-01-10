

#include "jveGuiProjectSettingsDock.h"


#include <QEvent>
#include <QAction>


#include "../windows/jveGuiProjectSettingsWindow.h"


jveGuiProjectSettingsDock::jveGuiProjectSettingsDock(QMainWindow *parent)
    : jveGuiWindowableDock(
        parent,
        new jveGuiProjectSettingsWindow(parent)
    ),
        mp_scrollArea(this),
        mp_view(this)
{
    // properties
    setObjectName("project-settings-dock");

    // scroll area
    mp_scrollArea.setFocusPolicy(Qt::NoFocus);
    mp_scrollArea.setWidgetResizable(true);
    mp_scrollArea.setSizePolicy(
        QSizePolicy::Expanding,
        QSizePolicy::Expanding
    );

    // real view
    mp_scrollArea.setWidget(&mp_view);

    // scroll area as view
    setView(&mp_scrollArea);

    // initial translate
    updateTranslations();
}

jveGuiProjectSettingsDock::~jveGuiProjectSettingsDock(void)
{
}

void
jveGuiProjectSettingsDock::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    }
    jveGuiWindowableDock::changeEvent(event);
}

void
jveGuiProjectSettingsDock::updateTranslations(void)
{
    // title
    setWindowTitle(tr("gui_project_settings_dock_title"));

    // toggle view action
    mp_toggleViewAction->setText(
        tr("gui_project_settings_dock_toggle_view_action_text")
    );
    mp_toggleViewAction->setStatusTip(
        tr("gui_project_settings_dock_toggle_view_action_status_tip")
    );
}


