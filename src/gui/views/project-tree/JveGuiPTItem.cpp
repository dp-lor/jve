

#include "JveGuiPTItem.h"


JveGuiPTItem::JveGuiPTItem(JveGuiPTItem *parent)
    : QGraphicsItem(parent)
{
    mp_parent = parent;
    mp_width  = 0;
    mp_offset = 0;
}

JveGuiPTItem::~JveGuiPTItem(void)
{
}

QRectF
JveGuiPTItem::boundingRect(void) const
{
    return QRectF();
}

void
JveGuiPTItem::paint(
          QPainter                 *painter,
    const QStyleOptionGraphicsItem *option,
          QWidget                  *widget
)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

int
JveGuiPTItem::width(void) const
{
    return mp_width;
}

int
JveGuiPTItem::offset(void) const
{
    return mp_offset;
}


