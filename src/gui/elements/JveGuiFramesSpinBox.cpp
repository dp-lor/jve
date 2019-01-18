

#include "JveGuiFramesSpinBox.h"


#include "../../core/definitions/JveLimits.h"


JveGuiFramesSpinBox::JveGuiFramesSpinBox(QWidget *parent)
    : JveGuiSpinBox(parent)
{
    // properties
    setRange(
        JVE_UNSIGNED_FRAME_NUMBER_MIN,
        JVE_UNSIGNED_FRAME_NUMBER_MAX
    );
    setSingleStep(1);
}

JveGuiFramesSpinBox::~JveGuiFramesSpinBox()
{
}


