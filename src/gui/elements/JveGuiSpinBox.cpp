

#include "JveGuiSpinBox.h"


#include "../definitions/JveGuiState.h"
#include "../../core/signals/JveGlobalSignals.h"


JveGuiSpinBox::JveGuiSpinBox(QWidget *parent)
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

JveGuiSpinBox::~JveGuiSpinBox()
{
}

void
JveGuiSpinBox::focusInEvent(QFocusEvent *event)
{
    emit JveGlobalSignals.guiStateChanged(JveGuiState::EditProcess);

    QSpinBox::focusInEvent(event);
}

void
JveGuiSpinBox::focusOutEvent(QFocusEvent *event)
{
    emit JveGlobalSignals.guiStateChanged(JveGuiState::Ready);

    QSpinBox::focusOutEvent(event);
}

void
JveGuiSpinBox::setExternalValue(const int value)
{
    setValue(value);
}

void
JveGuiSpinBox::catchEditingFinished(void)
{
    emit wantSetExternalValue(value());
}


