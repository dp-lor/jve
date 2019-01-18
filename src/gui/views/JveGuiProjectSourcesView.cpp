

#include "JveGuiProjectSourcesView.h"


#include <QEvent>


#include "../../core/definitions/JveState.h"
#include "../../core/signals/JveGlobalSignals.h"
#include "../../core/signals/JveProjectSourcesSignals.h"


JveGuiProjectSourcesView::JveGuiProjectSourcesView(QWidget *parent)
    : QWidget(parent),
        mp_layout(this),
        mp_bar(this),
        mp_area(this)
{
    // properties
    setFocusPolicy(Qt::NoFocus);
    setSizePolicy(
        QSizePolicy::Expanding,
        QSizePolicy::Expanding
    );

    // layout
    mp_layout.setMargin(0);
    mp_layout.setSpacing(0);

    // bar
    mp_layout.addWidget(&mp_bar);
    // area
    mp_layout.addWidget(&mp_area);

    // initial state
    slotStateChanged(JveState::None);
    slotResetView();

    // initial translate
    updateTranslations();

    // slot state changed
    connect(
        &JveGlobalSignals,
        SIGNAL(stateChanged(int)),
        this,
        SLOT(slotStateChanged(int)),
        Qt::QueuedConnection
    );

    // slot reset view
    connect(
        &JveProjectSourcesSignals,
        SIGNAL(wantResetView()),
        this,
        SLOT(slotResetView()),
        Qt::QueuedConnection
    );

    // slot apply items filter
    connect(
        &(mp_bar.searchWidget.searchInput),
        SIGNAL(textChanged(QString)),
        this,
        SLOT(slotApplyItemsFilter(QString)),
        Qt::DirectConnection
    );
}

JveGuiProjectSourcesView::~JveGuiProjectSourcesView()
{
}

void
JveGuiProjectSourcesView::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    }
    QWidget::changeEvent(event);
}

void
JveGuiProjectSourcesView::updateTranslations(void)
{
    mp_area.viewModel.updateTranslations();
}

void
JveGuiProjectSourcesView::slotStateChanged(const int state)
{
    setDisabled(
        !(state & JveState::ProjectOpened)
            || state & JveState::Busy
    );
}

void
JveGuiProjectSourcesView::slotResetView(void)
{
    mp_area.viewModel.clear();
    mp_bar.searchWidget.searchInput.clear();
}

void
JveGuiProjectSourcesView::slotApplyItemsFilter(const QString &searchString)
{
    mp_area.applyItemsFilter(searchString.trimmed());
}


