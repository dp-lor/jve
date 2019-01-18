

#include "jveGuiHistoryWindow.h"


#include <QEvent>
#include <QAction>


#include "../../core/definitions/jveDefines.h"
#include "../definitions/jveGuiWindowsSettingsDefines.h"


jveGuiHistoryWindow::jveGuiHistoryWindow(QWidget *parent)
    : jveGuiDockableWindow(
        parent,
        JVE_GUI_SETTINGS_HISTORY_WINDOW_VISIBLE,
        JVE_GUI_SETTINGS_HISTORY_WINDOW_GEOMETRY,
        JVE_GUI_SETTINGS_HISTORY_WINDOW_EXTRA
    )
{
    // initial translate
    updateTranslations();
}

jveGuiHistoryWindow::~jveGuiHistoryWindow(void)
{
}

void
jveGuiHistoryWindow::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    }
    jveGuiDockableWindow::changeEvent(event);
}

void
jveGuiHistoryWindow::updateTranslations(void)
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


