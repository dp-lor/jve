

#include "jveGuiMenuWindow.h"


jveGuiMenuWindow::jveGuiMenuWindow(QWidget *parent)
    : QMenu(parent)
{
    // initial translate
    updateTranslations();
}

jveGuiMenuWindow::~jveGuiMenuWindow(void)
{
}

void
jveGuiMenuWindow::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    }
    QMenu::changeEvent(event);
}

void
jveGuiMenuWindow::updateTranslations(void)
{
    // menu action
    menuAction()->setText(tr("gui_menu_window_text"));
}


