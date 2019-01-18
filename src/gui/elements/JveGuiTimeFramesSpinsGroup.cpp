

#include "JveGuiTimeFramesSpinsGroup.h"


#include "../definitions/JveGuiAppearanceDefines.h"


JveGuiTimeFramesSpinsGroup::JveGuiTimeFramesSpinsGroup(QWidget *parent)
    : QWidget(parent),
        timeSpin(this),
        framesSpin(this),
        mp_layout(this),
        mp_betweenLabel(this)
{
    // properties
    setFocusPolicy(Qt::NoFocus);
    setSizePolicy(
        QSizePolicy::Minimum,
        QSizePolicy::Minimum
    );

    // layout
    mp_layout.setMargin(0);
    mp_layout.setSpacing(JVE_GUI_TOOLS_LAYOUT_SPACING);
    mp_layout.setAlignment(Qt::AlignVCenter);

    // time spin
    mp_layout.addWidget(&timeSpin);

    // between label
    mp_betweenLabel.setText("-");
    mp_layout.addWidget(&mp_betweenLabel);

    // frames spin
    mp_layout.addWidget(&framesSpin);

    // set initial values
    resetSpins();
}

JveGuiTimeFramesSpinsGroup::~JveGuiTimeFramesSpinsGroup(void)
{
}

void
JveGuiTimeFramesSpinsGroup::resetSpins(void)
{
    timeSpin.setExternalValue(1);
    framesSpin.setExternalValue(1);
}


