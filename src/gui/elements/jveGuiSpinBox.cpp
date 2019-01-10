

#include "jveGuiSpinBox.h"


#include "../definitions/jveGuiState.h"
#include "../../core/signals/jveGlobalSignals.h"


jveGuiSpinBox::jveGuiSpinBox(QWidget *parent)
    : QSpinBox(parent)
{
    // properties
    setFocusPolicy(Qt::ClickFocus);

    // slot catch editing finished
    connect(
        this,
        SIGNAL(editingFinished()),
        this,
        SLOT(catchEditingFinished()),
        Qt::DirectConnection
    );
}

jveGuiSpinBox::~jveGuiSpinBox()
{
}

void
jveGuiSpinBox::focusInEvent(QFocusEvent *event)
{
    emit jveGlobalSignals.guiStateChanged(jveGuiState::EditProcess);

    QSpinBox::focusInEvent(event);
}

void
jveGuiSpinBox::focusOutEvent(QFocusEvent *event)
{
    emit jveGlobalSignals.guiStateChanged(jveGuiState::Ready);

    QSpinBox::focusOutEvent(event);
}

void
jveGuiSpinBox::setExternalValue(const int value)
{
    setValue(value);
}

void
jveGuiSpinBox::catchEditingFinished(void)
{
    emit wantSetExternalValue(value());
}


