

#include "jveProjectState.h"


#include "../definitions/jveLimits.h"

#include "../mutexes/jveProjectMutex.h"
#include "../application/jveApplication.h"

#include "../signals/jveProjectStateSignals.h"

#include "jveProjectSettings.h"


jveProjectState::jveProjectState(
    jveApplication *app,
    QDomElement     domNode
) : jveBaseModel(app, domNode)
{
    // set self to application
    mp_app->setProjectState(this);

    // playhead position
    int rangeStart = mp_app->projectSettings()->rangeStart();
    int rangeEnd   = mp_app->projectSettings()->rangeEnd();

    mp_playheadPosition = mp_domNode.attribute("playheadPosition").toInt();
    if (mp_playheadPosition < rangeStart) {
        mp_playheadPosition = rangeStart;
    }
    if (mp_playheadPosition > rangeEnd) {
        mp_playheadPosition = rangeEnd;
    }
    mp_domNode.setAttribute("playheadPosition", mp_playheadPosition);

    // video monitor quality
    mp_videoMonitorQuality
            = mp_domNode.attribute("videoMonitorQuality").toInt();
}

jveProjectState::~jveProjectState(void)
{
}

void
jveProjectState::setUp(void)
{
    // slot set playhead position
    connect(
        &jveProjectStateSignals,
        SIGNAL(wantSetPlayheadPosition(int)),
        this,
        SLOT(slotSetPlayheadPosition(int)),
        Qt::QueuedConnection
    );
    // slot set video onitor quality
    connect(
        &jveProjectStateSignals,
        SIGNAL(wantSetVideoMonitorQuality(int)),
        this,
        SLOT(slotSetVideoMonitorQuality(int)),
        Qt::QueuedConnection
    );

    emit jveProjectStateSignals
                .playheadPositionChanged(mp_playheadPosition);
    emit jveProjectStateSignals
                .videoMonitorQualityChanged(mp_videoMonitorQuality);
}

void
jveProjectState::upSet(void)
{
    emit jveProjectStateSignals.wantResetView();
}

int
jveProjectState::playheadPosition(void) const
{
    return mp_playheadPosition;
}

void
jveProjectState::setPlayheadPosition(
    const int  position,
    const bool locked
)
{
    bool lockItself = !locked;

    if (lockItself) {
        jveProjectMutex.lock();
    }

    mp_playheadPosition = position;
    mp_domNode.setAttribute("playheadPosition", mp_playheadPosition);

    mp_app->setProjectHiddenModified(true);
    emit jveProjectStateSignals.playheadPositionChanged(mp_playheadPosition);

    if (lockItself) {
        jveProjectMutex.unlock();
    }
}

void
jveProjectState::setVideoMonitorQuality(
    const int  quality,
    const bool locked
)
{
    bool lockItself = !locked;

    if (lockItself) {
        jveProjectMutex.lock();
    }

    mp_videoMonitorQuality = quality;
    mp_domNode.setAttribute("videoMonitorQuality", mp_videoMonitorQuality);

    mp_app->setProjectHiddenModified(true);
    emit jveProjectStateSignals
                .videoMonitorQualityChanged(mp_videoMonitorQuality);

    if (lockItself) {
        jveProjectMutex.unlock();
    }
}

void
jveProjectState::slotSetPlayheadPosition(const int position)
{
    jveProjectMutex.lock();

    int newPosition = position;
    int rangeStart  = mp_app->projectSettings()->rangeStart();
    int rangeEnd    = mp_app->projectSettings()->rangeEnd();

    if (newPosition < rangeStart) {
        newPosition = rangeStart;
    } else if (newPosition > rangeEnd) {
        newPosition = rangeEnd;
    }

    if (newPosition != mp_playheadPosition) {
        setPlayheadPosition(newPosition, true);
    } else {
        emit jveProjectStateSignals.playheadPositionChanged(newPosition);
    }

    jveProjectMutex.unlock();
}

void
jveProjectState::slotSetVideoMonitorQuality(const int quality)
{
    jveProjectMutex.lock();

    int newQuality = quality;

    if (newQuality < 1) {
        newQuality = 1;
    } else if (newQuality > 100) {
        newQuality = 100;
    }

    if (newQuality != mp_videoMonitorQuality) {
        setVideoMonitorQuality(newQuality, true);
    } else {
        emit jveProjectStateSignals
                    .videoMonitorQualityChanged(mp_videoMonitorQuality);
    }

    jveProjectMutex.unlock();
}


