

#include "jveGuiDockTitleBar.h"
#include "../definitions/jveGuiAppearanceDefines.h"


#include <QEvent>


jveGuiDockTitleBar::jveGuiDockTitleBar(QWidget *parent)
    : QWidget(parent),
        mp_layout(this),
        mp_trail(this)
{
    // properties
    setCursor(Qt::OpenHandCursor);
    setSizePolicy(
        QSizePolicy::Expanding,
        QSizePolicy::Minimum
    );

    // layout
    mp_layout.setContentsMargins(
        0,
        0,
        0,
        JVE_GUI_VERTICAL_SPACE
    );
    mp_layout.setSpacing(0);

    // trail
    mp_layout.addWidget(&mp_trail);

    // initial translate
    updateTranslations();
}

jveGuiDockTitleBar::~jveGuiDockTitleBar(void)
{
}

void
jveGuiDockTitleBar::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    }
    QWidget::changeEvent(event);
}

void
jveGuiDockTitleBar::toggleTabifiedMode(const bool toTabified)
{
    mp_layout.setContentsMargins(
        0,
        toTabified ? JVE_GUI_VERTICAL_SPACE : 0,
        0,
        JVE_GUI_VERTICAL_SPACE
    );
}

void
jveGuiDockTitleBar::updateTranslations(void)
{
    // tooltip
    setToolTip(tr("gui_dock_title_bar_tool_tip"));
}


