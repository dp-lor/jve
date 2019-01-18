

#include "JveGuiForm.h"


#include <QtMath>


#include "../definitions/JveGuiAppearanceDefines.h"


JveGuiForm::JveGuiForm(QWidget *parent)
    : QWidget(parent),
        mp_labelsAlignment(Qt::AlignRight),
        mp_fieldsAlignment(Qt::AlignLeft),
        mp_layout(this)
{
    // properties
    setFocusPolicy(Qt::NoFocus);
    setSizePolicy(
        QSizePolicy::Minimum,
        QSizePolicy::Minimum
    );

    // layout
    mp_layout.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

JveGuiForm::~JveGuiForm(void)
{
}

void
JveGuiForm::showEvent(QShowEvent *event)
{
    updateRows(JveGuiForm::UpdateAfterAddRow);
    QWidget::showEvent(event);
}

void
JveGuiForm::addSpace(void)
{
    addRow(nullptr, nullptr);
}

void
JveGuiForm::addSectionLabel(QLabel *sectionLabel)
{
    QFont font = sectionLabel->font();

    font.setWeight(QFont::DemiBold);
    sectionLabel->setFont(font);

    addRow(nullptr, sectionLabel);
}

void
JveGuiForm::addRow(QWidget *label, QWidget *field)
{
    int rowCount = mp_layout.rowCount();

    if (nullptr == label) {
        label = new QWidget(this);
        label->setFixedSize(0, 0);
    } else {
        label->setParent(this);
    }
    if (nullptr == field) {
        field = new QWidget(this);
        field->setFixedSize(0, 0);
    } else {
        field->setParent(this);
    }
    mp_layout.addWidget(label, rowCount, 0, mp_labelsAlignment);
    mp_layout.addWidget(field, rowCount, 1, mp_fieldsAlignment);

    updateRows(JveGuiForm::UpdateAfterAddRow);
}

void
JveGuiForm::setLayoutAlignment(Qt::Alignment alignment)
{
    mp_layout.setAlignment(alignment);
}

void
JveGuiForm::setLabelsAlignment(Qt::Alignment alignment)
{
    mp_labelsAlignment = alignment;
    updateRows(JveGuiForm::UpdateAfterSetLabelsAlignment);
}

void
JveGuiForm::setFieldsAlignment(Qt::Alignment alignment)
{
    mp_fieldsAlignment = alignment;
    updateRows(JveGuiForm::UpdateAfterSetFieldsAlignment);
}

void
JveGuiForm::updateRows(const int updateType)
{
    QLayoutItem *layoutItem;
    int          minWidth = 0;

    for (int i = 0; i < mp_layout.rowCount(); i++) {
        if (JveGuiForm::UpdateAfterSetLabelsAlignment == updateType) {
            layoutItem = mp_layout.itemAtPosition(i, 0);
            if (nullptr != layoutItem) {
                layoutItem->setAlignment(mp_labelsAlignment);
            }
        } else {
            layoutItem = mp_layout.itemAtPosition(i, 1);
            if (nullptr != layoutItem) {
                if (JveGuiForm::UpdateAfterSetFieldsAlignment == updateType) {
                    layoutItem->setAlignment(mp_fieldsAlignment);
                } else if (JveGuiForm::UpdateAfterAddRow == updateType) {
                    minWidth = qMax(minWidth, layoutItem->widget()->width());
                }
            }
        }
    }

    if (JveGuiForm::UpdateAfterAddRow == updateType) {
        for (int i = 0; i < mp_layout.rowCount(); i++) {
            layoutItem = mp_layout.itemAtPosition(i, 1);
            if (nullptr != layoutItem) {
                layoutItem->widget()->setMinimumWidth(minWidth);
                layoutItem->widget()
                    ->setMinimumHeight(JVE_GUI_TOOLS_LAYOUT_SPACING);
            }
        }
    }
}


