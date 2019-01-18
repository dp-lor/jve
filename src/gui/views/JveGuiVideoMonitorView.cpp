

#include "JveGuiVideoMonitorView.h"


#include "../../core/definitions/JveState.h"
#include "../../core/signals/JveGlobalSignals.h"


JveGuiVideoMonitorView::JveGuiVideoMonitorView(QWidget *parent)
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
    slotSetState(JveState::None);

    // slot set state
    connect(
        &JveGlobalSignals,
        SIGNAL(stateChanged(int)),
        this,
        SLOT(slotSetState(int)),
        Qt::QueuedConnection
    );
}

JveGuiVideoMonitorView::~JveGuiVideoMonitorView(void)
{
}

void
JveGuiVideoMonitorView::slotSetState(const int state)
{
    setDisabled(
        !(state & JveState::ProjectOpened)
            || state & JveState::Busy
    );
}


