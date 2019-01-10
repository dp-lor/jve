

#include "jveProjectSettings.h"


#include "../definitions/jveLimits.h"
#include "../mutexes/jveProjectMutex.h"
#include "../application/jveApplication.h"

#include "jveProjectState.h"

#include "../signals/jveProjectSettingsSignals.h"

#include "../history/jveHistory.h"
#include "../history/jveSetRangeStartCommand.h"
#include "../history/jveSetRangeEndCommand.h"


jveProjectSettings::jveProjectSettings(
    jveApplication *app,
    QDomElement     domNode
) : jveBaseModel(app, domNode),
        mp_rangeStart(JVE_UNSIGNED_FRAME_NUMBER_MIN),
        mp_rangeEnd(JVE_UNSIGNED_FRAME_NUMBER_MAX)
{
    // set self to application
    mp_app->setProjectSettings(this);

    // range
    int rangeStart = mp_domNode.attribute("rangeStart").toInt();
    int rangeEnd   = mp_domNode.attribute("rangeEnd"  ).toInt();

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

    mp_domNode.setAttribute("rangeStart", mp_rangeStart);
    mp_domNode.setAttribute("rangeEnd",   mp_rangeEnd  );
}

jveProjectSettings::~jveProjectSettings(void)
{
}

void
jveProjectSettings::setUp(void)
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
jveProjectSettings::upSet(void)
{
    emit jveProjectSettingsSignals.wantResetView();
}

int
jveProjectSettings::rangeStart(void) const
{
    return mp_rangeStart;
}

int
jveProjectSettings::rangeEnd(void) const
{
    return mp_rangeEnd;
}

void
jveProjectSettings::setRangeStart(
    const int  rangeStart,
    const bool locked
)
{
    bool lockItself = !locked;

    if (lockItself) {
        jveProjectMutex.lock();
    }

    mp_rangeStart = rangeStart;
    mp_domNode.setAttribute("rangeStart", mp_rangeStart);

    emit jveProjectSettingsSignals.rangeStartChanged(mp_rangeStart);

    // fix playhead position
    if (mp_app->projectState()->playheadPosition() < mp_rangeStart) {
        mp_app->projectState()->setPlayheadPosition(
            mp_rangeStart,
            locked ?: lockItself
        );
    }

    if (lockItself) {
        jveProjectMutex.unlock();
    }
}

void
jveProjectSettings::setRangeEnd(
    const int  rangeEnd,
    const bool locked
)
{
    bool lockItself = !locked;

    if (lockItself) {
        jveProjectMutex.lock();
    }

    mp_rangeEnd = rangeEnd;
    mp_domNode.setAttribute("rangeEnd", mp_rangeEnd);

    emit jveProjectSettingsSignals.rangeEndChanged(mp_rangeEnd);

    // fix playhead position
    if (mp_app->projectState()->playheadPosition() > mp_rangeEnd) {
        mp_app->projectState()->setPlayheadPosition(
            mp_rangeEnd,
            locked ?: lockItself
        );
    }

    if (lockItself) {
        jveProjectMutex.unlock();
    }
}

void
jveProjectSettings::slotSetRangeStart(const int rangeStart)
{
    jveProjectMutex.lock();

    int newRangeStart = rangeStart;

    if (newRangeStart > mp_rangeEnd) {
        newRangeStart = mp_rangeEnd;
    } else if (newRangeStart < JVE_UNSIGNED_FRAME_NUMBER_MIN) {
        newRangeStart = JVE_UNSIGNED_FRAME_NUMBER_MIN;
    }

    if (newRangeStart != mp_rangeStart) {
        mp_app->history()->appendUndoCommand(
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
jveProjectSettings::slotSetRangeEnd(const int rangeEnd)
{
    jveProjectMutex.lock();

    int newRangeEnd = rangeEnd;

    if (newRangeEnd < mp_rangeStart) {
        newRangeEnd = mp_rangeStart;
    } else if (newRangeEnd > JVE_UNSIGNED_FRAME_NUMBER_MAX) {
        newRangeEnd = JVE_UNSIGNED_FRAME_NUMBER_MAX;
    }

    if (newRangeEnd != mp_rangeEnd) {
        mp_app->history()->appendUndoCommand(
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


