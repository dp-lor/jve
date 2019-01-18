

#include "JveGuiToolSpacer.h"


JveGuiToolSpacer::JveGuiToolSpacer(QWidget *parent, const int size)
    : QWidget(parent)
{
    setFixedSize((size * 8), 1);
}

JveGuiToolSpacer::~JveGuiToolSpacer(void)
{
}


