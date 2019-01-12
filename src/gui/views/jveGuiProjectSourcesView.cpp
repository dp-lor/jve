

#include "jveGuiProjectSourcesView.h"


#include <QEvent>


#include "../../core/definitions/jveState.h"
#include "../../core/signals/jveGlobalSignals.h"
#include "../../core/signals/jveProjectSourcesSignals.h"


jveGuiProjectSourcesView::jveGuiProjectSourcesView(QWidget *parent)
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
    slotStateChanged(jveState::None);
    slotResetView();

    // initial translate
    updateTranslations();

    // slot state changed
    connect(
        &jveGlobalSignals,
        SIGNAL(stateChanged(int)),
        this,
        SLOT(slotStateChanged(int)),
        Qt::QueuedConnection
    );

    // slot reset view
    connect(
        &jveProjectSourcesSignals,
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

jveGuiProjectSourcesView::~jveGuiProjectSourcesView()
{
}

void
jveGuiProjectSourcesView::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    }
    QWidget::changeEvent(event);
}

void
jveGuiProjectSourcesView::updateTranslations(void)
{
    mp_area.viewModel.updateTranslations();
}

void
jveGuiProjectSourcesView::slotStateChanged(const int state)
{
    setDisabled(
        !(state & jveState::ProjectOpened)
            || state & jveState::Busy
    );
}

void
jveGuiProjectSourcesView::slotResetView(void)
{
    mp_area.viewModel.clear();
    mp_bar.searchWidget.searchInput.clear();
}

void
jveGuiProjectSourcesView::slotApplyItemsFilter(const QString &searchString)
{
    mp_area.applyItemsFilter(searchString.trimmed());
}


