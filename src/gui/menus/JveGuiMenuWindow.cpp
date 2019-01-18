

#include "JveGuiMenuWindow.h"


JveGuiMenuWindow::JveGuiMenuWindow(QWidget *parent)
    : QMenu(parent)
{
    // initial translate
    updateTranslations();
}

JveGuiMenuWindow::~JveGuiMenuWindow(void)
{
}

void
JveGuiMenuWindow::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    }
    QMenu::changeEvent(event);
}

void
JveGuiMenuWindow::updateTranslations(void)
{
    // menu action
    menuAction()->setText(tr("gui_menu_window_text"));
}


