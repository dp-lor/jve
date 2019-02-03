

#include "JveProject.h"


#include <QFile>
#include <QTextStream>
#include <QDomDocument>


#include "../definitions/JveXmlDefines.h"
#include "../definitions/JveProjectFileDefines.h"

#include "../definitions/JveFsCheckOption.h"
#include "../definitions/JveFsCheckStatus.h"
#include "../definitions/JveProjectVersion.h"

#include "../mutexes/JveLoadingProjectMutex.h"

#include "Jve.h"
#include "JveReport.h"

#include "../utils/JveIdProvider.h"
#include "../utils/JveFsUtils.h"
#include "../utils/JveXmlValidator.h"
#include "../utils/JveProjectUtils.h"

#include "../history/JveHistory.h"


void
JveProject::close(void)
{
    Jve.clear();
    JveIdProvider.clear();
    Jve.setProjectClosedState();
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

    //------------------------------------------------------------//

    // validate structure
    int version = JveXmlValidator.validateProjectFile(&projectFile);

    if (JveProjectVersion::Unsupported == version) {
        throw JveReport(
            JveReport::Error,
            JveReport::FileFormatUnsupported,
            JVE_XML_DATA_NEW_PROJECT_V1_0
        );
    }

    //------------------------------------------------------------//

    // load data
    projectFile.seek(0);
    Jve.domDocument().setContent(&projectFile);
    // upgrade data
    JveProjectUtils::convertProject(
        &(Jve.domDocument()),
         version,
         JveProjectVersion::Last
    );
    projectFile.close();

    // set environment
    Jve.setNewProjectEnv();

    // attach models to dom
    Jve.createAndAttachProjectModels();

    // set up history
    Jve.history().setNewProjectLoadedState();
    // set clean opened new project state
    Jve.setNewProjectOpenedState();

    // set up project models
    Jve.setUpProjectModels();
}

void
JveProject::load(const QString &filePath)
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

    //------------------------------------------------------------//

    QFile projectFile(filePath);

    // try open file
    if (!projectFile.open(QFile::ReadOnly)) {
        throw JveReport(
            JveReport::Error,
            JveReport::FileNotReadable,
            filePath
        );
    }

    //------------------------------------------------------------//

    // validate file structure
    int version = JveXmlValidator.validateProjectFile(&projectFile);

    if (JveProjectVersion::Unsupported == version) {
        throw JveReport(
            JveReport::Error,
            JveReport::FileFormatUnsupported,
            filePath
        );
    }

    //------------------------------------------------------------//

    // load project data
    projectFile.seek(0);
    Jve.domDocument().setContent(&projectFile);
    // upgrade data
    JveProjectUtils::convertProject(
        &(Jve.domDocument()),
         version,
         JveProjectVersion::Last
    );
    projectFile.close();

    // set environment
    Jve.setProjectEnv(filePath);

    //------------------------------------------------------------//

    if (isLoadingProcessRejected()) {
        throw JveReport(
            JveReport::Success,
            JveReport::LoadingProjectProcessRejected
        );
    }

    //------------------------------------------------------------//

    // TODO validate each dom element with id attribute for unique id

    //------------------------------------------------------------//

    if (isLoadingProcessRejected()) {
        throw JveReport(
            JveReport::Success,
            JveReport::LoadingProjectProcessRejected
        );
    }

    //------------------------------------------------------------//

    // TODO validate id references ( sources <-> regions )

    //------------------------------------------------------------//

    if (isLoadingProcessRejected()) {
        throw JveReport(
            JveReport::Success,
            JveReport::LoadingProjectProcessRejected
        );
    }

    //------------------------------------------------------------//

    // attach models to dom
    Jve.createAndAttachProjectModels();
    // TODO init models here

    //------------------------------------------------------------//

    if (isLoadingProcessRejected()) {
        throw JveReport(
            JveReport::Success,
            JveReport::LoadingProjectProcessRejected
        );
    }

    //------------------------------------------------------------//

    // add project size to statistics
    // 6 = number of actions with project data (check, read, validate, etc..)
    Jve.addToResourcesStat(Jve.projectFileSize(6));
}

void
JveProject::initSources(void)
{
    /*
    // create history
    //mp_history = new JveHistory(this);

    // set up project models
    mp_rootModel->setUp();
    // set up history
    //mp_history->setProjectLoadedState();
    */

    //------------------------------------------------------------//

    if (isLoadingProcessRejected()) {
        throw JveReport(
            JveReport::Success,
            JveReport::LoadingProjectProcessRejected
        );
    }
}

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

    //------------------------------------------------------------//

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

    //------------------------------------------------------------//

    // update environment
    Jve.setProjectEnv(filePath);


    // TODO rebuild all sources path's for actual project path


    // write data
    QTextStream stream(&projectFile);
    stream << Jve.domDocument().toString(JVE_PROJECT_FILE_XML_INDENT_SIZE);

    // close file
    projectFile.close();

    // set clean state for history
    Jve.history().setUndoStackClean();
    // set clean opened project state
    Jve.setProjectOpenedState();
}

bool
JveProject::isLoadingProcessRejected(void)
{
    bool rejected;

    JveLoadingProjectMutex.lock();
    rejected = Jve.isLoadingProjectProcessRejected();
    JveLoadingProjectMutex.unlock();

    return rejected;
}


