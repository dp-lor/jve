

#include "jveSettingsModel.h"


#include "../definitions/jveLimits.h"
#include "../mutexes/jveProjectMutex.h"
#include "../signals/jveProjectSettingsSignals.h"

#include "jveStateModel.h"
#include "../application/jveProject.h"

#include "../history/jveHistory.h"
#include "../history/jveSetRangeStartCommand.h"
#include "../history/jveSetRangeEndCommand.h"


jveSettingsModel::jveSettingsModel(
    jveProject  *project,
    QDomElement  domElement
) : jveBaseModel(domElement),
        mp_project(project),
        mp_rangeStart(JVE_UNSIGNED_FRAME_NUMBER_MIN),
        mp_rangeEnd(JVE_UNSIGNED_FRAME_NUMBER_MAX)
{
    // share self to project
    mp_project->setSettingsModel(this);

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

jveSettingsModel::~jveSettingsModel(void)
{
}

void
jveSettingsModel::setUp(void)
{
    // slot set range start
    connect(
        &jveProjectSettingsSignals,
        SIGNAL(wantSetRangeStart(int)),
        this,
        SLOT(slotSetRangeStart(int)),
        Qt::QueuedConnection
    );
    // slot set range end
    connect(
        &jveProjectSettingsSignals,
        SIGNAL(wantSetRangeEnd(int)),
        this,
        SLOT(slotSetRangeEnd(int)),
        Qt::QueuedConnection
    );

    emit jveProjectSettingsSignals.rangeStartChanged(mp_rangeStart);
    emit jveProjectSettingsSignals.rangeEndChanged(mp_rangeEnd);
}

void
jveSettingsModel::upSet(void)
{
    emit jveProjectSettingsSignals.wantResetView();
}

int
jveSettingsModel::rangeStart(void) const
{
    return mp_rangeStart;
}

int
jveSettingsModel::rangeEnd(void) const
{
    return mp_rangeEnd;
}

void
jveSettingsModel::setRangeStart(
    const int  rangeStart,
    const bool locked
)
{
    bool lockItself = !locked;

    if (lockItself) {
        jveProjectMutex.lock();
    }

    mp_rangeStart = rangeStart;
    mp_domElement.setAttribute("rangeStart", mp_rangeStart);

    emit jveProjectSettingsSignals.rangeStartChanged(mp_rangeStart);

    // fix playhead position
    if (mp_project->stateModel()->playheadPosition() < mp_rangeStart) {
        mp_project->stateModel()->setPlayheadPosition(
            mp_rangeStart,
            locked ?: lockItself
        );
    }

    if (lockItself) {
        jveProjectMutex.unlock();
    }
}

void
jveSettingsModel::setRangeEnd(
    const int  rangeEnd,
    const bool locked
)
{
    bool lockItself = !locked;

    if (lockItself) {
        jveProjectMutex.lock();
    }

    mp_rangeEnd = rangeEnd;
    mp_domElement.setAttribute("rangeEnd", mp_rangeEnd);

    emit jveProjectSettingsSignals.rangeEndChanged(mp_rangeEnd);

    // fix playhead position
    if (mp_project->stateModel()->playheadPosition() > mp_rangeEnd) {
        mp_project->stateModel()->setPlayheadPosition(
            mp_rangeEnd,
            locked ?: lockItself
        );
    }

    if (lockItself) {
        jveProjectMutex.unlock();
    }
}

void
jveSettingsModel::slotSetRangeStart(const int rangeStart)
{
    jveProjectMutex.lock();

    int newRangeStart = rangeStart;

    if (newRangeStart > mp_rangeEnd) {
        newRangeStart = mp_rangeEnd;
    } else if (newRangeStart < JVE_UNSIGNED_FRAME_NUMBER_MIN) {
        newRangeStart = JVE_UNSIGNED_FRAME_NUMBER_MIN;
    }

    if (newRangeStart != mp_rangeStart) {
        mp_project->history()->appendUndoCommand(
            new jveSetRangeStartCommand(
                this,
                mp_rangeStart,
                newRangeStart
            )
        );
    } else {
        emit jveProjectSettingsSignals.rangeStartChanged(newRangeStart);
    }

    jveProjectMutex.unlock();
}

void
jveSettingsModel::slotSetRangeEnd(const int rangeEnd)
{
    jveProjectMutex.lock();

    int newRangeEnd = rangeEnd;

    if (newRangeEnd < mp_rangeStart) {
        newRangeEnd = mp_rangeStart;
    } else if (newRangeEnd > JVE_UNSIGNED_FRAME_NUMBER_MAX) {
        newRangeEnd = JVE_UNSIGNED_FRAME_NUMBER_MAX;
    }

    if (newRangeEnd != mp_rangeEnd) {
        mp_project->history()->appendUndoCommand(
            new jveSetRangeEndCommand(
                this,
                mp_rangeEnd,
                newRangeEnd
            )
        );
    } else {
        emit jveProjectSettingsSignals.rangeEndChanged(newRangeEnd);
    }

    jveProjectMutex.unlock();
}


