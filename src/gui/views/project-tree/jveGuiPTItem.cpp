

#include "jveGuiPTItem.h"


jveGuiPTItem::jveGuiPTItem(jveGuiPTItem *parent)
    : QGraphicsItem(parent)
{
    mp_parent = parent;
    mp_width  = 0;
    mp_offset = 0;
}

jveGuiPTItem::~jveGuiPTItem(void)
{
}

QRectF
jveGuiPTItem::boundingRect(void) const
{
    return QRectF();
}

void
jveGuiPTItem::paint(
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
jveGuiPTItem::width(void) const
{
    return mp_width;
}

int
jveGuiPTItem::offset(void) const
{
    return mp_offset;
}


