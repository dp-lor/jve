

#ifndef JVEPRIVATE_H
#define JVEPRIVATE_H


#include <QString>
#include <QDomDocument>


#include "../history/JveHistory.h"


class JveRootModel;
class JveSettingsModel;
class JveSourcesModel;
class JveTreeModel;
class JveStateModel;


class JvePrivate
{
    public:
        explicit  JvePrivate(void);
        virtual  ~JvePrivate(void);
    public:
        int  state(void) const;
        bool isLoadingProjectProcessRejected(void) const;
        bool isProjectOpened(void) const;
        bool isProjectNew(void) const;
        bool isProjectHiddenModified(void) const;
        bool isProjectModified(void) const;
    public:
        QString projectParentDirPath(void) const;
        QString projectFilePath(void) const;
        QString projectFileName(void) const;
    public:
        qint64 projectFileSize(void) const;
        qint64 resourcesSize(void) const;
        int    resourcesCount(void) const;
    public:
        JveHistory   & history(void);
        QDomDocument & domDocument(void);
    public:
        JveSettingsModel * settingsModel(void);
        JveSourcesModel  * sourcesModel(void);
        JveTreeModel     * treeModel(void);
        JveStateModel    * stateModel(void);
    public:
        void setLoadingProjectProcessRejected(const bool rejected);
        void setProjectClosedState(void);
        void setProjectOpenedState(void);
        void setNewProjectOpenedState(void);
        void setProjectHiddenModifiedState(const bool status);
        void setProjectModifiedState(const bool status);
        void updateProjectNameTranslation(void);
        void setNewProjectEnv(void);
        void setProjectEnv(const QString &filePath);
        void addToResourcesStat(const qint64 size);
    public:
        void clear(void);
        void createAndAttachProjectModels(void);
        void initProjectModels(void);
        void setUpProjectModels(void);
    private:
        // states
        int  mp_state;
        bool mp_loadingProjectProcessRejected;
        // project environment
        QString mp_projectParentDirPath;
        QString mp_projectFilePath;
        QString mp_projectFileName;
        // project counters
        qint64 mp_projectFileSize;
        qint64 mp_resourcesSize;
        int    mp_resourcesCount;
        // undo/redo history
        JveHistory mp_history;
        // project data
        QDomDocument mp_domDocument;
        // project shared objects
        JveRootModel     *mp_rootModel;
        JveSettingsModel *mp_settingsModel;
        JveSourcesModel  *mp_sourcesModel;
        JveTreeModel     *mp_treeModel;
        JveStateModel    *mp_stateModel;
};


#endif // JVEPRIVATE_H


