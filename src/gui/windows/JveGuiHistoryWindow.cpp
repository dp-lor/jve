

#include "JveGuiHistoryWindow.h"


#include <QEvent>
#include <QAction>


#include "../../core/definitions/JveDefines.h"
#include "../definitions/JveGuiWindowsSettingsDefines.h"


JveGuiHistoryWindow::JveGuiHistoryWindow(QWidget *parent)
    : JveGuiDockableWindow(
        parent,
        JVE_GUI_SETTINGS_HISTORY_WINDOW_VISIBLE,
        JVE_GUI_SETTINGS_HISTORY_WINDOW_GEOMETRY,
        JVE_GUI_SETTINGS_HISTORY_WINDOW_EXTRA
    )
{
    // initial translate
    updateTranslations();
}

JveGuiHistoryWindow::~JveGuiHistoryWindow(void)
{
}

void
JveGuiHistoryWindow::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    }
    JveGuiDockableWindow::changeEvent(event);
}

void
JveGuiHistoryWindow::updateTranslations(void)
{
    // title
    setWindowTitle(
        tr("gui_history_window_title")
            .append(" - ")
            .append(JVE_NAME_STRING)
    );

    // toggle action
    mp_toggleAction->setText(
        tr("gui_history_window_toggle_window_action_text")
    );
    mp_toggleAction->setStatusTip(
        tr("gui_history_window_toggle_window_action_status_tip")
    );
}


