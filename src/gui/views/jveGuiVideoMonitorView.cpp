

#include "jveGuiVideoMonitorView.h"


#include "../../core/definitions/jveState.h"
#include "../../core/signals/jveGlobalSignals.h"


jveGuiVideoMonitorView::jveGuiVideoMonitorView(QWidget *parent)
    : QWidget(parent),
        mp_layout(this),
        mp_viewport(this),
        mp_bar(this)
{
    // properties
    setSizePolicy(
        QSizePolicy::Expanding,
        QSizePolicy::Expanding
    );
    QPalette pal(palette());
    pal.setColor(QPalette::Window, Qt::black);
    setPalette(pal);
    setAutoFillBackground(true);

    // layout
    mp_layout.setMargin(0);
    mp_layout.setSpacing(0);
    mp_layout.setAlignment(Qt::AlignHCenter);

    // viewport
    mp_layout.addWidget(&mp_viewport);
    // bar
    mp_layout.addWidget(&mp_bar);

    //initial state
    slotSetState(jveState::None);

    // slot set state
    connect(
        &jveGlobalSignals,
        SIGNAL(stateChanged(int)),
        this,
        SLOT(slotSetState(int)),
        Qt::QueuedConnection
    );
}

jveGuiVideoMonitorView::~jveGuiVideoMonitorView(void)
{
}

void
jveGuiVideoMonitorView::slotSetState(const int state)
{
    setDisabled(
        !(state & jveState::ProjectOpened)
            || state & jveState::Busy
    );
}


