

#include "JveGuiProjectSourcesDock.h"


#include <QEvent>
#include <QAction>


#include "../windows/JveGuiProjectSourcesWindow.h"


JveGuiProjectSourcesDock::JveGuiProjectSourcesDock(QMainWindow *parent)
    : JveGuiWindowableDock(
        parent,
        new JveGuiProjectSourcesWindow(parent)
    ),
        mp_view(this)
{
    // properties
    setObjectName("project-sources-dock");

    // view
    setView(&mp_view);

    // initial translate
    updateTranslations();
}

JveGuiProjectSourcesDock::~JveGuiProjectSourcesDock(void)
{
}

void
JveGuiProjectSourcesDock::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    }
    JveGuiWindowableDock::changeEvent(event);
}

void
JveGuiProjectSourcesDock::updateTranslations(void)
{
    // title
    setWindowTitle(tr("gui_project_sources_dock_title"));

    // toggle view action
    mp_toggleViewAction->setText(
        tr("gui_project_sources_dock_toggle_view_action_text")
    );
    mp_toggleViewAction->setStatusTip(
        tr("gui_project_sources_dock_toggle_view_action_status_tip")
    );
}


