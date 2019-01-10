

#include "jveGuiMenuHelp.h"


#include <QApplication>


#include "../../core/signals/jveGlobalSignals.h"


jveGuiMenuHelp::jveGuiMenuHelp(QWidget *parent)
    : QMenu(parent),
        actionKeyboardShortcuts(this),
        actionAboutJve(this),
        actionAboutQt(this)
{
    // keyboard shortcuts
    addAction(&actionKeyboardShortcuts);
    connect(
        &actionKeyboardShortcuts,
        SIGNAL(triggered()),
        &jveGlobalSignals,
        SIGNAL(wantShowKeyboardShortcutsInfo())
    );

    // separator
    addSeparator();

    // about jve
    addAction(&actionAboutJve);
    connect(
        &actionAboutJve,
        SIGNAL(triggered()),
        &jveGlobalSignals,
        SIGNAL(wantShowAboutJveDialog())
    );

    // about qt
    addAction(&actionAboutQt);
    connect(
        &actionAboutQt,
        SIGNAL(triggered()),
        qApp,
        SLOT(aboutQt())
    );

    // initial translate
    updateTranslations();
}

jveGuiMenuHelp::~jveGuiMenuHelp(void)
{
}

void
jveGuiMenuHelp::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    }
    QMenu::changeEvent(event);
}

void
jveGuiMenuHelp::updateTranslations(void)
{
    // menu action
    menuAction()->setText(tr("gui_menu_help_text"));

    // keyboard shortcuts
    actionKeyboardShortcuts.setText(
        tr("gui_menu_help_action_keyboard_shortcuts_text")
    );
    actionKeyboardShortcuts.setStatusTip(
        tr("gui_menu_help_action_keyboard_shortcuts_status_tip")
    );

    // about jve
    actionAboutJve.setText(
        tr("gui_menu_help_action_about_jve_text")
    );
    actionAboutJve.setStatusTip(
        tr("gui_menu_help_action_about_jve_status_tip")
    );

    // about qt
    actionAboutQt.setText(
        tr("gui_menu_help_action_about_qt_text")
    );
    actionAboutQt.setStatusTip(
        tr("gui_menu_help_action_about_qt_status_tip")
    );
}


