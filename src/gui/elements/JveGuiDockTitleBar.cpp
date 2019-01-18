

#include "JveGuiDockTitleBar.h"
#include "../definitions/JveGuiAppearanceDefines.h"


#include <QEvent>


JveGuiDockTitleBar::JveGuiDockTitleBar(QWidget *parent)
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

JveGuiDockTitleBar::~JveGuiDockTitleBar(void)
{
}

void
JveGuiDockTitleBar::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    }
    QWidget::changeEvent(event);
}

void
JveGuiDockTitleBar::toggleTabifiedMode(const bool toTabified)
{
    mp_layout.setContentsMargins(
        0,
        toTabified ? JVE_GUI_VERTICAL_SPACE : 0,
        0,
        JVE_GUI_VERTICAL_SPACE
    );
}

void
JveGuiDockTitleBar::updateTranslations(void)
{
    // tooltip
    setToolTip(tr("gui_dock_title_bar_tool_tip"));
}


