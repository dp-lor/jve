

#include "JveGuiProjectSettingsDock.h"


#include <QEvent>
#include <QAction>


#include "../windows/JveGuiProjectSettingsWindow.h"


JveGuiProjectSettingsDock::JveGuiProjectSettingsDock(QMainWindow *parent)
    : JveGuiWindowableDock(
        parent,
        new JveGuiProjectSettingsWindow(parent)
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

JveGuiProjectSettingsDock::~JveGuiProjectSettingsDock(void)
{
}

void
JveGuiProjectSettingsDock::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    }
    JveGuiWindowableDock::changeEvent(event);
}

void
JveGuiProjectSettingsDock::updateTranslations(void)
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


