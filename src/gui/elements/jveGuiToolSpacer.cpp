

#include "jveGuiToolSpacer.h"


jveGuiToolSpacer::jveGuiToolSpacer(QWidget *parent, const int size)
    : QWidget(parent)
{
    setFixedSize((size * 8), 1);
}

jveGuiToolSpacer::~jveGuiToolSpacer(void)
{
}


