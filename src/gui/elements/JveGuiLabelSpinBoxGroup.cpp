

#include "JveGuiLabelSpinBoxGroup.h"


JveGuiLabelSpinBoxGroup::JveGuiLabelSpinBoxGroup(QWidget *parent)
    : QWidget(parent),
        label(this),
        spinBox(this),
        mp_layout(this)
{
    // properties
    setFocusPolicy(Qt::NoFocus);
    setSizePolicy(
        QSizePolicy::Minimum,
        QSizePolicy::Minimum
    );

    // layout
    mp_layout.setMargin(0);
    mp_layout.setAlignment(Qt::AlignVCenter);

    // label
    label.setSizePolicy(
        QSizePolicy::Minimum,
        QSizePolicy::Minimum
    );
    mp_layout.addWidget(&label);

    // spin box
    spinBox.setSizePolicy(
        QSizePolicy::Preferred,
        QSizePolicy::Minimum
    );
    mp_layout.addWidget(&spinBox);
}

JveGuiLabelSpinBoxGroup::~JveGuiLabelSpinBoxGroup(void)
{
}


