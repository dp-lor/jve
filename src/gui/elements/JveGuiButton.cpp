

#include "JveGuiButton.h"


JveGuiButton::JveGuiButton(QWidget *parent)
    : QPushButton(parent)
{
    // properties
    setFocusPolicy(Qt::NoFocus);
    setAutoRepeat(false);
}

JveGuiButton::~JveGuiButton(void)
{
}


