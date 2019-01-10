

#include "jveGuiFramesSpinBox.h"


#include "../../core/definitions/jveLimits.h"


jveGuiFramesSpinBox::jveGuiFramesSpinBox(QWidget *parent)
    : jveGuiSpinBox(parent)
{
    // properties
    setRange(
        JVE_UNSIGNED_FRAME_NUMBER_MIN,
        JVE_UNSIGNED_FRAME_NUMBER_MAX
    );
    setSingleStep(1);
}

jveGuiFramesSpinBox::~jveGuiFramesSpinBox()
{
}


