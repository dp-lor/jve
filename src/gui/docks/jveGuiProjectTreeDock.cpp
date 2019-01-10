

#include "jveGuiProjectTreeDock.h"


#include <QEvent>
#include <QAction>


jveGuiProjectTreeDock::jveGuiProjectTreeDock(QMainWindow *parent)
    : jveGuiDock(parent),
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

jveGuiProjectTreeDock::~jveGuiProjectTreeDock(void)
{
}

void
jveGuiProjectTreeDock::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    }
    jveGuiDock::changeEvent(event);
}

void
jveGuiProjectTreeDock::updateTranslations(void)
{
    // title
    setWindowTitle(tr("gui_project_tree_dock_title"));
}


