

#include "JveGuiPTRegion.h"


#include <QCursor>
#include <QPainter>
#include <QDebug>


#include "JveGuiPTRegionJoint.h"


JveGuiPTRegion::JveGuiPTRegion(
    const int          width,
    const int          offset,
          JveGuiPTItem *parent
) : JveGuiPTItem(parent)
{
    mp_width  = width;
    mp_offset = offset;

    setPos(mp_offset, 35);
    setCursor(Qt::OpenHandCursor);

    JveGuiPTRegionJoint *j = new JveGuiPTRegionJoint(this);
    Q_UNUSED(j);
}

JveGuiPTRegion::~JveGuiPTRegion(void)
{
}

QRectF
JveGuiPTRegion::boundingRect(void) const
{
    return QRectF(0, 0, mp_width, 32);
}

void
JveGuiPTRegion::paint(
          QPainter                 *painter,
    const QStyleOptionGraphicsItem *option,
          QWidget                  *widget
)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    //painter->fillRect(boundingRect(), Qt::black);
    painter->setPen(QPen(Qt::gray, 1));
    painter->drawRect(0, 0, mp_width - 1, 31);
    //painter->drawLine(mp_internalOffset - 1, 28, mp_viewOffset - 1, 28);
    //painter->drawText(0, 52, QString("Test text"));
}


