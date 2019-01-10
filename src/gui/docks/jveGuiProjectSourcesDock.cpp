

#include "jveGuiProjectSourcesDock.h"


#include <QEvent>
#include <QAction>


#include "../windows/jveGuiProjectSourcesWindow.h"


jveGuiProjectSourcesDock::jveGuiProjectSourcesDock(QMainWindow *parent)
    : jveGuiWindowableDock(
        parent,
        new jveGuiProjectSourcesWindow(parent)
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

jveGuiProjectSourcesDock::~jveGuiProjectSourcesDock(void)
{
}

void
jveGuiProjectSourcesDock::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    }
    jveGuiWindowableDock::changeEvent(event);
}

void
jveGuiProjectSourcesDock::updateTranslations(void)
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


