

#include "jveGuiTransportBar.h"


#include <QtMath>
#include <QEvent>


#include "../definitions/jveGuiMediaDefines.h"
#include "../definitions/jveGuiAppearanceDefines.h"
#include "../../core/definitions/jveState.h"

#include "../../core/signals/jveGlobalSignals.h"
#include "../../core/signals/jveProjectStateSignals.h"


jveGuiTransportBar::jveGuiTransportBar(QWidget *parent)
    : QWidget(parent),
        mp_layout(this),
        // buttons
        mp_buttonSeekToStart (this, JVE_GUI_ICON_SEEK_TO_START),
        mp_buttonSeekToPrevKF(this, JVE_GUI_ICON_SEEK_TO_PREVIOUS_KEYFRAME),
        mp_buttonPlayPause   (this, JVE_GUI_ICON_PLAY),
        mp_buttonSeekToNextKF(this, JVE_GUI_ICON_SEEK_TO_NEXT_KEYFRAME),
        mp_buttonSeekToEnd   (this, JVE_GUI_ICON_SEEK_TO_END),
        mp_buttonLoop        (this, JVE_GUI_ICON_LOOP),
        // spacer
        mp_spacer(this),
        // playhead position spins group
        mp_playheadPositionSpinsGroup(this)
{
    // properties
    setFocusPolicy(Qt::NoFocus);
    setSizePolicy(
        QSizePolicy::Minimum,
        QSizePolicy::Minimum
    );

    // layout
    mp_layout.setMargin(0);
    mp_layout.setSpacing(JVE_GUI_TOOLS_LAYOUT_SPACING);
    mp_layout.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    // seek to start
    mp_layout.addWidget(&mp_buttonSeekToStart);
    // seek to previous keyframe
    mp_layout.addWidget(&mp_buttonSeekToPrevKF);
    // play/pause
    mp_buttonPlayPause.setMinimumWidth(
        qFloor(mp_buttonPlayPause.height() * 2.5)
    );
    mp_layout.addWidget(&mp_buttonPlayPause);
    // seek to next keyframe
    mp_layout.addWidget(&mp_buttonSeekToNextKF);
    // seek to end
    mp_layout.addWidget(&mp_buttonSeekToEnd);
    // loop
    mp_layout.addWidget(&mp_buttonLoop);

    // spacer
    mp_layout.addWidget(&mp_spacer);

    // playhead position
    mp_layout.addWidget(&mp_playheadPositionSpinsGroup);


    mp_playheadPositionSpinsGroup.timeSpin.setFps(23.976023976);


    // initial state
    slotSetState(jveState::None);
    slotResetView();

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

    // slot reset view
    connect(
        &jveProjectStateSignals,
        SIGNAL(wantResetView()),
        this,
        SLOT(slotResetView()),
        Qt::QueuedConnection
    );
    // slot set playhead position
    connect(
        &jveProjectStateSignals,
        SIGNAL(playheadPositionChanged(int)),
        this,
        SLOT(slotSetPlayheadPosition(int)),
        Qt::QueuedConnection
    );

    // signal set playhead position from time spin
    connect(
        &mp_playheadPositionSpinsGroup.timeSpin,
        SIGNAL(wantSetExternalValue(int)),
        &jveProjectStateSignals,
        SIGNAL(wantSetPlayheadPosition(int)),
        Qt::DirectConnection
    );
    // signal set playhead position from frames spin
    connect(
        &mp_playheadPositionSpinsGroup.framesSpin,
        SIGNAL(wantSetExternalValue(int)),
        &jveProjectStateSignals,
        SIGNAL(wantSetPlayheadPosition(int)),
        Qt::DirectConnection
    );
}

jveGuiTransportBar::~jveGuiTransportBar(void)
{
}

void
jveGuiTransportBar::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    }
    QWidget::changeEvent(event);
}

void
jveGuiTransportBar::updateTranslations(void)
{
    // seek to start
    mp_buttonSeekToStart.setToolTip(
        tr("gui_transport_bar_button_seek_to_start_tool_tip")
    );
    // seek to previous keyframe
    mp_buttonSeekToPrevKF.setToolTip(
        tr("gui_transport_bar_button_seek_to_previous_key_frame_tool_tip")
    );
    // play/pause
    mp_buttonPlayPause.setToolTip(
        tr("gui_transport_bar_button_play_pause_tool_tip")
    );
    // seek to next keyframe
    mp_buttonSeekToNextKF.setToolTip(
        tr("gui_transport_bar_button_seek_to_next_key_frame_tool_tip")
    );
    // seek to end
    mp_buttonSeekToEnd.setToolTip(
        tr("gui_transport_bar_button_seek_to_end_tool_tip")
    );
    // loop
    mp_buttonLoop.setToolTip(
        tr("gui_transport_bar_button_loop_tool_tip")
    );

    // playhead position time
    mp_playheadPositionSpinsGroup.timeSpin.setToolTip(
        tr("gui_transport_bar_spin_current_time_tool_tip")
    );
    // playhead position frame number
    mp_playheadPositionSpinsGroup.framesSpin.setToolTip(
        tr("gui_transport_bar_spin_current_frame_tool_tip")
    );
}

void
jveGuiTransportBar::slotSetState(const int state)
{
    setDisabled(
        !(state & jveState::ProjectOpened)
            || state & jveState::Busy
    );
}

void
jveGuiTransportBar::slotResetView(void)
{
    slotSetPlayheadPosition(1);
}

void
jveGuiTransportBar::slotSetPlayheadPosition(const int position)
{
    mp_playheadPositionSpinsGroup.timeSpin  .setExternalValue(position);
    mp_playheadPositionSpinsGroup.framesSpin.setExternalValue(position);
}


