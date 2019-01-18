

#include "JveGuiProjectTreeView.h"


#include "../../core/application/JveSettings.h"
#include "../../core/signals/JveGlobalSignals.h"

#include "../definitions/JveGuiAppearanceDefines.h"
#include "../definitions/JveGuiSettingsDefines.h"


JveGuiProjectTreeView::JveGuiProjectTreeView(QWidget *parent)
    : QWidget(parent),
        mp_transportBarPosition(false),
        mp_layout(this),
        mp_transportBar(this),
        mp_area(this)
{
    // properties
    setSizePolicy(
        QSizePolicy::Expanding,
        QSizePolicy::Expanding
    );

    // layout
    mp_layout.setMargin(0);
    mp_layout.setSpacing(0);

    // restore settings
    restoreSettings();

    // slot set transport bar position
    connect(
        &JveGlobalSignals,
        SIGNAL(wantSetTransportBarPosition(bool)),
        this,
        SLOT(slotSetTransportBarPosition(bool)),
        Qt::DirectConnection
    );
}

JveGuiProjectTreeView::~JveGuiProjectTreeView()
{
    saveSettings();
}

void
JveGuiProjectTreeView::restoreSettings(void)
{
    JveSettings.lock();

    bool position = false;
    bool contains = JveSettings.contains(
        JVE_GUI_SETTINGS_PROJECT_TREE_TRANSPORT_BAR_POSITION
    );

    if (contains) {
        position = JveSettings.value(
            JVE_GUI_SETTINGS_PROJECT_TREE_TRANSPORT_BAR_POSITION
        ).toBool();
    }

    JveSettings.unlock();

    slotSetTransportBarPosition(position);
    emit JveGlobalSignals.wantSetUpTransportBarFeatures(position);
}

void
JveGuiProjectTreeView::saveSettings(void)
{
    JveSettings.lock();

    JveSettings.setValue(
        JVE_GUI_SETTINGS_PROJECT_TREE_TRANSPORT_BAR_POSITION,
        mp_transportBarPosition
    );

    JveSettings.sync();
    JveSettings.unlock();
}

void
JveGuiProjectTreeView::slotSetTransportBarPosition(const bool position)
{
    mp_transportBarPosition = position;

    // bottom
    if (position) {
        mp_transportBar.setContentsMargins(
            0,
            JVE_GUI_VERTICAL_SPACE,
            0,
            JVE_GUI_VERTICAL_SPACE
        );
        mp_layout.insertWidget(0, &mp_area);
        mp_layout.insertWidget(1, &mp_transportBar);
    // top
    } else {
        mp_transportBar.setContentsMargins(
            0,
            0,
            0,
            JVE_GUI_VERTICAL_SPACE
        );
        mp_layout.insertWidget(0, &mp_transportBar);
        mp_layout.insertWidget(1, &mp_area);
    }
}


