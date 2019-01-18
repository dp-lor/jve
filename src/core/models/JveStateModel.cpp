

#include "JveStateModel.h"


#include "../definitions/JveLimits.h"
#include "../mutexes/JveProjectMutex.h"
#include "../signals/JveProjectStateSignals.h"

#include "JveSettingsModel.h"
#include "../application/JveProject.h"


JveStateModel::JveStateModel(
    JveProject  *project,
    QDomElement  domElement
) : JveBaseModel(domElement),
        mp_project(project)
{
    // share self to project
    mp_project->setStateModel(this);

    // playhead position
    int rangeStart = mp_project->settingsModel()->rangeStart();
    int rangeEnd   = mp_project->settingsModel()->rangeEnd();

    mp_playheadPosition = mp_domElement.attribute("playheadPosition").toInt();
    if (mp_playheadPosition < rangeStart) {
        mp_playheadPosition = rangeStart;
    }
    if (mp_playheadPosition > rangeEnd) {
        mp_playheadPosition = rangeEnd;
    }
    mp_domElement.setAttribute("playheadPosition", mp_playheadPosition);

    // video monitor quality
    mp_videoMonitorQuality
            = mp_domElement.attribute("videoMonitorQuality").toInt();
}

JveStateModel::~JveStateModel(void)
{
}

void
JveStateModel::setUp(void)
{
    // slot set playhead position
    connect(
        &JveProjectStateSignals,
        SIGNAL(wantSetPlayheadPosition(int)),
        this,
        SLOT(slotSetPlayheadPosition(int)),
        Qt::QueuedConnection
    );
    // slot set video onitor quality
    connect(
        &JveProjectStateSignals,
        SIGNAL(wantSetVideoMonitorQuality(int)),
        this,
        SLOT(slotSetVideoMonitorQuality(int)),
        Qt::QueuedConnection
    );

    emit JveProjectStateSignals
                .playheadPositionChanged(mp_playheadPosition);
    emit JveProjectStateSignals
                .videoMonitorQualityChanged(mp_videoMonitorQuality);
}

void
JveStateModel::upSet(void)
{
    emit JveProjectStateSignals.wantResetView();
}

int
JveStateModel::playheadPosition(void) const
{
    return mp_playheadPosition;
}

void
JveStateModel::setPlayheadPosition(
    const int  position,
    const bool locked
)
{
    bool lockItself = !locked;

    if (lockItself) {
        JveProjectMutex.lock();
    }

    mp_playheadPosition = position;
    mp_domElement.setAttribute("playheadPosition", mp_playheadPosition);

    mp_project->setHiddenModified(true);
    emit JveProjectStateSignals.playheadPositionChanged(mp_playheadPosition);

    if (lockItself) {
        JveProjectMutex.unlock();
    }
}

void
JveStateModel::setVideoMonitorQuality(
    const int  quality,
    const bool locked
)
{
    bool lockItself = !locked;

    if (lockItself) {
        JveProjectMutex.lock();
    }

    mp_videoMonitorQuality = quality;
    mp_domElement.setAttribute("videoMonitorQuality", mp_videoMonitorQuality);

    mp_project->setHiddenModified(true);
    emit JveProjectStateSignals
                .videoMonitorQualityChanged(mp_videoMonitorQuality);

    if (lockItself) {
        JveProjectMutex.unlock();
    }
}

void
JveStateModel::slotSetPlayheadPosition(const int position)
{
    JveProjectMutex.lock();

    int newPosition = position;
    int rangeStart  = mp_project->settingsModel()->rangeStart();
    int rangeEnd    = mp_project->settingsModel()->rangeEnd();

    if (newPosition < rangeStart) {
        newPosition = rangeStart;
    } else if (newPosition > rangeEnd) {
        newPosition = rangeEnd;
    }

    if (newPosition != mp_playheadPosition) {
        setPlayheadPosition(newPosition, true);
    } else {
        emit JveProjectStateSignals.playheadPositionChanged(newPosition);
    }

    JveProjectMutex.unlock();
}

void
JveStateModel::slotSetVideoMonitorQuality(const int quality)
{
    JveProjectMutex.lock();

    int newQuality = quality;

    if (newQuality < 1) {
        newQuality = 1;
    } else if (newQuality > 100) {
        newQuality = 100;
    }

    if (newQuality != mp_videoMonitorQuality) {
        setVideoMonitorQuality(newQuality, true);
    } else {
        emit JveProjectStateSignals
                    .videoMonitorQualityChanged(mp_videoMonitorQuality);
    }

    JveProjectMutex.unlock();
}


