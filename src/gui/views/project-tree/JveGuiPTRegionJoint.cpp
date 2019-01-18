

#include "JveGuiPTRegionJoint.h"


#include <QPainter>
#include <QDebug>


JveGuiPTRegionJoint::JveGuiPTRegionJoint(JveGuiPTItem *parent)
    : JveGuiPTItem(parent)
{
    setPos(-mp_parent->offset(), 0);
}

JveGuiPTRegionJoint::~JveGuiPTRegionJoint(void)
{
}

QRectF
JveGuiPTRegionJoint::boundingRect(void) const
{
    return QRectF(0, 0, 10, 1);
}

void
JveGuiPTRegionJoint::paint(
          QPainter                 *painter,
    const QStyleOptionGraphicsItem *option,
          QWidget                  *widget
)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPen pen(Qt::gray, 1);
    pen.setStyle(Qt::DotLine);
    painter->setPen(pen);

    painter->drawLine(0, 10, mp_parent->offset(), 10);
}


