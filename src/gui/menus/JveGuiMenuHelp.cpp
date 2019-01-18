

#include "JveGuiMenuHelp.h"


#include <QApplication>


#include "../../core/signals/JveGlobalSignals.h"


JveGuiMenuHelp::JveGuiMenuHelp(QWidget *parent)
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
        &JveGlobalSignals,
        SIGNAL(wantShowKeyboardShortcutsInfo())
    );

    // separator
    addSeparator();

    // about Jve
    addAction(&actionAboutJve);
    connect(
        &actionAboutJve,
        SIGNAL(triggered()),
        &JveGlobalSignals,
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

JveGuiMenuHelp::~JveGuiMenuHelp(void)
{
}

void
JveGuiMenuHelp::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    }
    QMenu::changeEvent(event);
}

void
JveGuiMenuHelp::updateTranslations(void)
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

    // about Jve
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


