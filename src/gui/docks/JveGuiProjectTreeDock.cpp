

#include "JveGuiProjectTreeDock.h"


#include <QEvent>
#include <QAction>


JveGuiProjectTreeDock::JveGuiProjectTreeDock(QMainWindow *parent)
    : JveGuiDock(parent),
        mp_view(this)
{
    // properties
    setObjectName("project-tree-dock");
    mp_toggleViewAction->setEnabled(false);

    // view
    setWidget(&mp_view);

    // initial translate
    updateTranslations();
}

JveGuiProjectTreeDock::~JveGuiProjectTreeDock(void)
{
}

void
JveGuiProjectTreeDock::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    }
    JveGuiDock::changeEvent(event);
}

void
JveGuiProjectTreeDock::updateTranslations(void)
{
    // title
    setWindowTitle(tr("gui_project_tree_dock_title"));
}


