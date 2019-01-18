

#include "JveGuiToolButton.h"


#include <QEvent>


JveGuiToolButton::JveGuiToolButton(QWidget *parent, const QString &iconPath)
    : QToolButton(parent),
        mp_pixmap(iconPath),
        mp_mask(mp_pixmap.createMaskFromColor(Qt::black, Qt::MaskOutColor))
{
    // properties
    setToolButtonStyle(Qt::ToolButtonIconOnly);
    setFocusPolicy(Qt::NoFocus);
    setAutoRepeat(false);

    // initial icon color
    updateIcon();
}

JveGuiToolButton::~JveGuiToolButton(void)
{
}

void
JveGuiToolButton::changeEvent(QEvent *event)
{
    if (QEvent::StyleChange == event->type()) {
        updateIcon();
    }
    QToolButton::changeEvent(event);
}

void
JveGuiToolButton::updateIcon(void)
{
    mp_pixmap.fill(palette().color(QPalette::Disabled, QPalette::ButtonText));
    mp_pixmap.setMask(mp_mask);
    setIcon(mp_pixmap);
}


