

#include "jveGuiDockTitleBarTrail.h"


#include <QEvent>
#include <QPaintEvent>
#include <QPainter>


#include "../definitions/jveGuiMediaDefines.h"


jveGuiDockTitleBarTrail::jveGuiDockTitleBarTrail(QWidget *parent)
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

jveGuiDockTitleBarTrail::~jveGuiDockTitleBarTrail(void)
{
}

void
jveGuiDockTitleBarTrail::changeEvent(QEvent *event)
{
    if (QEvent::StyleChange == event->type()) {
        updateTrailColor();
    }
    QWidget::changeEvent(event);
}

void
jveGuiDockTitleBarTrail::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.save();
    painter.fillRect(0, 0, width(), height(), mp_brush);
    painter.restore();
}

void
jveGuiDockTitleBarTrail::updateTrailColor(void)
{
    mp_pixmap.fill(palette().color(QPalette::Disabled, QPalette::ButtonText));
    mp_pixmap.setMask(mp_mask);
    mp_brush.setTexture(mp_pixmap);
}


