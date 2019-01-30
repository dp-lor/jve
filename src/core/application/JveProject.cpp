

#include "JveProject.h"


#include <QFile>
#include <QFileInfo>
#include <QTextStream>


#include "../definitions/JveFsCheckOption.h"
#include "../definitions/JveFsCheckStatus.h"
#include "../definitions/JveProjectVersion.h"
#include "../definitions/JveXmlDefines.h"


#include "JveReport.h"
#include "JveApplication.h"

#include "../utils/JveFsUtils.h"
#include "../utils/JveXmlValidator.h"
#include "../utils/JveProjectUtils.h"

#include "../mutexes/JveLocalizationMutex.h"
#include "../localization/JveTranslation.h"
#include "../localization/JveTr.h"

#include "../models/JveProjectRootModel.h"
//#include "../history/JveHistory.h"


JveProject::JveProject(JveApplication *app)
    : mp_app(app),
        mp_masterMode(nullptr != mp_app),
        mp_parentDirPath(),
        mp_filePath(),
        mp_fileName(),
        mp_domDocument(),
        mp_rootModel(nullptr)/*,
        mp_history(nullptr)*/
{
}

JveProject::~JveProject(void)
{
}

bool
JveProject::isMater(void) const
{
    return mp_masterMode;
}

QString
JveProject::parentDirPath(void) const
{
    return mp_parentDirPath;
}

QString
JveProject::filePath(void) const
{
    return mp_filePath;
}

QString
JveProject::fileName(void) const
{
    return mp_fileName;
}

QDomDocument &
JveProject::domDocument(void)
{
    return mp_domDocument;
}

/*JveHistory *
JveProject::history(void)
{
    return mp_history;
}*/

JveSettingsModel *
JveProject::settingsModel(void)
{
    return mp_settingsModel;
}

JveSourcesModel *
JveProject::sourcesModel(void)
{
    return mp_sourcesModel;
}

JveTreeModel *
JveProject::treeModel(void)
{
    return mp_treeModel;
}

JveStateModel *
JveProject::stateModel(void)
{
    return mp_stateModel;
}

void
JveProject::setSettingsModel(JveSettingsModel *settingsModel)
{
    mp_settingsModel = settingsModel;
}

void
JveProject::setSourcesModel(JveSourcesModel *sourcesModel)
{
    mp_sourcesModel = sourcesModel;
}

void
JveProject::setTreeModel(JveTreeModel *treeModel)
{
    mp_treeModel = treeModel;
}

void
JveProject::setStateModel(JveStateModel *stateModel)
{
    mp_stateModel = stateModel;
}

void
JveProject::setHiddenModified(const bool status)
{
    if (mp_masterMode) {
        mp_app->setProjectHiddenModifiedState(status);
    }
}

void
JveProject::setModified(const bool status)
{
    if (mp_masterMode) {
        mp_app->setProjectModifiedState(status);
    }
}

void
JveProject::updateTranslations(void)
{
    JveLocalizationMutex.lock();
    mp_fileName = JveTr.textAt(JveTranslation::NewProjectName);
    JveLocalizationMutex.unlock();
}

void
JveProject::close(void)
{
    if (nullptr != mp_rootModel) {

        delete mp_rootModel;

        mp_rootModel     = nullptr;
        mp_settingsModel = nullptr;
        mp_sourcesModel  = nullptr;
        mp_treeModel     = nullptr;
        mp_stateModel    = nullptr;

    }

    /*if (nullptr != mp_history) {
        mp_history->clear();

        delete mp_history;
        mp_history = nullptr;
    }*/

    mp_domDocument   .clear();
    mp_parentDirPath .clear();
    mp_filePath      .clear();
    mp_fileName      .clear();
}

void
JveProject::loadNew(void)
{
    // load XML data from resources
    QFile projectFile(JVE_XML_DATA_NEW_PROJECT_V1_0);

    // try open it
    if (!projectFile.open(QFile::ReadOnly)) {
        throw JveReport(
            JveReport::Error,
            JveReport::FileNotReadable,
            JVE_XML_DATA_NEW_PROJECT_V1_0
        );
    }

    /**********************************************************/

    // validate structure
    int version = JveXmlValidator.validateProjectFile(&projectFile);

    if (JveProjectVersion::Unsupported == version) {
        throw JveReport(
            JveReport::Error,
            JveReport::FileFormatUnsupported,
            JVE_XML_DATA_NEW_PROJECT_V1_0
        );
    }

    /**********************************************************/

    // load data
    projectFile.seek(0);
    mp_domDocument.setContent(&projectFile);
    // upgrade data
    JveProjectUtils::convertProject(
        &mp_domDocument,
         version,
         JveProjectVersion::Last
    );
    projectFile.close();

    // set environment
    setNewEnv();

    // create root model
    mp_rootModel = new JveProjectRootModel(
        this,
        mp_domDocument.documentElement()
    );

    if (mp_masterMode) {
        // create history
        //mp_history = new JveHistory(this);

        // set up project models
        mp_rootModel->setUp();
        // set up history
        //mp_history->setNewProjectLoadedState();
    }
}

void
JveProject::load(const QString &filePath)
{
    throwIfIsMasterAndLoadingProcessRejected();

    // check file
    int status = JveFsUtils.checkFile(
        filePath,
        JveFsCheckOption::IsExists | JveFsCheckOption::IsReadable
    );

    switch (status) {
        // not exists
        case JveFsCheckStatus::NotExists:
            throw JveReport(
                JveReport::Error,
                JveReport::FileNotExists,
                filePath
            );
        // not a file
        case JveFsCheckStatus::NotFile:
            throw JveReport(
                JveReport::Error,
                JveReport::FileIsNotFile,
                filePath
            );
        // not readable
        case JveFsCheckStatus::NotReadable:
            throw JveReport(
                JveReport::Error,
                JveReport::FileNotReadable,
                filePath
            );
    }

    /**********************************************************/

    throwIfIsMasterAndLoadingProcessRejected();

    QFile projectFile(filePath);

    // try open file
    if (!projectFile.open(QFile::ReadOnly)) {
        throw JveReport(
            JveReport::Error,
            JveReport::FileNotReadable,
            filePath
        );
    }

    /**********************************************************/

    throwIfIsMasterAndLoadingProcessRejected();

    // validate file structure
    int version = JveXmlValidator.validateProjectFile(&projectFile);

    if (JveProjectVersion::Unsupported == version) {
        throw JveReport(
            JveReport::Error,
            JveReport::FileFormatUnsupported,
            filePath
        );
    }

    /**********************************************************/

    throwIfIsMasterAndLoadingProcessRejected();

    // TODO validate each dom element with id attribute for unique id

    /**********************************************************/

    throwIfIsMasterAndLoadingProcessRejected();

    // TODO validate dependencies ( regions <-> sources )

    /**********************************************************/

    throwIfIsMasterAndLoadingProcessRejected();

    // load project data
    projectFile.seek(0);
    mp_domDocument.setContent(&projectFile);
    // upgrade project data
    JveProjectUtils::convertProject(
        &mp_domDocument,
         version,
         JveProjectVersion::Last
    );
    projectFile.close();

    // set environment
    setEnv(filePath);

    /**********************************************************/

    throwIfIsMasterAndLoadingProcessRejected();

    // create root model
    mp_rootModel = new JveProjectRootModel(
        this,
        mp_domDocument.documentElement()
    );

    if (mp_masterMode) {
        // create history
        //mp_history = new JveHistory(this);

        // set up project models
        mp_rootModel->setUp();
        // set up history
        //mp_history->setProjectLoadedState();
    }

    /**********************************************************/

    throwIfIsMasterAndLoadingProcessRejected();
}

/*QFile
JveProject::loadFile(const QString &filePath)
{
    // check file
    int status = JveFsUtils.checkFile(
        filePath,
        JveFsCheckOption::IsExists | JveFsCheckOption::IsReadable
    );

    switch (status) {
        // not exists
        case JveFsCheckStatus::NotExists:
            throw JveReport(
                JveReport::Error,
                JveReport::FileNotExists,
                filePath
            );
        // not a file
        case JveFsCheckStatus::NotFile:
            throw JveReport(
                JveReport::Error,
                JveReport::FileIsNotFile,
                filePath
            );
        // not readable
        case JveFsCheckStatus::NotReadable:
            throw JveReport(
                JveReport::Error,
                JveReport::FileNotReadable,
                filePath
            );
    }

    QFile loadingFile(filePath);

    // try open file
    if (!loadingFile.open(QFile::ReadOnly)) {
        throw JveReport(
            JveReport::Error,
            JveReport::FileNotReadable,
            filePath
        );
    }

    return QFile(loadingFile);
}

int
JveProject::determineVersion(QFile *loadingFile) const
{
    QString filePath = loadingFile->fileName();
    int     version  = JveXmlValidator.validateProjectFile(loadingFile);

    // unsupported version
    if (JveProjectVersion::Unsupported == version) {
        loadingFile->close();
        throw JveReport(
            JveReport::Error,
            JveReport::FileFormatUnsupported,
            filePath
        );
    }
}

void
JveProject::loadData(QFile &loadingFile, const int version)
{
    QString filePath = loadingFile.fileName();

    // load project data
    loadingFile.seek(0);
    mp_domDocument.setContent(&loadingFile);
    // upgrade project data
    JveProjectUtils::convertProject(
        &mp_domDocument,
         mp_loadingFileVersion,
         JveProjectVersion::Last
    );
    mp_loadingFile.close();

    // TODO validate each dom element with id attribute for unique id

    // TODO validate dependencies ( regions <-> sources )

    // set environment
    setEnv(filePath);

    // create root model
    mp_rootModel = new JveProjectRootModel(
        this,
        mp_domDocument.documentElement()
    );

    if (mp_masterMode) {
        // create history
        mp_history = new JveHistory(this);

        // set up project models
        //mp_rootModel->setUp();
        // set up history
        //mp_history->setProjectLoadedState();
    }
}*/

void
JveProject::save(const QString &filePath)
{
    bool    isExistsTargetFile = JveFsUtils.isExists(filePath);
    QString parentDirPath      = JveFsUtils.parentPath(filePath);

    // check for exists file
    if (isExistsTargetFile) {

        // check file
        int status = JveFsUtils.checkFile(
            filePath,
            JveFsCheckOption::IsWritable
        );

        switch (status) {
            // not a file
            case JveFsCheckStatus::NotFile:
                throw JveReport(
                    JveReport::Error,
                    JveReport::FileIsNotFile,
                    filePath
                );
            // not writable
            case JveFsCheckStatus::NotWritable:
                throw JveReport(
                    JveReport::Error,
                    JveReport::FileNotWritable,
                    filePath
                );
        }

    // check for new file
    } else {

        // check parent directory
        int status = JveFsUtils.checkDirectory(
            parentDirPath,
            JveFsCheckOption::IsExists | JveFsCheckOption::IsWritable
        );

        switch (status) {
            // parent not exists
            case JveFsCheckStatus::NotExists:
                throw JveReport(
                    JveReport::Error,
                    JveReport::ParentDirectoryNotExists,
                    parentDirPath
                );
            // parent not a directory
            case JveFsCheckStatus::NotDirectory:
                throw JveReport(
                    JveReport::Error,
                    JveReport::ParentDirectoryIsNotDirectory,
                    parentDirPath
                );
            // parent not writable
            case JveFsCheckStatus::NotWritable:
                throw JveReport(
                    JveReport::Error,
                    JveReport::ParentDirectoryNotWritable,
                    parentDirPath
                );
        }

    }

    /**********************************************************/

    QFile projectFile(filePath);

    // try open file
    if (!projectFile.open(QFile::WriteOnly)) {
        if (isExistsTargetFile) {
            throw JveReport(
                JveReport::Error,
                JveReport::FileNotWritable,
                filePath
            );
        } else {
            throw JveReport(
                JveReport::Error,
                JveReport::DirectoryNotWritable,
                parentDirPath
            );
        }
    }

    /**********************************************************/

    // update environment
    setEnv(filePath);

    // TODO rebuild all sources path's for actual project path

    /**********************************************************/

    QTextStream stream(&projectFile);

    // write data
    stream << mp_domDocument.toString(JVE_XML_FILE_INDENT_SIZE);
    // close file
    projectFile.close();

    if (mp_masterMode) {
        // set clean state for history
        //mp_history->setUndoStackClean();
    }
}

void
JveProject::setNewEnv(void)
{
    // TODO https://stackoverflow.com/a/28052962/3558278
    QFileInfo info(QDir::currentPath());

    mp_parentDirPath = info.absoluteDir().path();
    mp_filePath      = info.filePath();

    updateTranslations();
}

void
JveProject::setEnv(const QString &projectFilePath)
{
    QFileInfo info(projectFilePath);

    mp_parentDirPath = info.absoluteDir().path();
    mp_filePath      = info.filePath();
    mp_fileName      = info.fileName();
}

void
JveProject::throwIfIsMasterAndLoadingProcessRejected(void)
{
    if (mp_masterMode && mp_app->isLoadingProjectProcessRejected()) {
        throw JveReport(
            JveReport::Success,
            JveReport::LoadingProjectProcessRejected
        );
    }
}


