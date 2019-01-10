

#include "jveGuiProjectTreeView.h"


#include "../../core/application/jveSettings.h"
#include "../../core/signals/jveGlobalSignals.h"

#include "../definitions/jveGuiAppearanceDefines.h"
#include "../definitions/jveGuiSettingsDefines.h"


jveGuiProjectTreeView::jveGuiProjectTreeView(QWidget *parent)
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
        &jveGlobalSignals,
        SIGNAL(wantSetTransportBarPosition(bool)),
        this,
        SLOT(slotSetTransportBarPosition(bool)),
        Qt::DirectConnection
    );
}

jveGuiProjectTreeView::~jveGuiProjectTreeView()
{
    saveSettings();
}

void
jveGuiProjectTreeView::restoreSettings(void)
{
    jveSettings.lock();

    bool position = false;
    bool contains = jveSettings.contains(
        JVE_GUI_SETTINGS_PROJECT_TREE_TRANSPORT_BAR_POSITION
    );

    if (contains) {
        position = jveSettings.value(
            JVE_GUI_SETTINGS_PROJECT_TREE_TRANSPORT_BAR_POSITION
        ).toBool();
    }

    jveSettings.unlock();

    slotSetTransportBarPosition(position);
    emit jveGlobalSignals.wantSetUpTransportBarFeatures(position);
}

void
jveGuiProjectTreeView::saveSettings(void)
{
    jveSettings.lock();

    jveSettings.setValue(
        JVE_GUI_SETTINGS_PROJECT_TREE_TRANSPORT_BAR_POSITION,
        mp_transportBarPosition
    );

    jveSettings.sync();
    jveSettings.unlock();
}

void
jveGuiProjectTreeView::slotSetTransportBarPosition(const bool position)
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


