

#include "JveGuiTimeSpinBox.h"


#include <QtMath>


#include "../../core/definitions/JveLimits.h"
#include "../definitions/JveGuiState.h"

#include "../../core/signals/JveGlobalSignals.h"


JveGuiTimeSpinBox::JveGuiTimeSpinBox(QWidget *parent)
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

JveGuiTimeSpinBox::~JveGuiTimeSpinBox()
{
}

void
JveGuiTimeSpinBox::focusInEvent(QFocusEvent *event)
{
    emit JveGlobalSignals.guiStateChanged(JveGuiState::EditProcess);

    QTimeEdit::focusInEvent(event);
}

void
JveGuiTimeSpinBox::focusOutEvent(QFocusEvent *event)
{
    emit JveGlobalSignals.guiStateChanged(JveGuiState::Ready);

    QTimeEdit::focusOutEvent(event);
}

void
JveGuiTimeSpinBox::setFps(const double fps)
{
    mp_fps = fps;
    setTime(
        mp_timeHelper.fromMSecsSinceStartOfDay(
            qFloor(mp_frameNumber / mp_fps) * 1000
        )
    );
}

void
JveGuiTimeSpinBox::setExternalValue(const int frameNumber)
{
    mp_frameNumber = frameNumber;
    setTime(
        mp_timeHelper.fromMSecsSinceStartOfDay(
            qFloor(mp_frameNumber / mp_fps) * 1000
        )
    );
}

void
JveGuiTimeSpinBox::catchEditingFinished(void)
{
    int seconds     = time().msecsSinceStartOfDay() / 1000;
    int frameNumber = qCeil(mp_fps * seconds);

    emit wantSetExternalValue(frameNumber ?: 1);
}


