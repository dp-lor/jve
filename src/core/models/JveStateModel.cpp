

#include "JveStateModel.h"


#include <QDebug>


#include "../definitions/JveLimits.h"
#include "../mutexes/JveProjectMutex.h"
#include "../signals/JveProjectStateSignals.h"

#include "../application/Jve.h"
#include "JveSettingsModel.h"


JveStateModel::JveStateModel(QDomElement domElement)
    : JveBaseModel(domElement)
{
    // playhead position
    int rangeStart = 1;//Jve.settingsModel()->rangeStart();
    int rangeEnd   = 1;//Jve.settingsModel()->rangeEnd();

    qDebug() << Jve.settingsModel();

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

    Jve.setProjectHiddenModifiedState(true);
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

    Jve.setProjectHiddenModifiedState(true);
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
    int rangeStart  = Jve.settingsModel()->rangeStart();
    int rangeEnd    = Jve.settingsModel()->rangeEnd();

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


