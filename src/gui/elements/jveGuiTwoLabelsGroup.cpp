

#include "jveGuiTwoLabelsGroup.h"


jveGuiTwoLabelsGroup::jveGuiTwoLabelsGroup(QWidget *parent)
    : QWidget(parent),
        labelOne(this),
        labelTwo(this),
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

    // label one
    labelOne.setSizePolicy(
        QSizePolicy::Minimum,
        QSizePolicy::Minimum
    );
    mp_layout.addWidget(&labelOne);

    // label two
    labelTwo.setSizePolicy(
        QSizePolicy::Minimum,
        QSizePolicy::Minimum
    );
    mp_layout.addWidget(&labelTwo);
}

jveGuiTwoLabelsGroup::~jveGuiTwoLabelsGroup(void)
{
}


