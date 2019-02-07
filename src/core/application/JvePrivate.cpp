

#include "JvePrivate.h"


#include <QFileInfo>
#include <QDir>


#include "../definitions/JveState.h"

#include "../mutexes/JveLocalizationMutex.h"

#include "../localization/JveTranslation.h"
#include "../localization/JveTr.h"

#include "../models/JveRootModel.h"


JvePrivate Jve;


JvePrivate::JvePrivate(void)
    : mp_state(JveState::None),
        mp_loadingProjectProcessRejected(false),
        mp_projectParentDirPath(),
        mp_projectFilePath(),
        mp_projectFileName(),
        mp_projectFileSize(0),
        mp_resourcesSize(0),
        mp_resourcesCount(0),
        mp_history(),
        mp_domDocument(),
        mp_rootModel(nullptr),
        mp_settingsModel(nullptr),
        mp_sourcesModel(nullptr),
        mp_treeModel(nullptr),
        mp_stateModel(nullptr)
{
}

JvePrivate::~JvePrivate(void)
{
}

int
JvePrivate::state(void) const
{
    return mp_state;
}

bool
JvePrivate::isLoadingProjectProcessRejected(void) const
{
    return mp_loadingProjectProcessRejected;
}

bool
JvePrivate::isProjectOpened(void) const
{
    return (mp_state & JveState::ProjectOpened);
}

bool
JvePrivate::isProjectNew(void) const
{
    return (mp_state & JveState::ProjectNew);
}

bool
JvePrivate::isProjectHiddenModified(void) const
{
    return (mp_state & JveState::ProjectHiddenModified);
}

bool
JvePrivate::isProjectModified(void) const
{
    return (mp_state & JveState::ProjectModified);
}

QString
JvePrivate::projectParentDirPath(void) const
{
    return mp_projectParentDirPath;
}

QString
JvePrivate::projectFilePath(void) const
{
    return mp_projectFilePath;
}

QString
JvePrivate::projectFileName(void) const
{
    return mp_projectFileName;
}

qint64
JvePrivate::projectFileSize(void) const
{
    return mp_projectFileSize;
}

qint64
JvePrivate::resourcesSize(void) const
{
    return mp_resourcesSize;
}

int
JvePrivate::resourcesCount(void) const
{
    return mp_resourcesCount;
}

JveHistory &
JvePrivate::history(void)
{
    return mp_history;
}

QDomDocument &
JvePrivate::domDocument(void)
{
    return mp_domDocument;
}

JveSettingsModel *
JvePrivate::settingsModel(void)
{
    return mp_settingsModel;
}

JveSourcesModel *
JvePrivate::sourcesModel(void)
{
    return mp_sourcesModel;
}

JveTreeModel *
JvePrivate::treeModel(void)
{
    return mp_treeModel;
}

JveStateModel *
JvePrivate::stateModel(void)
{
    return mp_stateModel;
}

void
JvePrivate::setLoadingProjectProcessRejected(const bool rejected)
{
    mp_loadingProjectProcessRejected = rejected;
}

void
JvePrivate::setProjectClosedState(void)
{
    mp_state &= ~(
        JveState::ProjectModified
            | JveState::ProjectHiddenModified
            | JveState::ProjectNew
            | JveState::ProjectOpened
    );
}

void
JvePrivate::setProjectOpenedState(void)
{
    mp_state = JveState::ProjectOpened;
}

void
JvePrivate::setNewProjectOpenedState(void)
{
    mp_state = (JveState::ProjectOpened | JveState::ProjectNew);
}

void
JvePrivate::setProjectHiddenModifiedState(const bool status)
{
    if (status) {
        mp_state |=  JveState::ProjectHiddenModified;
    } else {
        mp_state &= ~JveState::ProjectHiddenModified;
    }
}

void
JvePrivate::setProjectModifiedState(const bool status)
{
    if (status) {
        mp_state |=  JveState::ProjectModified;
    } else {
        mp_state &= ~JveState::ProjectModified;
    }
}

void
JvePrivate::updateProjectNameTranslation(void)
{
    JveLocalizationMutex.lock();
    mp_projectFileName = JveTr.textAt(JveTranslation::NewProjectName);
    JveLocalizationMutex.unlock();
}

void
JvePrivate::setNewProjectEnv(void)
{
    // TODO https://stackoverflow.com/a/28052962/3558278
    QFileInfo info(QDir::currentPath());

    mp_projectParentDirPath = info.absoluteDir().path();
    mp_projectFilePath      = info.absoluteFilePath();

    updateProjectNameTranslation();

    mp_projectFileSize = 0;
}

void
JvePrivate::setProjectEnv(const QString &filePath)
{
    QFileInfo info(filePath);

    mp_projectParentDirPath = info.absoluteDir().path();
    mp_projectFilePath      = info.absoluteFilePath();
    mp_projectFileName      = info.fileName();
    mp_projectFileSize      = info.size();
}

void
JvePrivate::addToResourcesStat(const qint64 size)
{
    mp_resourcesSize  += size;
    mp_resourcesCount += 1;
}

void
JvePrivate::clear(void)
{
    if (nullptr != mp_rootModel) {

        delete mp_rootModel;

        mp_rootModel     = nullptr;
        mp_settingsModel = nullptr;
        mp_sourcesModel  = nullptr;
        mp_treeModel     = nullptr;
        mp_stateModel    = nullptr;

    }

    mp_history     .clear();
    mp_domDocument .clear();

    mp_projectFileSize = 0;
    mp_resourcesSize   = 0;
    mp_resourcesCount  = 0;

    mp_projectParentDirPath .clear();
    mp_projectFilePath      .clear();
    mp_projectFileName      .clear();
}

void
JvePrivate::createAndAttachProjectModels(void)
{
    mp_rootModel = new JveRootModel(mp_domDocument.documentElement());

    mp_settingsModel = mp_rootModel->settingsModel();
    mp_sourcesModel  = mp_rootModel->sourcesModel();
    mp_treeModel     = mp_rootModel->treeModel();
    mp_stateModel    = mp_rootModel->stateModel();
}

void
JvePrivate::initProjectModels(void)
{
    //mp_sourcesModel  ->init();
    //mp_treeModel     ->init();
    //mp_stateModel    ->init();
}

void
JvePrivate::setUpProjectModels(void)
{
    mp_rootModel->setUp();
}


