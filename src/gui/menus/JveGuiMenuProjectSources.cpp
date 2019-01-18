

#include "JveGuiMenuProjectSources.h"


#include <QEvent>


#include "../../core/definitions/JveState.h"

#include "../../core/signals/JveGlobalSignals.h"
#include "../../core/signals/JveProjectSourcesSignals.h"


JveGuiMenuProjectSources::JveGuiMenuProjectSources(QWidget *parent)
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
        &JveProjectSourcesSignals,
        SIGNAL(wantShowAddMediaItemsDialog()),
        Qt::DirectConnection
    );
    // add images sequence item
    addAction(&actionAddImagesSequenceItem);
    connect(
        &actionAddImagesSequenceItem,
        SIGNAL(triggered()),
        &JveProjectSourcesSignals,
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
        &JveProjectSourcesSignals,
        SIGNAL(wantRemoveUnusedItems()),
        Qt::DirectConnection
    );

    // initial state
    slotSetState(JveState::None);
    // initial translate
    updateTranslations();

    // slot set state
    connect(
        &JveGlobalSignals,
        SIGNAL(stateChanged(int)),
        this,
        SLOT(slotSetState(int)),
        Qt::QueuedConnection
    );
}

JveGuiMenuProjectSources::~JveGuiMenuProjectSources(void)
{
}

void
JveGuiMenuProjectSources::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    }
    QMenu::changeEvent(event);
}

void
JveGuiMenuProjectSources::setTargetRow(const int row)
{
    bool isInvalidRow = 0 > row;

    mp_targetRow = row;

    actionProperties .setDisabled(isInvalidRow);
    actionRemove     .setDisabled(isInvalidRow);
}

void
JveGuiMenuProjectSources::updateTranslations(void)
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
JveGuiMenuProjectSources::slotSetState(const int state)
{
    setDisabled(
        !(state & JveState::ProjectOpened)
            || state & JveState::Busy
    );
}

void
JveGuiMenuProjectSources::slotActionPropertiesTriggered(void)
{
    emit wantViewItemProperties(mp_targetRow);
}

void
JveGuiMenuProjectSources::slotActionRemoveTriggered(void)
{
    emit wantRemoveItem(mp_targetRow);
}


