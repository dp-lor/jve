

#include "jveGuiProjectSourcesViewBar.h"


#include <QEvent>


#include "../definitions/jveGuiMediaDefines.h"
#include "../definitions/jveGuiAppearanceDefines.h"

#include "../../core/signals/jveProjectSourcesSignals.h"


jveGuiProjectSourcesViewBar::jveGuiProjectSourcesViewBar(QWidget *parent)
    : QWidget(parent),
        searchWidget(this),
        mp_layout(this),
        mp_buttonAddMediaItems(this, JVE_GUI_ICON_ADD_MEDIA_ITEM),
        mp_buttonAddImagesSequenceItem(
            this,
            JVE_GUI_ICON_ADD_IMAGES_SEQUENCE_ITEM
        )
{
    // properties
    setFocusPolicy(Qt::NoFocus);
    setSizePolicy(
        QSizePolicy::Expanding,
        QSizePolicy::Minimum
    );
    setContentsMargins(
        0,
        0,
        0,
        JVE_GUI_VERTICAL_SPACE
    );

    // layout
    mp_layout.setMargin(0);
    mp_layout.setSpacing(JVE_GUI_TOOLS_LAYOUT_SPACING);
    mp_layout.setAlignment(Qt::AlignVCenter);

    // search widget
    mp_layout.addWidget(&searchWidget);

    // add media items button
    mp_layout.addWidget(&mp_buttonAddMediaItems);
    connect(
        &mp_buttonAddMediaItems,
        SIGNAL(clicked()),
        &jveProjectSourcesSignals,
        SIGNAL(wantShowAddMediaItemsDialog()),
        Qt::DirectConnection
    );

    // add images sequence item button
    mp_layout.addWidget(&mp_buttonAddImagesSequenceItem);
    connect(
        &mp_buttonAddImagesSequenceItem,
        SIGNAL(clicked()),
        &jveProjectSourcesSignals,
        SIGNAL(wantShowAddImagesSequenceItemDialog()),
        Qt::DirectConnection
    );

    // initial translate
    updateTranslations();
}

jveGuiProjectSourcesViewBar::~jveGuiProjectSourcesViewBar(void)
{
}

void
jveGuiProjectSourcesViewBar::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    }
    QWidget::changeEvent(event);
}

void
jveGuiProjectSourcesViewBar::updateTranslations(void)
{
    // search input
    searchWidget.searchInput.setToolTip(
        tr("gui_project_sources_view_bar_search_input_tool_tip")
    );

    // add media items button
    mp_buttonAddMediaItems.setToolTip(
        tr("gui_project_sources_view_bar_add_media_items_button_tool_tip")
    );

    // add images sequence item button
    mp_buttonAddImagesSequenceItem.setToolTip(
        tr("gui_project_sources_view_bar_add_images_sequence_item_button_tool_tip")
    );
}


