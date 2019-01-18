

#include "jveProject.h"


#include <QFile>
#include <QFileInfo>
#include <QTextStream>


#include "../definitions/jveProjectState.h"
#include "../definitions/jveFsCheckOption.h"
#include "../definitions/jveFsCheckStatus.h"
#include "../definitions/jveProjectVersion.h"
#include "../definitions/jveXmlDefines.h"


#include "jveReport.h"

#include "../utils/jveFsUtils.h"
#include "../utils/jveXmlValidator.h"
#include "../utils/jveProjectUtils.h"

#include "../mutexes/jveLocalizationMutex.h"
#include "../localization/jveTranslation.h"
#include "../localization/jveTr.h"
#include "../signals/jveProjectSignals.h"

#include "../models/jveProjectRootModel.h"
#include "../history/jveHistory.h"


jveProject::jveProject(const bool masterMode)
    : mp_masterMode(masterMode),
        mp_state(jveProjectState::Closed),
        mp_parentDirPath(),
        mp_filePath(),
        mp_fileName(),
        mp_domDocument(),
        mp_rootModel(Q_NULLPTR),
        mp_history(Q_NULLPTR)
{
}

jveProject::~jveProject(void)
{
}

bool
jveProject::isMaster(void) const
{
    return mp_masterMode;
}

int
jveProject::state(void) const
{
    return mp_state;
}

bool
jveProject::isOpened(void) const
{
    return (mp_state & jveProjectState::Opened);
}

bool
jveProject::isNew(void) const
{
    return (mp_state & jveProjectState::New);
}

bool
jveProject::isHiddenModified(void) const
{
    return (mp_state & jveProjectState::HiddenModified);
}

bool
jveProject::isModified(void) const
{
    return (mp_state & jveProjectState::Modified);
}

QString
jveProject::parentDirPath(void) const
{
    return mp_parentDirPath;
}

QString
jveProject::filePath(void) const
{
    return mp_filePath;
}

QString
jveProject::fileName(void) const
{
    return mp_fileName;
}

jveHistory *
jveProject::history(void)
{
    return mp_history;
}

jveSettingsModel *
jveProject::settingsModel(void)
{
    return mp_settingsModel;
}

jveSourcesModel *
jveProject::sourcesModel(void)
{
    return mp_sourcesModel;
}

jveTreeModel *
jveProject::treeModel(void)
{
    return mp_treeModel;
}

jveStateModel *
jveProject::stateModel(void)
{
    return mp_stateModel;
}

void
jveProject::setSettingsModel(jveSettingsModel *settingsModel)
{
    mp_settingsModel = settingsModel;
}

void
jveProject::setSourcesModel(jveSourcesModel *sourcesModel)
{
    mp_sourcesModel = sourcesModel;
}

void
jveProject::setTreeModel(jveTreeModel *treeModel)
{
    mp_treeModel = treeModel;
}

void
jveProject::setStateModel(jveStateModel *stateModel)
{
    mp_stateModel = stateModel;
}

void
jveProject::setHiddenModified(const bool status)
{
    if (status) {
        mp_state |=  jveProjectState::HiddenModified;
    } else {
        mp_state &= ~jveProjectState::HiddenModified;
    }
    if (mp_masterMode) {
        emit jveProjectSignals.stateChanged(mp_state);
    }
}

void
jveProject::setModified(const bool status)
{
    if (status) {
        mp_state |=  jveProjectState::Modified;
    } else {
        mp_state &= ~jveProjectState::Modified;
    }
    if (mp_masterMode) {
        emit jveProjectSignals.stateChanged(mp_state);
    }
}

void
jveProject::updateTranslations(void)
{
    silentUpdateTranslations();
    if (mp_masterMode) {
        emit jveProjectSignals.nameChanged(mp_fileName);
    }
}

void
jveProject::close(void)
{
    if (mp_masterMode && !isNew()) {
        emit jveProjectSignals.wantAddToRecentItems(mp_filePath);
    }

    if (Q_NULLPTR != mp_rootModel) {

        delete mp_rootModel;

        mp_rootModel     = Q_NULLPTR;
        mp_settingsModel = Q_NULLPTR;
        mp_sourcesModel  = Q_NULLPTR;
        mp_treeModel     = Q_NULLPTR;
        mp_stateModel    = Q_NULLPTR;

        if (Q_NULLPTR != mp_history) {
            mp_history->clear();

            delete mp_history;
            mp_history = Q_NULLPTR;
        }

    }

    mp_domDocument   .clear();
    mp_parentDirPath .clear();
    mp_filePath      .clear();
    mp_fileName      .clear();

    mp_state = jveProjectState::Closed;

    if (mp_masterMode) {
        emit jveProjectSignals.nameChanged(mp_fileName);
        emit jveProjectSignals.stateChanged(mp_state);
    }
}

void
jveProject::loadNew(void)
{
    // load XML data from resources
    QFile projectFile(JVE_XML_DATA_NEW_PROJECT_V1_0);

    // try open it
    if (!projectFile.open(QFile::ReadOnly)) {
        throw jveReport(
            jveReport::Error,
            jveReport::FileNotReadable,
            JVE_XML_DATA_NEW_PROJECT_V1_0
        );
    }

    /**********************************************************/

    // validate structure
    int version = jveXmlValidator.validateProjectFile(&projectFile);

    if (jveProjectVersion::Unsupported == version) {
        throw jveReport(
            jveReport::Error,
            jveReport::FileFormatUnsupported,
            JVE_XML_DATA_NEW_PROJECT_V1_0
        );
    }

    /**********************************************************/

    // load data
    projectFile.seek(0);
    mp_domDocument.setContent(&projectFile);
    // upgrade data
    jveProjectUtils::convertProject(
        &mp_domDocument,
         version,
         jveProjectVersion::Last
    );
    projectFile.close();

    // set environment
    setNewEnv();

    // create root model
    mp_rootModel = new jveProjectRootModel(
        this,
        mp_domDocument.documentElement()
    );
    // create history
    mp_history = new jveHistory(this);

    // set up project models
    mp_rootModel->setUp();
    // set up history
    mp_history->setNewProjectLoadedState();
    // set state
    mp_state = jveProjectState::Opened | jveProjectState::New;

    if (mp_masterMode) {
        emit jveProjectSignals.nameChanged(mp_fileName);
        emit jveProjectSignals.stateChanged(mp_state);
    }
}

void
jveProject::load(const QString &filePath)
{
    // check file
    int status = jveFsUtils.checkFile(
        filePath,
        jveFsCheckOption::IsExists | jveFsCheckOption::IsReadable
    );

    switch (status) {
        // not exists
        case jveFsCheckStatus::NotExists:
            throw jveReport(
                jveReport::Error,
                jveReport::FileNotExists,
                filePath
            );
        break;
        // not a file
        case jveFsCheckStatus::NotFile:
            throw jveReport(
                jveReport::Error,
                jveReport::FileIsNotFile,
                filePath
            );
        break;
        // not readable
        case jveFsCheckStatus::NotReadable:
            throw jveReport(
                jveReport::Error,
                jveReport::FileNotReadable,
                filePath
            );
        break;
    }

    /**********************************************************/

    QFile projectFile(filePath);

    // try open file
    if (!projectFile.open(QFile::ReadOnly)) {
        throw jveReport(
            jveReport::Error,
            jveReport::FileNotReadable,
            filePath
        );
    }

    /**********************************************************/

    // validate file structure
    int version = jveXmlValidator.validateProjectFile(&projectFile);

    if (jveProjectVersion::Unsupported == version) {
        throw jveReport(
            jveReport::Error,
            jveReport::FileFormatUnsupported,
            filePath
        );
    }

    /**********************************************************/

    // TODO validate each dom element with id attribute for unique id

    /**********************************************************/

    // load project data
    projectFile.seek(0);
    mp_domDocument.setContent(&projectFile);
    // upgrade project data
    jveProjectUtils::convertProject(
        &mp_domDocument,
         version,
         jveProjectVersion::Last
    );
    projectFile.close();

    // set environment
    setEnv(filePath);

    // create root model
    mp_rootModel = new jveProjectRootModel(
        this,
        mp_domDocument.documentElement()
    );
    // create history
    mp_history = new jveHistory(this);

    // set up project models
    mp_rootModel->setUp();
    // set up history
    mp_history->setProjectLoadedState();
    // set state
    mp_state = jveProjectState::Opened;

    if (mp_masterMode) {
        emit jveProjectSignals.nameChanged(mp_fileName);
        emit jveProjectSignals.stateChanged(mp_state);
    }
}

void
jveProject::save(const QString &filePath, const bool forceMasterMode)
{
    bool    isExistsTargetFile = jveFsUtils.isExists(filePath);
    QString parentDirPath      = jveFsUtils.parentPath(filePath);

    // check for exists file
    if (isExistsTargetFile) {

        // check file
        int status = jveFsUtils.checkFile(
            filePath,
            jveFsCheckOption::IsWritable
        );

        switch (status) {
            // not a file
            case jveFsCheckStatus::NotFile:
                throw jveReport(
                    jveReport::Error,
                    jveReport::FileIsNotFile,
                    filePath
                );
            break;
            // not writable
            case jveFsCheckStatus::NotWritable:
                throw jveReport(
                    jveReport::Error,
                    jveReport::FileNotWritable,
                    filePath
                );
            break;
        }

    // check for new file
    } else {

        // check parent directory
        int status = jveFsUtils.checkDirectory(
            parentDirPath,
            jveFsCheckOption::IsExists | jveFsCheckOption::IsWritable
        );

        switch (status) {
            // parent not exists
            case jveFsCheckStatus::NotExists:
                throw jveReport(
                    jveReport::Error,
                    jveReport::ParentDirectoryNotExists,
                    parentDirPath
                );
            break;
            // parent not a directory
            case jveFsCheckStatus::NotDirectory:
                throw jveReport(
                    jveReport::Error,
                    jveReport::ParentDirectoryIsNotDirectory,
                    parentDirPath
                );
            break;
            // parent not writable
            case jveFsCheckStatus::NotWritable:
                throw jveReport(
                    jveReport::Error,
                    jveReport::ParentDirectoryNotWritable,
                    parentDirPath
                );
            break;
        }

    }

    /**********************************************************/

    QFile projectFile(filePath);

    // try open file
    if (!projectFile.open(QFile::WriteOnly)) {
        if (isExistsTargetFile) {
            throw jveReport(
                jveReport::Error,
                jveReport::FileNotWritable,
                filePath
            );
        } else {
            throw jveReport(
                jveReport::Error,
                jveReport::DirectoryNotWritable,
                parentDirPath
            );
        }
    }

    /**********************************************************/

    QTextStream stream(&projectFile);

    // write data
    stream << mp_domDocument.toString(JVE_XML_FILE_INDENT_SIZE);
    // close file
    projectFile.close();

    // update environment
    setEnv(filePath);
    // set clean state for history
    mp_history->setUndoStackClean();
    // set state
    mp_state = jveProjectState::Opened;

    if (forceMasterMode && mp_masterMode) {
        emit jveProjectSignals.nameChanged(mp_fileName);
        emit jveProjectSignals.stateChanged(mp_state);
    }
}

void
jveProject::setNewEnv(void)
{
    // TODO https://stackoverflow.com/a/28052962/3558278
    QFileInfo info(QDir::currentPath());

    mp_parentDirPath = info.absoluteDir().path();
    mp_filePath      = info.filePath();

    silentUpdateTranslations();
}

void
jveProject::setEnv(const QString &projectFilePath)
{
    QFileInfo info(projectFilePath);

    mp_parentDirPath = info.absoluteDir().path();
    mp_filePath      = info.filePath();
    mp_fileName      = info.fileName();
}

void
jveProject::silentUpdateTranslations(void)
{
    jveLocalizationMutex.lock();
    mp_fileName = jveTr.textAt(jveTranslation::NewProjectName);
    jveLocalizationMutex.unlock();
}


