

#include "jveApplication.h"


#include <QEvent>
#include <QFileInfo>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDomDocument>


#include "../definitions/jveProjectFileDefines.h"
#include "../definitions/jveFsCheckOption.h"
#include "../definitions/jveFsCheckStatus.h"
#include "../definitions/jveProjectVersion.h"
#include "../definitions/jveOption.h"
#include "../definitions/jveState.h"

#include "../mutexes/jveProjectMutex.h"
#include "../mutexes/jveLocalizationMutex.h"

#include "../history/jveHistory.h"

#include "../utils/jveIdProvider.h"
#include "../utils/jveFsUtils.h"
#include "../utils/jveXmlValidator.h"
#include "../utils/jveProjectUtils.h"

#include "jveReport.h"

#include "../signals/jveGlobalSignals.h"
#include "../signals/jveProjectSignals.h"

#include "../models/jveProject.h"

#include "../localization/jveTranslation.h"
#include "../localization/jveTr.h"


jveApplication::jveApplication(void)
    : QObject(Q_NULLPTR),
        mp_history(Q_NULLPTR),
        mp_projectDom(),
        mp_project(Q_NULLPTR)
{
    // initial project state
    clear();

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

    // slot route options
    connect(
        &jveProjectSignals,
        SIGNAL(wantRouteOptions(int, QString, QString)),
        this,
        SLOT(slotRouteOptions(int, QString, QString)),
        Qt::QueuedConnection
    );

    // ui change event
    connect(
        &jveGlobalSignals,
        SIGNAL(wantSendUiChangeEventType(int)),
        this,
        SLOT(watchUiChangeEventType(int)),
        Qt::QueuedConnection
    );
}

jveApplication::~jveApplication(void)
{
}

jveHistory *
jveApplication::history(void)
{
    return mp_history;
}

void
jveApplication::setHistory(jveHistory *history)
{
    mp_history = history;

    mp_history->setApplication(this);
}

jveProjectSettings *
jveApplication::projectSettings(void)
{
    return mp_projectSettings;
}

jveProjectState *
jveApplication::projectState(void)
{
    return mp_projectState;
}

jveProjectSources *
jveApplication::projectSources(void)
{
    return mp_projectSources;
}

void
jveApplication::setProjectHiddenModified(const bool status)
{
    if (status) {
        mp_state |=  jveState::ProjectHiddenModified;
    } else {
        mp_state &= ~jveState::ProjectHiddenModified;
    }
}

void
jveApplication::setProjectModified(const bool status)
{
    if (status) {
        mp_state |=  jveState::ProjectModified;
    } else {
        mp_state &= ~jveState::ProjectModified;
    }

    emit jveGlobalSignals.stateChanged(mp_state);
}

void
jveApplication::setProjectSettings(jveProjectSettings *settings)
{
    mp_projectSettings = settings;
}

void
jveApplication::setProjectState(jveProjectState *state)
{
    mp_projectState = state;
}

void
jveApplication::setProjectSources(jveProjectSources *sources)
{
    mp_projectSources = sources;
}

QString
jveApplication::projectDirPath(void) const
{
    return mp_projectDirPath;
}

void 
jveApplication::clear(void)
{
    jveIdProvider.clear();

    if (Q_NULLPTR != mp_history) {
        mp_history->clear();
    }
    if (Q_NULLPTR != mp_project) {
        delete mp_project;
        mp_project = Q_NULLPTR;
    }
    mp_projectDom       .clear();
    mp_projectName      .clear();
    mp_projectFilePath  .clear();
    mp_projectDirPath   .clear();

    mp_state = jveState::None;
}

void
jveApplication::setProjectFileEnv(const QString &projectFilePath)
{
    QFileInfo info(projectFilePath);

    mp_projectName     = info.fileName();
    mp_projectFilePath = info.absoluteFilePath();
    mp_projectDirPath  = info.absoluteDir().absolutePath();
}

void
jveApplication::closeProjectProcess(void)
{
    emit jveGlobalSignals.stateChanged(mp_state | jveState::Busy);
    emit jveGlobalSignals.wantShowReport(
        jveReport(
            jveReport::Message,
            jveReport::ProjectClosing
        )
    );
    clear();
    emit jveProjectSignals.projectNameChanged(mp_projectName);
    emit jveGlobalSignals.wantShowReport(
        jveReport(
            jveReport::Success,
            jveReport::ProjectClosed
        )
    );
    emit jveGlobalSignals.stateChanged(mp_state);
}

void
jveApplication::saveProjectProcess(const QString &savingProjectUrl)
{
    // check file (exists file only)
    if (jveFsUtils.isExists(savingProjectUrl)) {

        int status = jveFsUtils.checkFile(
            savingProjectUrl,
            jveFsCheckOption::IsWritable
        );

        switch (status) {
            // not a file
            case jveFsCheckStatus::NotFile:
                throw jveReport(
                    jveReport::Error,
                    jveReport::FileIsNotFile,
                    savingProjectUrl
                );
            break;
            // not writable
            case jveFsCheckStatus::NotWritable:
                throw jveReport(
                    jveReport::Error,
                    jveReport::FileNotWritable,
                    savingProjectUrl
                );
            break;
        }

    // check parent directory (file not exists)
    } else {

        QString parentPath = jveFsUtils.parentPath(savingProjectUrl);

        int status = jveFsUtils.checkDirectory(
            parentPath,
            jveFsCheckOption::IsExists | jveFsCheckOption::IsWritable
        );

        switch (status) {
            // parent not exists
            case jveFsCheckStatus::NotExists:
                throw jveReport(
                    jveReport::Error,
                    jveReport::ParentDirectoryNotExists,
                    parentPath
                );
            break;
            // parent not a directory
            case jveFsCheckStatus::NotDirectory:
                throw jveReport(
                    jveReport::Error,
                    jveReport::ParentDirectoryIsNotDirectory,
                    parentPath
                );
            break;
            // parent not writable
            case jveFsCheckStatus::NotWritable:
                throw jveReport(
                    jveReport::Error,
                    jveReport::ParentDirectoryNotWritable,
                    parentPath
                );
            break;
        }

    }

    // open file for write
    // TODO check opening status for write
    QFile projectFile(savingProjectUrl);
    projectFile.open(QFile::WriteOnly);
    // write data
    QTextStream projectData(&projectFile);
    projectData << mp_projectDom.toString(JVE_PROJECT_FILE_XML_INDENT_SIZE);
    // close file
    projectFile.close();

    // update project file environment
    setProjectFileEnv(savingProjectUrl);
    // set state
    mp_state = jveState::ProjectOpened;

    // emit update recent projects list
    emit jveProjectSignals.wantAddProjectUrlToRecentItems(mp_projectFilePath);
}

void
jveApplication::loadProjectProcess(const QString &loadingProjectUrl)
{
    // check file
    int status = jveFsUtils.checkFile(
        loadingProjectUrl,
        jveFsCheckOption::IsExists | jveFsCheckOption::IsReadable
    );

    switch (status) {
        // not exists
        case jveFsCheckStatus::NotExists:
            throw jveReport(
                jveReport::Error,
                jveReport::FileNotExists,
                loadingProjectUrl
            );
        break;
        // not a file
        case jveFsCheckStatus::NotFile:
            throw jveReport(
                jveReport::Error,
                jveReport::FileIsNotFile,
                loadingProjectUrl
            );
        break;
        // not readable
        case jveFsCheckStatus::NotReadable:
            throw jveReport(
                jveReport::Error,
                jveReport::FileNotReadable,
                loadingProjectUrl
            );
        break;
    }

    // open file
    // TODO check opening status for read
    QFile projectFile(loadingProjectUrl);
    projectFile.open(QFile::ReadOnly);

    // validate project file structure
    int version = jveXmlValidator.validateProjectFile(&projectFile);
    if (jveProjectVersion::Unsupported == version) {
        throw jveReport(
            jveReport::Error,
            jveReport::FileFormatUnsupported,
            loadingProjectUrl
        );
    }

    // TODO validate each sources item for unique id

    // load project data
    projectFile.seek(0);
    mp_projectDom.setContent(&projectFile);
    jveProjectUtils::convertProject(
        &mp_projectDom,
         version,
         jveProjectVersion::Last
    );
    projectFile.close();

    // update project environment
    setProjectFileEnv(loadingProjectUrl);
    // set up models (recursively)
    mp_project = new jveProject(
        this,
        mp_projectDom.documentElement()
    );
    mp_project->setUp();
    // set state
    mp_state = jveState::ProjectOpened;

    // emit update recent projects list
    emit jveProjectSignals.wantAddProjectUrlToRecentItems(mp_projectFilePath);
}

void
jveApplication::closeProject(
    const int      options,
    const QString &loadingProjectUrl
)
{
    bool canRouteMore = true;

    // opened
    if (mp_state & jveState::ProjectOpened) {
        // forced close
        if (options & jveOption::CloseProjectForced) {
            closeProjectProcess();
        // modified
        } else if (mp_state & jveState::ProjectModified) {
            canRouteMore = false;
            emit jveProjectSignals.wantShowModifiedProjectWarning(
                options,
                loadingProjectUrl
            );
        // hidden modified
        } else if (mp_state & jveState::ProjectHiddenModified) {

            // new (close only)
            if (mp_state & jveState::ProjectNew) {
                closeProjectProcess();
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
                    saveProjectProcess(mp_projectFilePath);
                    clear();
                    emit jveProjectSignals.projectNameChanged(mp_projectName);
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
            closeProjectProcess();
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
jveApplication::saveProject(
    const int      options,
    const QString &loadingProjectUrl,
    const QString &savingProjectUrl
)
{
    bool canRouteMore = true;

    // opened and saveable
    if (
        mp_state & jveState::ProjectOpened
            && Q_NULLPTR != savingProjectUrl
    ) {
        emit jveGlobalSignals.stateChanged(mp_state | jveState::Busy);
        emit jveGlobalSignals.wantShowReport(
            jveReport(
                jveReport::Message,
                jveReport::ProjectSaving
            )
        );
        try {
            saveProjectProcess(savingProjectUrl);
            mp_history->setUndoStackClean();
            emit jveProjectSignals.projectNameChanged(mp_projectName);
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
        loadProjectProcess(loadingProjectUrl);
        mp_history->setProjectLoadedState();
        emit jveProjectSignals.projectNameChanged(mp_projectName);
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
jveApplication::loadNewProject(void)
{
    emit jveGlobalSignals.stateChanged(mp_state | jveState::Busy);
    emit jveGlobalSignals.wantShowReport(
        jveReport(
            jveReport::Message,
            jveReport::ProjectNewLoading
        )
    );

    // TODO try load new project from preferences and validate it

    mp_state = jveState::ProjectOpened | jveState::ProjectNew;

    jveLocalizationMutex.lock();
    mp_projectName = jveTr.textAt(jveTranslation::NewProjectName);
    jveLocalizationMutex.unlock();

    mp_history->setNewProjectLoadedState();

    emit jveProjectSignals.projectNameChanged(mp_projectName);
    emit jveGlobalSignals.wantShowReport(
        jveReport(
            jveReport::Success,
            jveReport::ProjectNewLoaded
        )
    );
    emit jveGlobalSignals.stateChanged(mp_state);
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
            && (mp_state & jveState::ProjectNew)
    ) {
        // update project name
        jveLocalizationMutex.lock();
        mp_projectName = jveTr.textAt(jveTranslation::NewProjectName);
        jveLocalizationMutex.unlock();

        emit jveProjectSignals.projectNameChanged(mp_projectName);
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
            mp_projectFilePath
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


