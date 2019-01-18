

#include "JveApplication.h"


#include <QEvent>


#include "../definitions/JveOption.h"
#include "../definitions/JveState.h"

#include "../mutexes/JveProjectMutex.h"
#include "../utils/JveIdProvider.h"

#include "JveReport.h"
#include "JveProject.h"

#include "../signals/JveGlobalSignals.h"
#include "../signals/JveProjectSignals.h"


JveApplication::JveApplication(void)
    : QObject(nullptr),
        mp_state(JveState::None),
        mp_project(this)
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
}

JveApplication::~JveApplication(void)
{
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

    if (!isProjectNew()) {
        emit JveProjectSignals
                .wantAddToRecentItems(mp_project.filePath());
    }

    mp_project.close();
    JveIdProvider.clear();
    setProjectClosedState();

    emit JveProjectSignals
            .nameChanged(mp_project.fileName());

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
    const QString &loadingProjectUrl
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
                loadingProjectUrl
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

                    mp_project.save(mp_project.filePath());

                    emit JveProjectSignals
                            .wantAddToRecentItems(mp_project.filePath());

                    mp_project.close();
                    JveIdProvider.clear();
                    setProjectClosedState();

                    emit JveProjectSignals
                            .nameChanged(mp_project.fileName());

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
            loadingProjectUrl,
            nullptr
        );
    }
}

void
JveApplication::loadNewProject(void)
{
    emit JveGlobalSignals.stateChanged(mp_state | JveState::Busy);
    emit JveGlobalSignals.wantShowReport(
        JveReport(
            JveReport::Message,
            JveReport::ProjectNewLoading
        )
    );

    try {

        mp_project.loadNew();
        setNewProjectOpenedState();

        emit JveProjectSignals
                .nameChanged(mp_project.fileName());

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
JveApplication::loadProject(const QString &loadingProjectUrl)
{
    emit JveGlobalSignals.stateChanged(mp_state | JveState::Busy);
    emit JveGlobalSignals.wantShowReport(
        JveReport(
            JveReport::Message,
            JveReport::ProjectLoading
        )
    );

    try {

        mp_project.load(loadingProjectUrl);
        setProjectOpenedState();

        emit JveProjectSignals
                .nameChanged(mp_project.fileName());

        emit JveGlobalSignals.wantShowReport(
            JveReport(
                JveReport::Success,
                JveReport::ProjectLoaded
            )
        );

    } catch (const JveReport &report) {
        emit JveGlobalSignals.wantShowReport(report);
    }

    emit JveGlobalSignals.stateChanged(mp_state);
}

void
JveApplication::saveProject(
    const int      options,
    const QString &loadingProjectUrl,
    const QString &savingProjectUrl
)
{
    bool canRouteMore = true;

    // opened and saveable
    if (isProjectOpened() && nullptr != savingProjectUrl) {
        emit JveGlobalSignals.stateChanged(mp_state | JveState::Busy);
        emit JveGlobalSignals.wantShowReport(
            JveReport(
                JveReport::Message,
                JveReport::ProjectSaving
            )
        );

        try {

            mp_project.save(savingProjectUrl);
            setNewProjectOpenedState();

            emit JveProjectSignals
                    .nameChanged(mp_project.fileName());

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
            loadingProjectUrl,
            nullptr
        );
    }
}

void
JveApplication::routeOptions(
    const int      options,
    const QString &loadingProjectUrl,
    const QString &savingProjectUrl
)
{
    // save project
    if (options & JveOption::SaveProject) {
        saveProject(options, loadingProjectUrl, savingProjectUrl);
    // close project
    } else if (options & JveOption::CloseProject) {
        closeProject(options, loadingProjectUrl);
    // accept quit
    } else if (options & JveOption::Quit) {
        emit JveGlobalSignals.wantAcceptQuit();
    // load new project
    } else if (options & JveOption::LoadNewProject) {
        loadNewProject();
    // load project
    } else if (options & JveOption::LoadProject) {
        loadProject(loadingProjectUrl);
    }
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
        mp_project.updateTranslations();

        emit JveProjectSignals
                .nameChanged(mp_project.fileName());
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
                mp_state & JveState::ProjectOpened
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
JveApplication::slotLoadProject(const QString &loadingProjectUrl)
{
    JveProjectMutex.lock();

    routeOptions(
        JveOption::CloseProject | JveOption::LoadProject,
        loadingProjectUrl,
        nullptr
    );

    JveProjectMutex.unlock();
}

void
JveApplication::slotSaveProject(
    const int      options,
    const QString &loadingProjectUrl
)
{
    JveProjectMutex.lock();

    // new
    if (mp_state & JveState::ProjectNew) {
        emit JveProjectSignals.wantShowSaveProjectDialog(
            options,
            loadingProjectUrl
        );
    // exists
    } else {
        saveProject(
            options,
            loadingProjectUrl,
            mp_project.filePath()
        );
    }

    JveProjectMutex.unlock();
}

void
JveApplication::slotSaveProjectAs(const QString &savingProjectUrl)
{
    JveProjectMutex.lock();

    saveProject(
        JveOption::None,
        nullptr,
        savingProjectUrl
    );

    JveProjectMutex.unlock();
}

void
JveApplication::slotRouteOptions(
    const int      options,
    const QString &loadingProjectUrl,
    const QString &savingProjectUrl
)
{
    JveProjectMutex.lock();

    routeOptions(
        options,
        loadingProjectUrl,
        savingProjectUrl
    );

    JveProjectMutex.unlock();
}


