

#include "jveApplication.h"


#include <QEvent>


#include "../definitions/jveOption.h"
#include "../definitions/jveState.h"

#include "../mutexes/jveProjectMutex.h"

#include "jveProject.h"

#include "../utils/jveIdProvider.h"

#include "jveReport.h"

#include "../signals/jveGlobalSignals.h"
#include "../signals/jveProjectSignals.h"


jveApplication::jveApplication(void)
    : QObject(Q_NULLPTR),
        mp_state(jveState::None),
        mp_project(true)
{
    // ui change event
    connect(
        &jveGlobalSignals,
        SIGNAL(wantSendUiChangeEventType(int)),
        this,
        SLOT(watchUiChangeEventType(int)),
        Qt::QueuedConnection
    );

    // slot exit
    connect(
        &jveGlobalSignals,
        SIGNAL(wantExit()),
        this,
        SLOT(slotExit()),
        Qt::QueuedConnection
    );

    // slot close project
    connect(
        &jveProjectSignals,
        SIGNAL(wantCloseProject()),
        this,
        SLOT(slotCloseProject()),
        Qt::QueuedConnection
    );

    // slot load new project
    connect(
        &jveProjectSignals,
        SIGNAL(wantLoadNewProject()),
        this,
        SLOT(slotLoadNewProject()),
        Qt::QueuedConnection
    );
    // slot load project
    connect(
        &jveProjectSignals,
        SIGNAL(wantLoadProject(QString)),
        this,
        SLOT(slotLoadProject(QString)),
        Qt::QueuedConnection
    );

    // slot save project
    connect(
        &jveProjectSignals,
        SIGNAL(wantSaveProject(int, QString)),
        this,
        SLOT(slotSaveProject(int, QString)),
        Qt::QueuedConnection
    );
    // slot save project as
    connect(
        &jveProjectSignals,
        SIGNAL(wantSaveProjectAs(QString)),
        this,
        SLOT(slotSaveProjectAs(QString)),
        Qt::QueuedConnection
    );

    // slot route options
    connect(
        &jveProjectSignals,
        SIGNAL(wantRouteOptions(int, QString, QString)),
        this,
        SLOT(slotRouteOptions(int, QString, QString)),
        Qt::QueuedConnection
    );
}

jveApplication::~jveApplication(void)
{
}

void
jveApplication::justCloseProject(void)
{
    emit jveGlobalSignals.stateChanged(mp_state | jveState::Busy);
    emit jveGlobalSignals.wantShowReport(
        jveReport(
            jveReport::Message,
            jveReport::ProjectClosing
        )
    );

    mp_project.close();
    jveIdProvider.clear();
    mp_state = jveState::None;

    emit jveGlobalSignals.wantShowReport(
        jveReport(
            jveReport::Success,
            jveReport::ProjectClosed
        )
    );
    emit jveGlobalSignals.stateChanged(mp_state);
}

void
jveApplication::closeProject(
    const int      options,
    const QString &loadingProjectUrl
)
{
    bool canRouteMore = true;

    // opened
    if (mp_project.isOpened()) {
        // forced close
        if (options & jveOption::CloseProjectForced) {
            justCloseProject();
        // modified
        } else if (mp_project.isModified()) {
            canRouteMore = false;
            emit jveProjectSignals.wantShowModifiedProjectWarning(
                options,
                loadingProjectUrl
            );
        // hidden modified
        } else if (mp_project.isHiddenModified()) {

            // new (close only)
            if (mp_project.isNew()) {
                justCloseProject();
            // exists
            } else {
                emit jveGlobalSignals.stateChanged(mp_state | jveState::Busy);
                emit jveGlobalSignals.wantShowReport(
                    jveReport(
                        jveReport::Message,
                        jveReport::ProjectClosing
                    )
                );

                try {

                    mp_project.save(mp_project.filePath(), false);
                    mp_project.close();
                    jveIdProvider.clear();
                    mp_state = jveState::None;

                    emit jveGlobalSignals.wantShowReport(
                        jveReport(
                            jveReport::Success,
                            jveReport::ProjectClosed
                        )
                    );

                } catch (const jveReport &report) {
                    canRouteMore = false;
                    if (options & jveOption::Quit) {
                        jveGlobalSignals.wantRejectQuit();
                    }
                    emit jveGlobalSignals.wantShowReport(report);
                }

                emit jveGlobalSignals.stateChanged(mp_state);
            }

        // close only (not forced, not modified, not hidden modified)
        } else {
            justCloseProject();
        }
    } // <-- opened

    // route more
    if (canRouteMore) {
        routeOptions(
            options & ~jveOption::CloseProject,
            loadingProjectUrl,
            Q_NULLPTR
        );
    }
}

void
jveApplication::loadNewProject(void)
{
    emit jveGlobalSignals.stateChanged(mp_state | jveState::Busy);
    emit jveGlobalSignals.wantShowReport(
        jveReport(
            jveReport::Message,
            jveReport::ProjectNewLoading
        )
    );

    try {

        mp_project.loadNew();
        mp_state = jveState::ProjectOpened | jveState::ProjectNew;

        emit jveGlobalSignals.wantShowReport(
            jveReport(
                jveReport::Success,
                jveReport::ProjectNewLoaded
            )
        );

    } catch (const jveReport &report) {
        emit jveGlobalSignals.wantShowReport(report);
    }

    emit jveGlobalSignals.stateChanged(mp_state);
}

void
jveApplication::loadProject(const QString &loadingProjectUrl)
{
    emit jveGlobalSignals.stateChanged(mp_state | jveState::Busy);
    emit jveGlobalSignals.wantShowReport(
        jveReport(
            jveReport::Message,
            jveReport::ProjectLoading
        )
    );

    try {

        mp_project.load(loadingProjectUrl);
        mp_state = jveState::ProjectOpened;

        emit jveGlobalSignals.wantShowReport(
            jveReport(
                jveReport::Success,
                jveReport::ProjectLoaded
            )
        );

    } catch (const jveReport &report) {
        emit jveGlobalSignals.wantShowReport(report);
    }

    emit jveGlobalSignals.stateChanged(mp_state);
}

void
jveApplication::saveProject(
    const int      options,
    const QString &loadingProjectUrl,
    const QString &savingProjectUrl
)
{
    bool canRouteMore = true;

    // opened and saveable
    if (mp_project.isOpened() && Q_NULLPTR != savingProjectUrl) {
        emit jveGlobalSignals.stateChanged(mp_state | jveState::Busy);
        emit jveGlobalSignals.wantShowReport(
            jveReport(
                jveReport::Message,
                jveReport::ProjectSaving
            )
        );

        try {

            mp_project.save(savingProjectUrl);
            mp_state = jveState::ProjectOpened;

            emit jveGlobalSignals.wantShowReport(
                jveReport(
                    jveReport::Success,
                    jveReport::ProjectSaved
                )
            );

        } catch (const jveReport &report) {
            canRouteMore = false;
            emit jveGlobalSignals.wantShowReport(report);
        }

        emit jveGlobalSignals.stateChanged(mp_state);
    }

    // route more
    if (canRouteMore) {
        routeOptions(
            options & ~jveOption::SaveProject,
            loadingProjectUrl,
            Q_NULLPTR
        );
    }
}

void
jveApplication::routeOptions(
    const int      options,
    const QString &loadingProjectUrl,
    const QString &savingProjectUrl
)
{
    // save project
    if (options & jveOption::SaveProject) {
        saveProject(options, loadingProjectUrl, savingProjectUrl);
    // close project
    } else if (options & jveOption::CloseProject) {
        closeProject(options, loadingProjectUrl);
    // accept quit
    } else if (options & jveOption::Quit) {
        emit jveGlobalSignals.wantAcceptQuit();
    // load new project
    } else if (options & jveOption::LoadNewProject) {
        loadNewProject();
    // load project
    } else if (options & jveOption::LoadProject) {
        loadProject(loadingProjectUrl);
    }
}

void
jveApplication::watchUiChangeEventType(const int eventType)
{
    jveProjectMutex.lock();

    if (
        QEvent::LanguageChange == eventType
            && mp_project.isOpened()
            && mp_project.isNew()
    ) {
        mp_project.updateTranslations();
    }

    jveProjectMutex.unlock();
}

void
jveApplication::slotExit(void)
{
    jveProjectMutex.lock();

    routeOptions(
        jveOption::Quit
            | (
                mp_state & jveState::ProjectOpened
                    ? jveOption::CloseProject
                    : jveOption::None
            ),
        Q_NULLPTR,
        Q_NULLPTR
    );

    jveProjectMutex.unlock();
}

void
jveApplication::slotCloseProject(void)
{
    jveProjectMutex.lock();

    closeProject(
        jveOption::CloseProject,
        Q_NULLPTR
    );

    jveProjectMutex.unlock();
}

void
jveApplication::slotLoadNewProject(void)
{
    jveProjectMutex.lock();

    routeOptions(
        jveOption::CloseProject | jveOption::LoadNewProject,
        Q_NULLPTR,
        Q_NULLPTR
    );

    jveProjectMutex.unlock();
}

void
jveApplication::slotLoadProject(const QString &loadingProjectUrl)
{
    jveProjectMutex.lock();

    routeOptions(
        jveOption::CloseProject | jveOption::LoadProject,
        loadingProjectUrl,
        Q_NULLPTR
    );

    jveProjectMutex.unlock();
}

void
jveApplication::slotSaveProject(
    const int      options,
    const QString &loadingProjectUrl
)
{
    jveProjectMutex.lock();

    // new
    if (mp_state & jveState::ProjectNew) {
        emit jveProjectSignals.wantShowSaveProjectDialog(
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

    jveProjectMutex.unlock();
}

void
jveApplication::slotSaveProjectAs(const QString &savingProjectUrl)
{
    jveProjectMutex.lock();

    saveProject(
        jveOption::None,
        Q_NULLPTR,
        savingProjectUrl
    );

    jveProjectMutex.unlock();
}

void
jveApplication::slotRouteOptions(
    const int      options,
    const QString &loadingProjectUrl,
    const QString &savingProjectUrl
)
{
    jveProjectMutex.lock();

    routeOptions(
        options,
        loadingProjectUrl,
        savingProjectUrl
    );

    jveProjectMutex.unlock();
}


