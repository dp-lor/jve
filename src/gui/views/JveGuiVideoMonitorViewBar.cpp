

#include "JveGuiVideoMonitorViewBar.h"


#include <QEvent>


#include "../definitions/JveGuiAppearanceDefines.h"
//#include "../definitions/JveGuiMediaDefines.h"
#include "../styles/JveGuiBlackStyle.h"

#include "../../core/signals/JveProjectStateSignals.h"


JveGuiVideoMonitorViewBar::JveGuiVideoMonitorViewBar(QWidget *parent)
    : QWidget(parent),
        mp_layout(this),
        //mp_heightHolder(this, JVE_GUI_ICON_DUMMY),
        mp_qualityGroup(this),
        mp_fpsGroup(this)
{
    // properties
    setFocusPolicy(Qt::NoFocus);
    setSizePolicy(
        QSizePolicy::Expanding,
        QSizePolicy::Minimum
    );

    // layout
    mp_layout.setContentsMargins(
        JVE_GUI_MARGIN_SIZE,
        JVE_GUI_VERTICAL_SPACE,
        JVE_GUI_MARGIN_SIZE,
        JVE_GUI_VERTICAL_SPACE
    );
    mp_layout.setSpacing(JVE_GUI_TOOLS_LAYOUT_SPACING * 10);
    mp_layout.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    // height holder
    //mp_heightHolder.setFixedWidth(0);
    //mp_layout.addWidget(&mp_heightHolder);

    // quality group label
    JveGuiBlackStyle::polish(&(mp_qualityGroup.label));
    // quality group spin box
    JveGuiBlackStyle::polish(&(mp_qualityGroup.spinBox));
    mp_qualityGroup.spinBox.setRange(1, 100);
    mp_qualityGroup.spinBox.setSingleStep(1);
    mp_qualityGroup.spinBox.setSuffix("%");
    // quality group
    mp_layout.addWidget(&mp_qualityGroup);

    // fps group
    JveGuiBlackStyle::polish(&(mp_fpsGroup.labelOne));
    JveGuiBlackStyle::polish(&(mp_fpsGroup.labelTwo));
    mp_layout.addWidget(&mp_fpsGroup);

    // initial state
    slotResetView();

    // initial translate
    updateTranslations();

    // slot reset view
    connect(
        &JveProjectStateSignals,
        SIGNAL(wantResetView()),
        this,
        SLOT(slotResetView()),
        Qt::QueuedConnection
    );
    // slot set video monitor quality
    connect(
        &JveProjectStateSignals,
        SIGNAL(videoMonitorQualityChanged(int)),
        this,
        SLOT(slotSetVideoMonitorQuality(int)),
        Qt::QueuedConnection
    );

    // signal set video monitor quality
    connect(
        &mp_qualityGroup.spinBox,
        SIGNAL(wantSetExternalValue(int)),
        &JveProjectStateSignals,
        SIGNAL(wantSetVideoMonitorQuality(int)),
        Qt::DirectConnection
    );
}

JveGuiVideoMonitorViewBar::~JveGuiVideoMonitorViewBar(void)
{
}

void
JveGuiVideoMonitorViewBar::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type()) {
        updateTranslations();
    }
    QWidget::changeEvent(event);
}

void
JveGuiVideoMonitorViewBar::updateTranslations(void)
{
    // quality label
    mp_qualityGroup.label.setText(
        tr("gui_video_monitor_view_bar_quality_label_text")
            .append(":")
    );

    // fps label
    mp_fpsGroup.labelOne.setText(
        tr("gui_video_monitor_view_bar_fps_label_text")
            .append(":")
    );
}

void
JveGuiVideoMonitorViewBar::slotResetView(void)
{
    mp_qualityGroup.spinBox.setExternalValue(100);
    mp_fpsGroup.labelTwo.setText("0");
}

void
JveGuiVideoMonitorViewBar::slotSetVideoMonitorQuality(const int quality)
{
    mp_qualityGroup.spinBox.setExternalValue(quality);
}


