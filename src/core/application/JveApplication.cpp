

#include "JveApplication.h"


#include <QEvent>
#include <QThread>
#include <QDebug>


#include "../definitions/JveOption.h"
#include "../definitions/JveState.h"

#include "../utils/JveIdProvider.h"

#include "../mutexes/JveProjectMutex.h"
#include "../mutexes/JveLoadingProjectMutex.h"

#include "JveReport.h"
#include "JveProject.h"

#include "../signals/JveGlobalSignals.h"
#include "../signals/JveProjectSignals.h"
#include "../signals/JveProjectSourcesSignals.h"

#include "../models/JveSourcesModel.h"


JveApplication::JveApplication(void)
    : QObject(nullptr),
        mp_state(JveState::None),
        mp_loadingProjectProcessRejected(false)/*,
        mp_project(this)*/
{
    // ui change event
    connect(
        &JveGlobalSignals,
        SIGNAL(wantSendUiChangeEventType(int)),
        this,
        SLOT(watchUiChangeEventType(int)),
        Qt::QueuedConnection
    );

    // slot exit
    connect(
        &JveGlobalSignals,
        SIGNAL(wantExit()),
        this,
        SLOT(slotExit()),
        Qt::QueuedConnection
    );

    // slot close project
    connect(
        &JveProjectSignals,
        SIGNAL(wantCloseProject()),
        this,
        SLOT(slotCloseProject()),
        Qt::QueuedConnection
    );

    // slot load new project
    connect(
        &JveProjectSignals,
        SIGNAL(wantLoadNewProject()),
        this,
        SLOT(slotLoadNewProject()),
        Qt::QueuedConnection
    );
    // slot load project
    connect(
        &JveProjectSignals,
        SIGNAL(wantLoadProject(QString)),
        this,
        SLOT(slotLoadProject(QString)),
        Qt::QueuedConnection
    );

    // slot reject loading project process
    connect(
        &JveProjectSignals,
        SIGNAL(wantRejectLoadingProjectProcess()),
        this,
        SLOT(slotRejectLoadingProjectProcess()),
        Qt::QueuedConnection
    );

    // slot save project
    connect(
        &JveProjectSignals,
        SIGNAL(wantSaveProject(int, QString)),
        this,
        SLOT(slotSaveProject(int, QString)),
        Qt::QueuedConnection
    );
    // slot save project as
    connect(
        &JveProjectSignals,
        SIGNAL(wantSaveProjectAs(QString)),
        this,
        SLOT(slotSaveProjectAs(QString)),
        Qt::QueuedConnection
    );

    // slot route options
    connect(
        &JveProjectSignals,
        SIGNAL(wantRouteOptions(int, QString, QString)),
        this,
        SLOT(slotRouteOptions(int, QString, QString)),
        Qt::QueuedConnection
    );

    // slot add sources items
    connect(
        &JveProjectSourcesSignals,
        SIGNAL(wantAddItems(QStringList)),
        this,
        SLOT(slotAddSourcesItems(QStringList)),
        Qt::QueuedConnection
    );
}

JveApplication::~JveApplication(void)
{
}

bool
JveApplication::isLoadingProjectProcessRejected(void) const
{
    bool rejected = false;

    JveLoadingProjectMutex.lock();
    rejected = mp_loadingProjectProcessRejected;
    JveLoadingProjectMutex.unlock();

    return rejected;
}

bool
JveApplication::isProjectOpened(void) const
{
    return (mp_state & JveState::ProjectOpened);
}

bool
JveApplication::isProjectNew(void) const
{
    return (mp_state & JveState::ProjectNew);
}

bool
JveApplication::isProjectHiddenModified(void) const
{
    return (mp_state & JveState::ProjectHiddenModified);
}

bool
JveApplication::isProjectModified(void) const
{
    return (mp_state & JveState::ProjectModified);
}

void
JveApplication::setLoadingProjectProcessNotRejected(void)
{
    JveLoadingProjectMutex.lock();
    mp_loadingProjectProcessRejected = false;
    JveLoadingProjectMutex.unlock();
}

void
JveApplication::setProjectClosedState(void)
{
    mp_state &= ~(
        JveState::ProjectModified
            | JveState::ProjectHiddenModified
            | JveState::ProjectNew
            | JveState::ProjectOpened
    );
}

void
JveApplication::setProjectOpenedState(void)
{
    mp_state = JveState::ProjectOpened;
}

void
JveApplication::setNewProjectOpenedState(void)
{
    mp_state = (JveState::ProjectOpened | JveState::ProjectNew);
}

void
JveApplication::setProjectHiddenModifiedState(const bool status)
{
    if (status) {
        mp_state |=  JveState::ProjectHiddenModified;
    } else {
        mp_state &= ~JveState::ProjectHiddenModified;
    }
}

void
JveApplication::setProjectModifiedState(const bool status)
{
    if (status) {
        mp_state |=  JveState::ProjectModified;
    } else {
        mp_state &= ~JveState::ProjectModified;
    }

    emit JveGlobalSignals.stateChanged(mp_state);
}


void
JveApplication::justCloseProject(void)
{
    emit JveGlobalSignals.stateChanged(mp_state | JveState::Busy);
    emit JveGlobalSignals.wantShowReport(
        JveReport(
            JveReport::Message,
            JveReport::ProjectClosing
        )
    );

    /*mp_project.close();
    JveIdProvider.clear();
    setProjectClosedState();

    emit JveProjectSignals
            .nameChanged(mp_project.fileName());*/

    emit JveGlobalSignals.wantShowReport(
        JveReport(
            JveReport::Success,
            JveReport::ProjectClosed
        )
    );
    emit JveGlobalSignals.stateChanged(mp_state);
}

void
JveApplication::closeProject(
    const int      options,
    const QString &loadingFilePath
)
{
    bool canRouteMore = true;

    // opened
    if (isProjectOpened()) {
        // forced close
        if (options & JveOption::CloseProjectForced) {
            justCloseProject();
        // modified
        } else if (isProjectModified()) {
            canRouteMore = false;
            emit JveProjectSignals.wantShowModifiedProjectWarning(
                options,
                loadingFilePath
            );
        // hidden modified
        } else if (isProjectHiddenModified()) {

            // new (close only)
            if (isProjectNew()) {
                justCloseProject();
            // exists
            } else {
                emit JveGlobalSignals.stateChanged(mp_state | JveState::Busy);
                emit JveGlobalSignals.wantShowReport(
                    JveReport(
                        JveReport::Message,
                        JveReport::ProjectClosing
                    )
                );

                try {

                    /*mp_project.save(mp_project.filePath());

                    emit JveProjectSignals
                            .wantAddToRecentItems(mp_project.filePath());

                    mp_project.close();
                    JveIdProvider.clear();
                    setProjectClosedState();

                    emit JveProjectSignals
                            .nameChanged(mp_project.fileName());*/

                    emit JveGlobalSignals.wantShowReport(
                        JveReport(
                            JveReport::Success,
                            JveReport::ProjectClosed
                        )
                    );

                } catch (const JveReport &report) {
                    canRouteMore = false;
                    if (options & JveOption::Quit) {
                        JveGlobalSignals.wantRejectQuit();
                    }
                    emit JveGlobalSignals.wantShowReport(report);
                }

                emit JveGlobalSignals.stateChanged(mp_state);
            }

        // close only (not forced, not modified, not hidden modified)
        } else {
            justCloseProject();
        }
    } // <-- opened

    // route more
    if (canRouteMore) {
        routeOptions(
            options & ~JveOption::CloseProject,
            loadingFilePath,
            nullptr
        );
    }
}

void
JveApplication::loadNewProject(void)
{
    // can not load over opened other
    if (isProjectOpened()) {
        return;
    }

    emit JveGlobalSignals.stateChanged(mp_state | JveState::Busy);
    emit JveGlobalSignals.wantShowReport(
        JveReport(
            JveReport::Message,
            JveReport::ProjectNewLoading
        )
    );

    try {

        /*mp_project.loadNew();
        setNewProjectOpenedState();

        emit JveProjectSignals
                .nameChanged(mp_project.fileName());*/

        emit JveGlobalSignals.wantShowReport(
            JveReport(
                JveReport::Success,
                JveReport::ProjectNewLoaded
            )
        );

    } catch (const JveReport &report) {
        emit JveGlobalSignals.wantShowReport(report);
    }

    emit JveGlobalSignals.stateChanged(mp_state);
}

void
JveApplication::loadProject(const QString &loadingFilePath)
{
    // can not load over opened other
    if (isProjectOpened()) {
        return;
    }

    setLoadingProjectProcessNotRejected();

    emit JveGlobalSignals.stateChanged(mp_state | JveState::Busy);
    emit JveGlobalSignals.wantShowReport(
        JveReport(
            JveReport::Message,
            JveReport::ProjectLoading
        )
    );

    emit JveProjectSignals
            .wantShowLoadingProjectProgress();

    try {

        //mp_project.load(loadingFilePath);

        qDebug() << isLoadingProjectProcessRejected();

        setProjectOpenedState();

        /*bool x        = false;
        int  progress = 0;

        if (isLoadingProjectProcessRejected()) {
            throw x;
        }

        QFile loadingFile = mp_project.loadFile(loadingFilePath);
        int   version     = mp_project.determineVersion(&loadingFile);

        if (isLoadingProjectProcessRejected()) {
            throw x;
        }

        progress += 5;
        emit JveProjectSignals.loadingProgressUpdated(progress);

        for (int i = 0; i < 95; i++, progress++) {

            if (isLoadingProjectProcessRejected()) {
                throw x;
            }

            QThread::usleep(30000);
            emit JveProjectSignals.loadingProgressUpdated(progress);
        }

        setProjectOpenedState();*/

        /*emit JveProjectSignals
                .nameChanged(mp_project.fileName());
        emit JveProjectSignals
                .wantAddToRecentItems(mp_project.filePath());*/

        emit JveGlobalSignals.wantShowReport(
            JveReport(
                JveReport::Success,
                JveReport::ProjectLoaded
            )
        );

    } catch (const JveReport &report) {
        if (JveReport::LoadingProjectProcessRejected == report.subType()) {
            //mp_project.close();
            JveIdProvider.clear();
            setProjectClosedState();
        }
        emit JveGlobalSignals
                .wantShowReport(report);
    }

    emit JveProjectSignals
            .loadingProcessCompleted();
    emit JveGlobalSignals
            .stateChanged(mp_state);
}

void
JveApplication::saveProject(
    const int      options,
    const QString &loadingFilePath,
    const QString &savingFilePath
)
{
    bool canRouteMore = true;

    // opened and saveable
    if (isProjectOpened() && nullptr != savingFilePath) {
        emit JveGlobalSignals.stateChanged(mp_state | JveState::Busy);
        emit JveGlobalSignals.wantShowReport(
            JveReport(
                JveReport::Message,
                JveReport::ProjectSaving
            )
        );

        try {

            /*mp_project.save(savingFilePath);
            setProjectOpenedState();

            emit JveProjectSignals
                    .nameChanged(mp_project.fileName());
            emit JveProjectSignals
                    .wantAddToRecentItems(mp_project.filePath());*/

            emit JveGlobalSignals.wantShowReport(
                JveReport(
                    JveReport::Success,
                    JveReport::ProjectSaved
                )
            );

        } catch (const JveReport &report) {
            canRouteMore = false;
            emit JveGlobalSignals.wantShowReport(report);
        }

        emit JveGlobalSignals.stateChanged(mp_state);
    }

    // route more
    if (canRouteMore) {
        routeOptions(
            options & ~JveOption::SaveProject,
            loadingFilePath,
            nullptr
        );
    }
}

void
JveApplication::routeOptions(
    const int      options,
    const QString &loadingFilePath,
    const QString &savingFilePath
)
{
    // save project
    if (options & JveOption::SaveProject) {
        saveProject(options, loadingFilePath, savingFilePath);
    // close project
    } else if (options & JveOption::CloseProject) {
        closeProject(options, loadingFilePath);
    // accept quit
    } else if (options & JveOption::Quit) {
        emit JveGlobalSignals.wantAcceptQuit();
    // load new project
    } else if (options & JveOption::LoadNewProject) {
        loadNewProject();
    // load project
    } else if (options & JveOption::LoadProject) {
        loadProject(loadingFilePath);
    }
}

void
JveApplication::addSourcesItems(const QStringList &resourcesList)
{
    emit JveGlobalSignals.stateChanged(mp_state | JveState::Busy);
    //mp_project.sourcesModel()->addItems(resourcesList);
    emit JveGlobalSignals.stateChanged(mp_state);
}

void
JveApplication::watchUiChangeEventType(const int eventType)
{
    JveProjectMutex.lock();

    if (
        QEvent::LanguageChange == eventType
            && isProjectOpened()
            && isProjectNew()
    ) {
        /*mp_project.updateTranslations();

        emit JveProjectSignals
                .nameChanged(mp_project.fileName());*/
    }

    JveProjectMutex.unlock();
}

void
JveApplication::slotExit(void)
{
    JveProjectMutex.lock();

    routeOptions(
        JveOption::Quit
            | (
                isProjectOpened()
                    ? JveOption::CloseProject
                    : JveOption::None
            ),
        nullptr,
        nullptr
    );

    JveProjectMutex.unlock();
}

void
JveApplication::slotCloseProject(void)
{
    JveProjectMutex.lock();

    closeProject(
        JveOption::CloseProject,
        nullptr
    );

    JveProjectMutex.unlock();
}

void
JveApplication::slotLoadNewProject(void)
{
    JveProjectMutex.lock();

    routeOptions(
        JveOption::CloseProject | JveOption::LoadNewProject,
        nullptr,
        nullptr
    );

    JveProjectMutex.unlock();
}

void
JveApplication::slotLoadProject(const QString &loadingFilePath)
{
    JveProjectMutex.lock();

    routeOptions(
        JveOption::CloseProject | JveOption::LoadProject,
        loadingFilePath,
        nullptr
    );

    JveProjectMutex.unlock();
}

void
JveApplication::slotRejectLoadingProjectProcess(void)
{
    JveLoadingProjectMutex.lock();
    mp_loadingProjectProcessRejected = true;
    qDebug() << "set rejected" << mp_loadingProjectProcessRejected;
    JveLoadingProjectMutex.unlock();
}

void
JveApplication::slotSaveProject(
    const int      options,
    const QString &loadingFilePath
)
{
    JveProjectMutex.lock();

    // new
    if (isProjectNew()) {
        emit JveProjectSignals.wantShowSaveProjectDialog(
            options,
            loadingFilePath
        );
    // exists
    } else {
        /*saveProject(
            options,
            loadingFilePath,
            mp_project.filePath()
        );*/
    }

    JveProjectMutex.unlock();
}

void
JveApplication::slotSaveProjectAs(const QString &savingFilePath)
{
    JveProjectMutex.lock();

    saveProject(
        JveOption::None,
        nullptr,
        savingFilePath
    );

    JveProjectMutex.unlock();
}

void
JveApplication::slotRouteOptions(
    const int      options,
    const QString &loadingFilePath,
    const QString &savingFilePath
)
{
    JveProjectMutex.lock();

    routeOptions(
        options,
        loadingFilePath,
        savingFilePath
    );

    JveProjectMutex.unlock();
}

void
JveApplication::slotAddSourcesItems(const QStringList &resourcesList)
{
    JveProjectMutex.lock();

    if (isProjectOpened()) {
        addSourcesItems(resourcesList);
    }

    JveProjectMutex.unlock();
}


