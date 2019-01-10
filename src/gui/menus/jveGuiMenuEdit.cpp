

#include "jveGuiMenuEdit.h"


#include "../../core/definitions/jveState.h"
#include "../definitions/jveGuiState.h"

#include "../../core/signals/jveGlobalSignals.h"
#include "../../core/signals/jveHistorySignals.h"
#include "../../core/signals/jveProjectSourcesSignals.h"


jveGuiMenuEdit::jveGuiMenuEdit(QWidget *parent)
    : QMenu(parent),
        actionUndo(this),
        actionRedo(this),
        actionCut(this),
        actionCopy(this),
        actionPaste(this),
        actionRemove(this),
        actionAddProjectSourcesMediaItems(this),
        actionAddProjectSourcesImagesSequenceItem(this),
        actionPreferences(this),
        // private members
        mp_canUndo(false),
        mp_canRedo(false),
        mp_canCut(false),
        mp_canCopy(false),
        mp_canPaste(false),
        mp_canRemove(false)
{
    // undo
    actionUndo.setShortcut(QKeySequence::Undo);
    actionUndo.setShortcutContext(Qt::ApplicationShortcut);
    addAction(&actionUndo);
    connect(
        &actionUndo,
        SIGNAL(triggered()),
        &jveHistorySignals,
        SIGNAL(wantUndo()),
        Qt::DirectConnection
    );
    // redo
    actionRedo.setShortcut(QKeySequence::Redo);
    actionRedo.setShortcutContext(Qt::ApplicationShortcut);
    addAction(&actionRedo);
    connect(
        &actionRedo,
        SIGNAL(triggered()),
        &jveHistorySignals,
        SIGNAL(wantRedo()),
        Qt::DirectConnection
    );

    // separator
    addSeparator();

    // cut
    actionCut.setShortcut(QKeySequence::Cut);
    addAction(&actionCut);
    connect(
        &actionCut,
        SIGNAL(triggered()),
        &jveGlobalSignals,
        SIGNAL(wantCut()),
        Qt::DirectConnection
    );
    // copy
    actionCopy.setShortcut(QKeySequence::Copy);
    addAction(&actionCopy);
    connect(
        &actionCopy,
        SIGNAL(triggered()),
        &jveGlobalSignals,
        SIGNAL(wantCopy()),
        Qt::DirectConnection
    );
    // paste
    actionPaste.setShortcut(QKeySequence::Paste);
    addAction(&actionPaste);
    connect(
        &actionPaste,
        SIGNAL(triggered()),
        &jveGlobalSignals,
        SIGNAL(wantPaste()),
        Qt::DirectConnection
    );
    // remove (delete)
    actionRemove.setShortcut(QKeySequence::Delete);
    addAction(&actionRemove);
    connect(
        &actionRemove,
        SIGNAL(triggered()),
        &jveGlobalSignals,
        SIGNAL(wantRemove()),
        Qt::DirectConnection
    );

    // separator
    addSeparator();

    // add project sources media items
    actionAddProjectSourcesMediaItems
        .setShortcut(Qt::ALT + Qt::Key_O);
    actionAddProjectSourcesMediaItems
        .setShortcutContext(Qt::ApplicationShortcut);
    addAction(&actionAddProjectSourcesMediaItems);
    connect(
        &actionAddProjectSourcesMediaItems,
        SIGNAL(triggered()),
        &jveProjectSourcesSignals,
        SIGNAL(wantShowAddMediaItemsDialog()),
        Qt::DirectConnection
    );
    // add project sources images sequence item
    actionAddProjectSourcesImagesSequenceItem
        .setShortcut(Qt::ALT + Qt::Key_I);
    actionAddProjectSourcesImagesSequenceItem
        .setShortcutContext(Qt::ApplicationShortcut);
    addAction(&actionAddProjectSourcesImagesSequenceItem);
    connect(
        &actionAddProjectSourcesImagesSequenceItem,
        SIGNAL(triggered()),
        &jveProjectSourcesSignals,
        SIGNAL(wantShowAddImagesSequenceItemDialog()),
        Qt::DirectConnection
    );

    // separator
    addSeparator();

    // preferences
    addAction(&actionPreferences);
    connect(
        &actionPreferences,
        SIGNAL(triggered()),
        &jveGlobalSignals,
        SIGNAL(wantShowPreferencesDialog()),
        Qt::DirectConnection
    );

    // initial state
    updateState(
        jveState::None,
        jveGuiState::Ready
    );

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
    // slot set gui state
    connect(
        &jveGlobalSignals,
        SIGNAL(guiStateChanged(int)),
        this,
        SLOT(slotSetGuiState(int)),
        Qt::DirectConnection
    );

    // slot set history actions state
    connect(
        &jveHistorySignals,
        SIGNAL(historyActionsStateChanged(bool, bool)),
        this,
        SLOT(slotSetHistoryActionsState(bool, bool)),
        Qt::DirectConnection
    );
}

jveGuiMenuEdit::~jveGuiMenuEdit(void)
{
}

void
jveGuiMenuEdit::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    }
    QMenu::changeEvent(event);
}

void
jveGuiMenuEdit::updateState(const int state, const int guiState)
{
    mp_state    = state;
    mp_guiState = guiState;
    mp_disabled = (
        mp_guiState & jveGuiState::EditProcess
            || mp_state & jveState::Busy
            || !(mp_state & jveState::ProjectOpened)
    );

    // history actions state
    actionUndo.setDisabled(mp_disabled ?: !mp_canUndo);
    actionRedo.setDisabled(mp_disabled ?: !mp_canRedo);

    // copy-paste actions state
    actionCut    .setDisabled(mp_disabled ?: !mp_canCut   );
    actionCopy   .setDisabled(mp_disabled ?: !mp_canCopy  );
    actionPaste  .setDisabled(mp_disabled ?: !mp_canPaste );
    actionRemove .setDisabled(mp_disabled ?: !mp_canRemove);

    // project sources actions
    actionAddProjectSourcesMediaItems         .setDisabled(mp_disabled);
    actionAddProjectSourcesImagesSequenceItem .setDisabled(mp_disabled);
}

void
jveGuiMenuEdit::updateTranslations(void)
{
    // menu action
    menuAction()->setText(tr("gui_menu_edit_text"));

    // undo
    actionUndo.setText(tr("gui_menu_edit_action_undo_text"));
    actionUndo.setStatusTip(tr("gui_menu_edit_action_undo_status_tip"));

    // redo
    actionRedo.setText(tr("gui_menu_edit_action_redo_text"));
    actionRedo.setStatusTip(tr("gui_menu_edit_action_redo_status_tip"));

    // cut
    actionCut.setText(tr("gui_menu_edit_action_cut_text"));
    actionCut.setStatusTip(tr("gui_menu_edit_action_cut_status_tip"));

    // copy
    actionCopy.setText(tr("gui_menu_edit_action_copy_text"));
    actionCopy.setStatusTip(tr("gui_menu_edit_action_copy_status_tip"));

    // paste
    actionPaste.setText(tr("gui_menu_edit_action_paste_text"));
    actionPaste.setStatusTip(tr("gui_menu_edit_action_paste_status_tip") );

    // remove (delete)
    actionRemove.setText(tr("gui_menu_edit_action_remove_text"));
    actionRemove.setStatusTip(tr("gui_menu_edit_action_remove_status_tip"));

    // add project sources media items
    actionAddProjectSourcesMediaItems.setText(
        tr("gui_menu_edit_add_project_sources_media_items_action_text")
    );
    actionAddProjectSourcesMediaItems.setStatusTip(
        tr("gui_menu_edit_add_project_sources_media_items_action_status_tip")
    );

    // add project sources images sequence item
    actionAddProjectSourcesImagesSequenceItem.setText(
        tr("gui_menu_edit_add_project_sources_images_sequence_item_action_text")
    );
    actionAddProjectSourcesImagesSequenceItem.setStatusTip(
        tr("gui_menu_edit_add_project_sources_images_sequence_item_action_status_tip")
    );

    // preferences
    actionPreferences.setText(tr("gui_menu_edit_action_preferences_text"));
    actionPreferences.setStatusTip(
        tr("gui_menu_edit_action_preferences_status_tip")
    );
}

void
jveGuiMenuEdit::slotSetState(const int state)
{
    updateState(state, mp_guiState);
}

void
jveGuiMenuEdit::slotSetGuiState(const int state)
{
    updateState(mp_state, state);
}

void
jveGuiMenuEdit::slotSetHistoryActionsState(
    const bool canUndo,
    const bool canRedo
)
{
    // store last received state
    mp_canUndo = canUndo;
    mp_canRedo = canRedo;

    // set state
    actionUndo.setDisabled(mp_disabled ?: !mp_canUndo);
    actionRedo.setDisabled(mp_disabled ?: !mp_canRedo);
}


