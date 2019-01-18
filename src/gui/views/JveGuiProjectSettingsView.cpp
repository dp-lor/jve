

#include "JveGuiProjectSettingsView.h"


#include <QEvent>


#include "../../core/definitions/JveState.h"

#include "../../core/signals/JveGlobalSignals.h"
#include "../../core/signals/JveProjectSettingsSignals.h"

#include "../definitions/JveGuiAppearanceDefines.h"


JveGuiProjectSettingsView::JveGuiProjectSettingsView(QWidget *parent)
    : QWidget(parent),
        // appearance
        mp_layout(this),
        mp_form(this),
        // ranges
        mp_labelStart(this),
        mp_startSpinsGroup(this),
        mp_labelEnd(this),
        mp_endSpinsGroup(this),
        // video
        mp_labelVideoSize(this),
        mp_comboVideoSize(this),
        mp_labelVideoFps(this),
        mp_comboVideoFps(this),
        // audio
        mp_labelAudioChannels(this),
        mp_comboAudioChannels(this),
        mp_labelAudioSampleRate(this),
        mp_comboAudioSampleRate(this)
{
    // properties
    setFocusPolicy(Qt::NoFocus);
    setSizePolicy(
        QSizePolicy::Expanding,
        QSizePolicy::Expanding
    );
    setContentsMargins(
        0,
        JVE_GUI_VERTICAL_SPACE * 2,
        0,
        JVE_GUI_VERTICAL_SPACE * 2
    );

    // layout
    mp_layout.setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    mp_layout.setMargin(0);
    mp_layout.setSpacing(0);
    // form
    mp_layout.addWidget(&mp_form);

    // range start
    mp_form.addRow(&mp_labelStart, &mp_startSpinsGroup);
    // range end
    mp_form.addRow(&mp_labelEnd, &mp_endSpinsGroup);
    // space
    mp_form.addSpace();
    // video size
    mp_form.addRow(&mp_labelVideoSize, &mp_comboVideoSize);
    // video fps
    mp_form.addRow(&mp_labelVideoFps, &mp_comboVideoFps);
    // space
    mp_form.addSpace();
    // audio channels
    mp_form.addRow(&mp_labelAudioChannels, &mp_comboAudioChannels);
    // audio samplerate
    mp_form.addRow(&mp_labelAudioSampleRate, &mp_comboAudioSampleRate);


    mp_startSpinsGroup.timeSpin.setFps(23.976023976);
    mp_endSpinsGroup.timeSpin.setFps(23.976023976);


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
        &JveProjectSettingsSignals,
        SIGNAL(wantResetView()),
        this,
        SLOT(slotResetView()),
        Qt::QueuedConnection
    );
    // slot set range start
    connect(
        &JveProjectSettingsSignals,
        SIGNAL(rangeStartChanged(int)),
        this,
        SLOT(slotSetRangeStart(int)),
        Qt::QueuedConnection
    );
    // slot set range end
    connect(
        &JveProjectSettingsSignals,
        SIGNAL(rangeEndChanged(int)),
        this,
        SLOT(slotSetRangeEnd(int)),
        Qt::QueuedConnection
    );

    // signal set range start from time spin
    connect(
        &mp_startSpinsGroup.timeSpin,
        SIGNAL(wantSetExternalValue(int)),
        &JveProjectSettingsSignals,
        SIGNAL(wantSetRangeStart(int)),
        Qt::DirectConnection
    );
    // signal set range start from frames spin
    connect(
        &mp_startSpinsGroup.framesSpin,
        SIGNAL(wantSetExternalValue(int)),
        &JveProjectSettingsSignals,
        SIGNAL(wantSetRangeStart(int)),
        Qt::DirectConnection
    );

    // signal set range end from time spin
    connect(
        &mp_endSpinsGroup.timeSpin,
        SIGNAL(wantSetExternalValue(int)),
        &JveProjectSettingsSignals,
        SIGNAL(wantSetRangeEnd(int)),
        Qt::DirectConnection
    );
    // signal set range end from frames spin
    connect(
        &mp_endSpinsGroup.framesSpin,
        SIGNAL(wantSetExternalValue(int)),
        &JveProjectSettingsSignals,
        SIGNAL(wantSetRangeEnd(int)),
        Qt::DirectConnection
    );
}

JveGuiProjectSettingsView::~JveGuiProjectSettingsView()
{
}

void
JveGuiProjectSettingsView::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    }
    QWidget::changeEvent(event);
}

void
JveGuiProjectSettingsView::updateTranslations(void)
{
    // start label
    mp_labelStart.setText(
        tr("gui_project_settings_view_label_start_text")
            .append(":")
    );
    // start time
    mp_startSpinsGroup.timeSpin.setToolTip(
        tr("gui_project_settings_view_spin_start_time_tool_tip")
    );
    // start frame
    mp_startSpinsGroup.framesSpin.setToolTip(
        tr("gui_project_settings_view_spin_start_frame_tool_tip")
    );

    // end label
    mp_labelEnd.setText(
        tr("gui_project_settings_view_label_end_text")
            .append(":")
    );
    // end time
    mp_endSpinsGroup.timeSpin.setToolTip(
        tr("gui_project_settings_view_spin_end_time_tool_tip")
    );
    // end frame
    mp_endSpinsGroup.framesSpin.setToolTip(
        tr("gui_project_settings_view_spin_end_frame_tool_tip")
    );

    // size label
    mp_labelVideoSize.setText(
        tr("gui_project_settings_view_label_video_size_text")
            .append(":")
    );
    // fps label
    mp_labelVideoFps.setText(
        tr("gui_project_settings_view_label_video_fps_text")
            .append(":")
    );

    // channels label
    mp_labelAudioChannels.setText(
        tr("gui_project_settings_view_label_audio_channels_text")
            .append(":")
    );
    // samplerate label
    mp_labelAudioSampleRate.setText(
        tr("gui_project_settings_view_label_audio_samplerate_text")
            .append(":")
    );
}

void
JveGuiProjectSettingsView::slotStateChanged(const int state)
{
    setDisabled(
        !(state & JveState::ProjectOpened)
            || state & JveState::Busy
    );
}

void
JveGuiProjectSettingsView::slotResetView(void)
{
    slotSetRangeStart(1);
    slotSetRangeEnd(1);
}

void
JveGuiProjectSettingsView::slotSetRangeStart(const int rangeStart)
{
    mp_startSpinsGroup.timeSpin   .setExternalValue(rangeStart);
    mp_startSpinsGroup.framesSpin .setExternalValue(rangeStart);
}

void
JveGuiProjectSettingsView::slotSetRangeEnd(const int rangeEnd)
{
    mp_endSpinsGroup.timeSpin   .setExternalValue(rangeEnd);
    mp_endSpinsGroup.framesSpin .setExternalValue(rangeEnd);
}


