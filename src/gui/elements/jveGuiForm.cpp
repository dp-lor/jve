

#include "jveGuiForm.h"


#include <QtMath>


#include "../definitions/jveGuiAppearanceDefines.h"


jveGuiForm::jveGuiForm(QWidget *parent)
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

jveGuiForm::~jveGuiForm(void)
{
}

void
jveGuiForm::showEvent(QShowEvent *event)
{
    updateRows(jveGuiForm::UpdateAfterAddRow);
    QWidget::showEvent(event);
}

void
jveGuiForm::addSpace(void)
{
    addRow(Q_NULLPTR, Q_NULLPTR);
}

void
jveGuiForm::addSectionLabel(QLabel *sectionLabel)
{
    QFont font = sectionLabel->font();

    font.setWeight(QFont::DemiBold);
    sectionLabel->setFont(font);

    addRow(Q_NULLPTR, sectionLabel);
}

void
jveGuiForm::addRow(QWidget *label, QWidget *field)
{
    int rowCount = mp_layout.rowCount();

    if (Q_NULLPTR == label) {
        label = new QWidget(this);
        label->setFixedSize(0, 0);
    } else {
        label->setParent(this);
    }
    if (Q_NULLPTR == field) {
        field = new QWidget(this);
        field->setFixedSize(0, 0);
    } else {
        field->setParent(this);
    }
    mp_layout.addWidget(label, rowCount, 0, mp_labelsAlignment);
    mp_layout.addWidget(field, rowCount, 1, mp_fieldsAlignment);

    updateRows(jveGuiForm::UpdateAfterAddRow);
}

void
jveGuiForm::setLayoutAlignment(Qt::Alignment alignment)
{
    mp_layout.setAlignment(alignment);
}

void
jveGuiForm::setLabelsAlignment(Qt::Alignment alignment)
{
    mp_labelsAlignment = alignment;
    updateRows(jveGuiForm::UpdateAfterSetLabelsAlignment);
}

void
jveGuiForm::setFieldsAlignment(Qt::Alignment alignment)
{
    mp_fieldsAlignment = alignment;
    updateRows(jveGuiForm::UpdateAfterSetFieldsAlignment);
}

void
jveGuiForm::updateRows(const int updateType)
{
    QLayoutItem *layoutItem;
    int          minWidth = 0;

    for (int i = 0; i < mp_layout.rowCount(); i += 1) {
        if (jveGuiForm::UpdateAfterSetLabelsAlignment == updateType) {
            layoutItem = mp_layout.itemAtPosition(i, 0);
            if (Q_NULLPTR != layoutItem) {
                layoutItem->setAlignment(mp_labelsAlignment);
            }
        } else {
            layoutItem = mp_layout.itemAtPosition(i, 1);
            if (Q_NULLPTR != layoutItem) {
                if (jveGuiForm::UpdateAfterSetFieldsAlignment == updateType) {
                    layoutItem->setAlignment(mp_fieldsAlignment);
                } else if (jveGuiForm::UpdateAfterAddRow == updateType) {
                    minWidth = qMax(minWidth, layoutItem->widget()->width());
                }
            }
        }
    }

    if (jveGuiForm::UpdateAfterAddRow == updateType) {
        for (int i = 0; i < mp_layout.rowCount(); i += 1) {
            layoutItem = mp_layout.itemAtPosition(i, 1);
            if (Q_NULLPTR != layoutItem) {
                layoutItem->widget()->setMinimumWidth(minWidth);
                layoutItem->widget()
                    ->setMinimumHeight(JVE_GUI_TOOLS_LAYOUT_SPACING);
            }
        }
    }
}


