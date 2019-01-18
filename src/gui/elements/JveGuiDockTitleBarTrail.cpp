

#include "JveGuiDockTitleBarTrail.h"


#include <QEvent>
#include <QPaintEvent>
#include <QPainter>


#include "../definitions/JveGuiMediaDefines.h"


JveGuiDockTitleBarTrail::JveGuiDockTitleBarTrail(QWidget *parent)
    : QWidget(parent),
        mp_pixmap(JVE_GUI_PATTERN_DOCK_TITLE_BAR_TRAIL),
        mp_mask(mp_pixmap.createMaskFromColor(Qt::black, Qt::MaskOutColor)),
        mp_brush(mp_pixmap)
{
    // properties
    setSizePolicy(
        QSizePolicy::Expanding,
        QSizePolicy::Fixed
    );
    setFixedHeight(4);

    // initial state
    updateTrailColor();
}

JveGuiDockTitleBarTrail::~JveGuiDockTitleBarTrail(void)
{
}

void
JveGuiDockTitleBarTrail::changeEvent(QEvent *event)
{
    if (QEvent::StyleChange == event->type()) {
        updateTrailColor();
    }
    QWidget::changeEvent(event);
}

void
JveGuiDockTitleBarTrail::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.save();
    painter.fillRect(0, 0, width(), height(), mp_brush);
    painter.restore();
}

void
JveGuiDockTitleBarTrail::updateTrailColor(void)
{
    mp_pixmap.fill(palette().color(QPalette::Disabled, QPalette::ButtonText));
    mp_pixmap.setMask(mp_mask);
    mp_brush.setTexture(mp_pixmap);
}


