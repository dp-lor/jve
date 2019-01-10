

#include "jveGuiHistoryView.h"


#include <QEvent>


#include "../../core/definitions/jveState.h"
#include "../definitions/jveGuiState.h"

#include "../../core/signals/jveGlobalSignals.h"


jveGuiHistoryView::jveGuiHistoryView(QWidget *parent)
    : QListView(parent),
        mp_viewModel(this)
{
    // properties
    setFocusPolicy(Qt::NoFocus);
    setSizePolicy(
        QSizePolicy::Expanding,
        QSizePolicy::Expanding
    );
    setWordWrap(false);

    // model
    setModel(&mp_viewModel);
    setSelectionModel(&(mp_viewModel.selectionModel));

    // initial state
    slotSetState(jveState::None);
    slotSetGuiState(jveGuiState::Ready);

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
}

jveGuiHistoryView::~jveGuiHistoryView()
{
}

void
jveGuiHistoryView::changeEvent(QEvent *event)
{
    if (QEvent::StyleChange == event->type()) {
        mp_viewModel.updateIcons();
    } else if (QEvent::LanguageChange == event->type()) {
        mp_viewModel.updateTranslations();
    }
    QListView::changeEvent(event);
}

void
jveGuiHistoryView::slotSetState(const int state)
{
    mp_state = state;

    setDisabled(
        mp_guiState & jveGuiState::EditProcess
            || mp_state & jveState::Busy
            || !(mp_state & jveState::ProjectOpened)
    );
}

void
jveGuiHistoryView::slotSetGuiState(const int state)
{
    mp_guiState = state;

    setDisabled(
        mp_guiState & jveGuiState::EditProcess
            || mp_state & jveState::Busy
            || !(mp_state & jveState::ProjectOpened)
    );
}


