

#ifndef JVEPROJECT_H
#define JVEPROJECT_H


#include <QString>
#include <QDomDocument>


class jveProjectRootModel;
class jveHistory;

class jveSettingsModel;
class jveSourcesModel;
class jveTreeModel;
class jveStateModel;


class jveProject
{
    public:
        explicit  jveProject(const bool masterMode = false);
        virtual  ~jveProject(void);
    public:
        bool isMaster(void) const;
    public:
        int  state(void) const;
        bool isOpened(void) const;
        bool isNew(void) const;
        bool isHiddenModified(void) const;
        bool isModified(void) const;
    public:
        QString parentDirPath(void) const;
        QString filePath(void) const;
        QString fileName(void) const;
    public:
        jveHistory * history(void);
    public:
        jveSettingsModel * settingsModel(void);
        jveSourcesModel  * sourcesModel(void);
        jveTreeModel     * treeModel(void);
        jveStateModel    * stateModel(void);
    public:
        void setSettingsModel(jveSettingsModel *settingsModel);
        void setSourcesModel(jveSourcesModel *sourcesModel);
        void setTreeModel(jveTreeModel *treeModel);
        void setStateModel(jveStateModel *stateModel);
    public:
        void setHiddenModified(const bool status);
        void setModified(const bool status);
        void updateTranslations(void);
    public:
        void close(void);
        void loadNew(void);
        void load(const QString &filePath);
        void save(const QString &filePath, const bool forceMasterMode = true);
    private:
        void setNewEnv(void);
        void setEnv(const QString &projectFilePath);
        void silentUpdateTranslations(void);
    private:
        // members
        bool mp_masterMode;
        int  mp_state;
        // environment members
        QString mp_parentDirPath;
        QString mp_filePath;
        QString mp_fileName;
        // data members
        QDomDocument         mp_domDocument;
        jveProjectRootModel *mp_rootModel;
        // shared data members
        jveHistory       *mp_history;
        jveSettingsModel *mp_settingsModel;
        jveSourcesModel  *mp_sourcesModel;
        jveTreeModel     *mp_treeModel;
        jveStateModel    *mp_stateModel;
};


#endif // JVEPROJECT_H


