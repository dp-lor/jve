

#include "JveGuiHistoryDock.h"


#include <QEvent>
#include <QAction>


#include "../windows/JveGuiHistoryWindow.h"


JveGuiHistoryDock::JveGuiHistoryDock(QMainWindow *parent)
    : JveGuiWindowableDock(
        parent,
        new JveGuiHistoryWindow(parent)
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

JveGuiHistoryDock::~JveGuiHistoryDock(void)
{
}

void
JveGuiHistoryDock::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    }
    JveGuiWindowableDock::changeEvent(event);
}

void
JveGuiHistoryDock::updateTranslations(void)
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


