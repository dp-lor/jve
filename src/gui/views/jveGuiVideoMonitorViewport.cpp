

#include "jveGuiVideoMonitorViewport.h"


#include <QResizeEvent>
#include <QDebug>


#include "../definitions/jveGuiAppearanceDefines.h"
#include "../definitions/jveGuiMediaDefines.h"


jveGuiVideoMonitorViewport::jveGuiVideoMonitorViewport(QWidget *parent)
    : QWidget(parent),
        mp_layout(this),
        mp_frameWrapper(this),
        mp_frame(&mp_frameWrapper),
        mp_originalWidth(1920),
        mp_originalHeight(1080)
{
    // properties
    setSizePolicy(
        QSizePolicy::Expanding,
        QSizePolicy::Expanding
    );
    setMinimumSize(
        JVE_GUI_VIDEO_MONITOR_VIEWPORT_MIN_WIDTH,
        JVE_GUI_VIDEO_MONITOR_VIEWPORT_MIN_HEIGHT
    );

    // layout
    mp_layout.setMargin(0);
    mp_layout.setSpacing(0);
    mp_layout.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    // frame wrapper
    mp_frameWrapper.setSizePolicy(
        QSizePolicy::Expanding,
        QSizePolicy::Expanding
    );
    mp_layout.addWidget(&mp_frameWrapper);

    // frame
    mp_frame.setStyleSheet(
        "background: url("
            JVE_GUI_IMAGE_GRAY_SHARPEN_LOGO
        ") no-repeat center center #101010;"
        //") no-repeat center center #880000;"
    );
}

jveGuiVideoMonitorViewport::~jveGuiVideoMonitorViewport(void)
{
}

void
jveGuiVideoMonitorViewport::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    double wDiff = ((double) mp_frameWrapper.width() ) / mp_originalWidth;
    double hDiff = ((double) mp_frameWrapper.height()) / mp_originalHeight;
    double scale = hDiff < wDiff ? hDiff : wDiff;

    int w = mp_originalWidth  * scale;
    int h = mp_originalHeight * scale;
    int x = mp_frameWrapper.width() > w
        ? ((mp_frameWrapper.width() - w) / 2)
        : 0;
    int y = mp_frameWrapper.height() > h
        ? ((mp_frameWrapper.height() - h) / 2)
        : 0;

    mp_frame.setGeometry(x, y, w, h);
}


