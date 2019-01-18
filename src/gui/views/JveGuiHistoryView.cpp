

#include "JveGuiHistoryView.h"


#include <QEvent>


#include "../../core/definitions/JveState.h"
#include "../definitions/JveGuiState.h"

#include "../../core/signals/JveGlobalSignals.h"


JveGuiHistoryView::JveGuiHistoryView(QWidget *parent)
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
    slotSetState(JveState::None);
    slotSetGuiState(JveGuiState::Ready);

    // slot set state
    connect(
        &JveGlobalSignals,
        SIGNAL(stateChanged(int)),
        this,
        SLOT(slotSetState(int)),
        Qt::QueuedConnection
    );
    // slot set gui state
    connect(
        &JveGlobalSignals,
        SIGNAL(guiStateChanged(int)),
        this,
        SLOT(slotSetGuiState(int)),
        Qt::DirectConnection
    );
}

JveGuiHistoryView::~JveGuiHistoryView()
{
}

void
JveGuiHistoryView::changeEvent(QEvent *event)
{
    if (QEvent::StyleChange == event->type()) {
        mp_viewModel.updateIcons();
    } else if (QEvent::LanguageChange == event->type()) {
        mp_viewModel.updateTranslations();
    }
    QListView::changeEvent(event);
}

void
JveGuiHistoryView::slotSetState(const int state)
{
    mp_state = state;

    setDisabled(
        mp_guiState & JveGuiState::EditProcess
            || mp_state & JveState::Busy
            || !(mp_state & JveState::ProjectOpened)
    );
}

void
JveGuiHistoryView::slotSetGuiState(const int state)
{
    mp_guiState = state;

    setDisabled(
        mp_guiState & JveGuiState::EditProcess
            || mp_state & JveState::Busy
            || !(mp_state & JveState::ProjectOpened)
    );
}


