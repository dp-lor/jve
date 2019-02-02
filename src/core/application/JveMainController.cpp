

#include "JveMainController.h"


#include <QEvent>
#include <QThread>
#include <QDebug>


#include "../definitions/JveState.h"
#include "../definitions/JveOption.h"

#include "../mutexes/JveProjectMutex.h"
#include "../mutexes/JveLoadingProjectMutex.h"

#include "Jve.h"
#include "JveReport.h"
#include "JveProject.h"

#include "../signals/JveGlobalSignals.h"
#include "../signals/JveProjectSignals.h"
#include "../signals/JveProjectSourcesSignals.h"

//#include "../models/JveSourcesModel.h"


JveMainController::JveMainController(void)
    : QObject(nullptr),
        mp_loadingProjectProgress(0)
{
    // ui change event
    connect(
        &JveGlobalSignals,
        SIGNAL(wantSendUiChangeEventType(int)),
        this,
        SLOT(watchUiChangeEventType(int)),
        Qt::QueuedConnection
    );

    // slot quit
    connect(
        &JveGlobalSignals,
        SIGNAL(wantExit()),
        this,
        SLOT(slotQuit()),
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

    // slot route project options
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

JveMainController::~JveMainController(void)
{
}

bool
JveMainController::isLoadingProjectProcessRejected(void) const
{
    bool rejected;

    JveLoadingProjectMutex.lock();
    rejected = Jve.isLoadingProjectProcessRejected();
    JveLoadingProjectMutex.unlock();

    return rejected;
}

void
JveMainController::resetLoadingProjectProcess(void)
{
    mp_loadingProjectProgress = 0;

    JveLoadingProjectMutex.lock();
    Jve.setLoadingProjectProcessRejected(false);
    JveLoadingProjectMutex.unlock();
}

void
JveMainController::justCloseProject(void)
{
    emit JveGlobalSignals.stateChanged(Jve.state() | JveState::Busy);
    emit JveGlobalSignals.wantShowReport(
        JveReport(
            JveReport::Message,
            JveReport::ProjectClosing
        )
    );

    JveProject::close();

    emit JveProjectSignals
            .nameChanged(Jve.projectFileName());

    emit JveGlobalSignals.wantShowReport(
        JveReport(
            JveReport::Success,
            JveReport::ProjectClosed
        )
    );
    emit JveGlobalSignals.stateChanged(Jve.state());
}

void
JveMainController::closeProject(
    const int      options,
    const QString &loadingFilePath
)
{
    bool canRouteMore = true;

    // opened
    if (Jve.isProjectOpened()) {
        // forced close
        if (options & JveOption::CloseProjectForced) {
            justCloseProject();
        // modified
        } else if (Jve.isProjectModified()) {
            canRouteMore = false;
            emit JveProjectSignals.wantShowModifiedProjectWarning(
                options,
                loadingFilePath
            );
        // hidden modified
        } else if (Jve.isProjectHiddenModified()) {

            // new (close only)
            if (Jve.isProjectNew()) {
                justCloseProject();
            // exists
            } else {
                emit JveGlobalSignals
                        .stateChanged(Jve.state() | JveState::Busy);
                emit JveGlobalSignals.wantShowReport(
                    JveReport(
                        JveReport::Message,
                        JveReport::ProjectClosing
                    )
                );

                try {

                    JveProject::save(Jve.projectFilePath());

                    emit JveProjectSignals
                            .wantAddToRecentItems(Jve.projectFilePath());

                    JveProject::close();

                    emit JveProjectSignals
                            .nameChanged(Jve.projectFileName());

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

                emit JveGlobalSignals.stateChanged(Jve.state());
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
JveMainController::loadNewProject(void)
{
    // can not load over opened other
    if (Jve.isProjectOpened()) {
        return;
    }

    emit JveGlobalSignals.stateChanged(Jve.state() | JveState::Busy);
    emit JveGlobalSignals.wantShowReport(
        JveReport(
            JveReport::Message,
            JveReport::ProjectNewLoading
        )
    );

    try {

        JveProject::loadNew();

        emit JveProjectSignals
                .nameChanged(Jve.projectFileName());

        emit JveGlobalSignals.wantShowReport(
            JveReport(
                JveReport::Success,
                JveReport::ProjectNewLoaded
            )
        );

    } catch (const JveReport &report) {
        emit JveGlobalSignals.wantShowReport(report);
    }

    emit JveGlobalSignals.stateChanged(Jve.state());
}

void
JveMainController::loadProject(const QString &loadingFilePath)
{
    // can not load over opened other
    if (Jve.isProjectOpened()) {
        return;
    }

    resetLoadingProjectProcess();

    emit JveGlobalSignals.stateChanged(Jve.state() | JveState::Busy);
    emit JveGlobalSignals.wantShowReport(
        JveReport(
            JveReport::Message,
            JveReport::ProjectLoading
        )
    );

    emit JveProjectSignals
            .wantShowLoadingProjectProgress();

    try {

        // load file to dom document
        JveProject::loadXmlToDom(loadingFilePath);
        mp_loadingProjectProgress += 2;
        emit JveProjectSignals
                .loadingProgressUpdated(mp_loadingProjectProgress);

        // validate ids
        JveProject::validateIds();
        mp_loadingProjectProgress += 1;
        emit JveProjectSignals
                .loadingProgressUpdated(mp_loadingProjectProgress);

        // validate references
        JveProject::validateReferences();
        mp_loadingProjectProgress += 1;
        emit JveProjectSignals
                .loadingProgressUpdated(mp_loadingProjectProgress);

        // create models
        JveProject::createModels();
        mp_loadingProjectProgress += 1;
        emit JveProjectSignals
                .loadingProgressUpdated(mp_loadingProjectProgress);

        // init sources
        JveProject::initSources();
        mp_loadingProjectProgress += 1;
        emit JveProjectSignals
                .loadingProgressUpdated(mp_loadingProjectProgress);


        for (int i = 0; i < 96; i++, mp_loadingProjectProgress++) {

            if (isLoadingProjectProcessRejected()) {
                throw JveReport(
                    JveReport::Success,
                    JveReport::LoadingProjectProcessRejected
                );
            }

            QThread::usleep(50000);
            emit JveProjectSignals
                    .loadingProgressUpdated(mp_loadingProjectProgress);
        }


        Jve.setProjectOpenedState();


        emit JveProjectSignals
                .nameChanged(Jve.projectFileName());
        emit JveProjectSignals
                .wantAddToRecentItems(Jve.projectFilePath());

        emit JveGlobalSignals.wantShowReport(
            JveReport(
                JveReport::Success,
                JveReport::ProjectLoaded
            )
        );

    } catch (const JveReport &report) {
        if (JveReport::LoadingProjectProcessRejected == report.subType()) {
            JveProject::close();
        }
        emit JveGlobalSignals
                .wantShowReport(report);
    }

    emit JveProjectSignals
            .loadingProcessCompleted();
    emit JveGlobalSignals
            .stateChanged(Jve.state());
}

void
JveMainController::saveProject(
    const int      options,
    const QString &loadingFilePath,
    const QString &savingFilePath
)
{
    bool canRouteMore = true;

    // opened and saveable
    if (Jve.isProjectOpened() && nullptr != savingFilePath) {
        emit JveGlobalSignals.stateChanged(Jve.state() | JveState::Busy);
        emit JveGlobalSignals.wantShowReport(
            JveReport(
                JveReport::Message,
                JveReport::ProjectSaving
            )
        );

        try {

            JveProject::save(savingFilePath);

            emit JveProjectSignals
                    .nameChanged(Jve.projectFileName());
            emit JveProjectSignals
                    .wantAddToRecentItems(Jve.projectFilePath());

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

        emit JveGlobalSignals.stateChanged(Jve.state());
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
JveMainController::routeOptions(
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
JveMainController::addSourcesItems(const QStringList &resourcesList)
{
    emit JveGlobalSignals.stateChanged(Jve.state() | JveState::Busy);
    //mp_project.sourcesModel()->addItems(resourcesList);
    emit JveGlobalSignals.stateChanged(Jve.state());
}

void
JveMainController::watchUiChangeEventType(const int eventType)
{
    JveProjectMutex.lock();

    if (
        QEvent::LanguageChange == eventType
            && Jve.isProjectOpened()
            && Jve.isProjectNew()
    ) {
        Jve.updateProjectNameTranslation();

        emit JveProjectSignals
                .nameChanged(Jve.projectFileName());
    }

    JveProjectMutex.unlock();
}

void
JveMainController::slotQuit(void)
{
    JveProjectMutex.lock();

    routeOptions(
        JveOption::Quit
            | (
                Jve.isProjectOpened()
                    ? JveOption::CloseProject
                    : JveOption::None
            ),
        nullptr,
        nullptr
    );

    JveProjectMutex.unlock();
}

void
JveMainController::slotCloseProject(void)
{
    JveProjectMutex.lock();

    closeProject(
        JveOption::CloseProject,
        nullptr
    );

    JveProjectMutex.unlock();
}

void
JveMainController::slotLoadNewProject(void)
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
JveMainController::slotLoadProject(const QString &loadingFilePath)
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
JveMainController::slotSaveProject(
    const int      options,
    const QString &loadingFilePath
)
{
    JveProjectMutex.lock();

    // new
    if (Jve.isProjectNew()) {
        emit JveProjectSignals.wantShowSaveProjectDialog(
            options,
            loadingFilePath
        );
    // exists
    } else {
        saveProject(
            options,
            loadingFilePath,
            Jve.projectFilePath()
        );
    }

    JveProjectMutex.unlock();
}

void
JveMainController::slotSaveProjectAs(const QString &savingFilePath)
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
JveMainController::slotRouteOptions(
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
JveMainController::slotAddSourcesItems(const QStringList &resourcesList)
{
    JveProjectMutex.lock();

    if (Jve.isProjectOpened()) {
        addSourcesItems(resourcesList);
    }

    JveProjectMutex.unlock();
}


