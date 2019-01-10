

#include "jveGuiHistoryDock.h"


#include <QEvent>
#include <QAction>


#include "../windows/jveGuiHistoryWindow.h"


jveGuiHistoryDock::jveGuiHistoryDock(QMainWindow *parent)
    : jveGuiWindowableDock(
        parent,
        new jveGuiHistoryWindow(parent)
    ),
        mp_view(this)
{
    // properties
    setObjectName("history-dock");

    // view
    setView(&mp_view);

    // initial translate
    updateTranslations();
}

jveGuiHistoryDock::~jveGuiHistoryDock(void)
{
}

void
jveGuiHistoryDock::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    }
    jveGuiWindowableDock::changeEvent(event);
}

void
jveGuiHistoryDock::updateTranslations(void)
{
    // title
    setWindowTitle(tr("gui_history_dock_title"));

    // toggle view action
    mp_toggleViewAction->setText(
        tr("gui_history_dock_toggle_view_action_text")
    );
    mp_toggleViewAction->setStatusTip(
        tr("gui_history_dock_toggle_view_action_status_tip")
    );
}


