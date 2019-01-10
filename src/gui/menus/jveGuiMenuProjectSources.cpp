

#include "jveGuiMenuProjectSources.h"


#include <QEvent>


#include "../../core/definitions/jveState.h"

#include "../../core/signals/jveGlobalSignals.h"
#include "../../core/signals/jveProjectSourcesSignals.h"


jveGuiMenuProjectSources::jveGuiMenuProjectSources(QWidget *parent)
    : QMenu(parent),
        // actions
        actionProperties(this),
        actionRemove(this),
        actionAddMediaItems(this),
        actionAddImagesSequenceItem(this),
        actionRemoveUnused(this),
        // private members
        mp_targetRow(-1)
{
    // properties
    addAction(&actionProperties);
    connect(
        &actionProperties,
        SIGNAL(triggered()),
        this,
        SLOT(slotActionPropertiesTriggered()),
        Qt::DirectConnection
    );
    // remove
    addAction(&actionRemove);
    connect(
        &actionRemove,
        SIGNAL(triggered()),
        this,
        SLOT(slotActionRemoveTriggered()),
        Qt::DirectConnection
    );

    // separator
    addSeparator();

    // add media items
    addAction(&actionAddMediaItems);
    connect(
        &actionAddMediaItems,
        SIGNAL(triggered()),
        &jveProjectSourcesSignals,
        SIGNAL(wantShowAddMediaItemsDialog()),
        Qt::DirectConnection
    );
    // add images sequence item
    addAction(&actionAddImagesSequenceItem);
    connect(
        &actionAddImagesSequenceItem,
        SIGNAL(triggered()),
        &jveProjectSourcesSignals,
        SIGNAL(wantShowAddImagesSequenceItemDialog()),
        Qt::DirectConnection
    );

    // separator
    addSeparator();

    // remove unused
    addAction(&actionRemoveUnused);
    connect(
        &actionRemoveUnused,
        SIGNAL(triggered()),
        &jveProjectSourcesSignals,
        SIGNAL(wantRemoveUnusedItems()),
        Qt::DirectConnection
    );

    // initial state
    slotSetState(jveState::None);
    // initial translate
    updateTranslations();

    // slot set state
    connect(
        &jveGlobalSignals,
        SIGNAL(stateChanged(int)),
        this,
        SLOT(slotSetState(int)),
        Qt::QueuedConnection
    );
}

jveGuiMenuProjectSources::~jveGuiMenuProjectSources(void)
{
}

void
jveGuiMenuProjectSources::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    }
    QMenu::changeEvent(event);
}

void
jveGuiMenuProjectSources::setTargetRow(const int row)
{
    bool isInvalidRow = 0 > row;

    mp_targetRow = row;

    actionProperties .setDisabled(isInvalidRow);
    actionRemove     .setDisabled(isInvalidRow);
}

void
jveGuiMenuProjectSources::updateTranslations(void)
{
    // menu action
    menuAction()->setText(tr("gui_menu_project_sources_text"));

    // properties
    actionProperties.setText(
        tr("gui_menu_project_sources_action_properties_text")
    );
    actionProperties.setStatusTip(
        tr("gui_menu_project_sources_action_properties_status_tip")
    );

    // remove
    actionRemove.setText(
        tr("gui_menu_project_sources_action_remove_text")
    );
    actionRemove.setStatusTip(
        tr("gui_menu_project_sources_action_remove_status_tip")
    );

    // add media items
    actionAddMediaItems.setText(
        tr("gui_menu_project_sources_add_media_items_action_text")
    );
    actionAddMediaItems.setStatusTip(
        tr("gui_menu_project_sources_add_media_items_action_status_tip")
    );

    // add images sequence item
    actionAddImagesSequenceItem.setText(
        tr("gui_menu_project_sources_add_images_sequence_item_action_text")
    );
    actionAddImagesSequenceItem.setStatusTip(
        tr("gui_menu_project_sources_add_images_sequence_item_action_status_tip")
    );

    // remove unused
    actionRemoveUnused.setText(
        tr("gui_menu_project_sources_action_remove_unused_text")
    );
    actionRemoveUnused.setStatusTip(
        tr("gui_menu_project_sources_action_remove_unused_status_tip")
    );
}

void
jveGuiMenuProjectSources::slotSetState(const int state)
{
    setDisabled(
        !(state & jveState::ProjectOpened)
            || state & jveState::Busy
    );
}

void
jveGuiMenuProjectSources::slotActionPropertiesTriggered(void)
{
    emit wantViewItemProperties(mp_targetRow);
}

void
jveGuiMenuProjectSources::slotActionRemoveTriggered(void)
{
    emit wantRemoveItem(mp_targetRow);
}


