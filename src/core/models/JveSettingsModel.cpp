

#include "JveSettingsModel.h"


#include "../definitions/JveLimits.h"
#include "../mutexes/JveProjectMutex.h"
#include "../signals/JveProjectSettingsSignals.h"

#include "../application/Jve.h"
#include "JveStateModel.h"

#include "../history/JveHistory.h"
#include "../history/JveSetRangeStartCommand.h"
#include "../history/JveSetRangeEndCommand.h"


JveSettingsModel::JveSettingsModel(QDomElement domElement)
    : JveBaseModel(domElement),
        mp_rangeStart(JVE_UNSIGNED_FRAME_NUMBER_MIN),
        mp_rangeEnd(JVE_UNSIGNED_FRAME_NUMBER_MAX)
{
    // range
    int rangeStart = mp_domElement.attribute("rangeStart").toInt();
    int rangeEnd   = mp_domElement.attribute("rangeEnd"  ).toInt();

    if (rangeStart < mp_rangeStart) {
        rangeStart = mp_rangeStart;
    }
    if (rangeEnd > mp_rangeEnd) {
        rangeEnd = mp_rangeEnd;
    }
    if (rangeStart > rangeEnd) {
        rangeStart = rangeEnd;
    }
    if (rangeEnd < rangeStart) {
        rangeEnd = rangeStart;
    }

    mp_rangeStart = rangeStart;
    mp_rangeEnd   = rangeEnd;

    mp_domElement.setAttribute("rangeStart", mp_rangeStart);
    mp_domElement.setAttribute("rangeEnd",   mp_rangeEnd  );
}

JveSettingsModel::~JveSettingsModel(void)
{
}

void
JveSettingsModel::setUp(void)
{
    // slot set range start
    connect(
        &JveProjectSettingsSignals,
        SIGNAL(wantSetRangeStart(int)),
        this,
        SLOT(slotSetRangeStart(int)),
        Qt::QueuedConnection
    );
    // slot set range end
    connect(
        &JveProjectSettingsSignals,
        SIGNAL(wantSetRangeEnd(int)),
        this,
        SLOT(slotSetRangeEnd(int)),
        Qt::QueuedConnection
    );

    emit JveProjectSettingsSignals.rangeStartChanged(mp_rangeStart);
    emit JveProjectSettingsSignals.rangeEndChanged(mp_rangeEnd);
}

void
JveSettingsModel::upSet(void)
{
    emit JveProjectSettingsSignals.wantResetView();
}

int
JveSettingsModel::rangeStart(void) const
{
    return mp_rangeStart;
}

int
JveSettingsModel::rangeEnd(void) const
{
    return mp_rangeEnd;
}

void
JveSettingsModel::setRangeStart(
    const int  rangeStart,
    const bool locked
)
{
    bool lockItself = !locked;

    if (lockItself) {
        JveProjectMutex.lock();
    }

    mp_rangeStart = rangeStart;
    mp_domElement.setAttribute("rangeStart", mp_rangeStart);

    emit JveProjectSettingsSignals.rangeStartChanged(mp_rangeStart);

    // fix playhead position
    if (Jve.stateModel()->playheadPosition() < mp_rangeStart) {
        Jve.stateModel()->setPlayheadPosition(
            mp_rangeStart,
            locked ?: lockItself
        );
    }

    if (lockItself) {
        JveProjectMutex.unlock();
    }
}

void
JveSettingsModel::setRangeEnd(
    const int  rangeEnd,
    const bool locked
)
{
    bool lockItself = !locked;

    if (lockItself) {
        JveProjectMutex.lock();
    }

    mp_rangeEnd = rangeEnd;
    mp_domElement.setAttribute("rangeEnd", mp_rangeEnd);

    emit JveProjectSettingsSignals.rangeEndChanged(mp_rangeEnd);

    // fix playhead position
    if (Jve.stateModel()->playheadPosition() > mp_rangeEnd) {
        Jve.stateModel()->setPlayheadPosition(
            mp_rangeEnd,
            locked ?: lockItself
        );
    }

    if (lockItself) {
        JveProjectMutex.unlock();
    }
}

void
JveSettingsModel::slotSetRangeStart(const int rangeStart)
{
    JveProjectMutex.lock();

    int newRangeStart = rangeStart;

    if (newRangeStart > mp_rangeEnd) {
        newRangeStart = mp_rangeEnd;
    } else if (newRangeStart < JVE_UNSIGNED_FRAME_NUMBER_MIN) {
        newRangeStart = JVE_UNSIGNED_FRAME_NUMBER_MIN;
    }

    if (newRangeStart != mp_rangeStart) {
        Jve.history().appendUndoCommand(
            new JveSetRangeStartCommand(
                this,
                mp_rangeStart,
                newRangeStart
            )
        );
    } else {
        emit JveProjectSettingsSignals.rangeStartChanged(newRangeStart);
    }

    JveProjectMutex.unlock();
}

void
JveSettingsModel::slotSetRangeEnd(const int rangeEnd)
{
    JveProjectMutex.lock();

    int newRangeEnd = rangeEnd;

    if (newRangeEnd < mp_rangeStart) {
        newRangeEnd = mp_rangeStart;
    } else if (newRangeEnd > JVE_UNSIGNED_FRAME_NUMBER_MAX) {
        newRangeEnd = JVE_UNSIGNED_FRAME_NUMBER_MAX;
    }

    if (newRangeEnd != mp_rangeEnd) {
        Jve.history().appendUndoCommand(
            new JveSetRangeEndCommand(
                this,
                mp_rangeEnd,
                newRangeEnd
            )
        );
    } else {
        emit JveProjectSettingsSignals.rangeEndChanged(newRangeEnd);
    }

    JveProjectMutex.unlock();
}


