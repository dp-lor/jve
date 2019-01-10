

#include "jveGuiTimeSpinBox.h"


#include <QtMath>


#include "../../core/definitions/jveLimits.h"
#include "../definitions/jveGuiState.h"

#include "../../core/signals/jveGlobalSignals.h"


jveGuiTimeSpinBox::jveGuiTimeSpinBox(QWidget *parent)
    : QTimeEdit(parent),
        mp_timeHelper()
{
    // properties
    setFocusPolicy(Qt::ClickFocus);
    setDisplayFormat(QString("HH:mm:ss"));

    // editing finished
    connect(
        this,
        SIGNAL(editingFinished()),
        this,
        SLOT(catchEditingFinished()),
        Qt::DirectConnection
    );
}

jveGuiTimeSpinBox::~jveGuiTimeSpinBox()
{
}

void
jveGuiTimeSpinBox::focusInEvent(QFocusEvent *event)
{
    emit jveGlobalSignals.guiStateChanged(jveGuiState::EditProcess);

    QTimeEdit::focusInEvent(event);
}

void
jveGuiTimeSpinBox::focusOutEvent(QFocusEvent *event)
{
    emit jveGlobalSignals.guiStateChanged(jveGuiState::Ready);

    QTimeEdit::focusOutEvent(event);
}

void
jveGuiTimeSpinBox::setFps(const double fps)
{
    mp_fps = fps;
    setTime(
        mp_timeHelper.fromMSecsSinceStartOfDay(
            qFloor(mp_frameNumber / mp_fps) * 1000
        )
    );
}

void
jveGuiTimeSpinBox::setExternalValue(const int frameNumber)
{
    mp_frameNumber = frameNumber;
    setTime(
        mp_timeHelper.fromMSecsSinceStartOfDay(
            qFloor(mp_frameNumber / mp_fps) * 1000
        )
    );
}

void
jveGuiTimeSpinBox::catchEditingFinished(void)
{
    int seconds     = time().msecsSinceStartOfDay() / 1000;
    int frameNumber = qCeil(mp_fps * seconds);

    emit wantSetExternalValue(frameNumber ?: 1);
}


