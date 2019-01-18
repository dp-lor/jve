

#include "JveGuiLabelComboBoxGroup.h"


JveGuiLabelComboBoxGroup::JveGuiLabelComboBoxGroup(QWidget *parent)
    : QWidget(parent),
        label(this),
        comboBox(this),
        mp_layout(this)
{
    // properties
    setFocusPolicy(Qt::NoFocus);
    setSizePolicy(
        QSizePolicy::Minimum,
        QSizePolicy::Minimum
    );

    // layout
    mp_layout.setAlignment(Qt::AlignVCenter);

    // label
    label.setSizePolicy(
        QSizePolicy::Minimum,
        QSizePolicy::Minimum
    );
    mp_layout.addWidget(&label);

    // combo box
    comboBox.setSizePolicy(
        QSizePolicy::Preferred,
        QSizePolicy::Minimum
    );
    mp_layout.addWidget(&comboBox);
}

JveGuiLabelComboBoxGroup::~JveGuiLabelComboBoxGroup(void)
{
}


