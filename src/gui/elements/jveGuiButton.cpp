

#include "jveGuiButton.h"


jveGuiButton::jveGuiButton(QWidget *parent)
    : QPushButton(parent)
{
    // properties
    setFocusPolicy(Qt::NoFocus);
    setAutoRepeat(false);
}

jveGuiButton::~jveGuiButton(void)
{
}


