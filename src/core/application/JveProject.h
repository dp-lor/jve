

#ifndef JVEPROJECT_H
#define JVEPROJECT_H


#include <QString>
#include <QDomDocument>


class JveApplication;

class JveProjectRootModel;
class JveHistory;

class JveSettingsModel;
class JveSourcesModel;
class JveTreeModel;
class JveStateModel;


class JveProject
{
    public:
        explicit  JveProject(JveApplication *app = nullptr);
        virtual  ~JveProject(void);
    public:
        bool isMater(void) const;
    public:
        QString parentDirPath(void) const;
        QString filePath(void) const;
        QString fileName(void) const;
    public:
        QDomDocument & domDocument(void);
    public:
        JveHistory * history(void);
    public:
        JveSettingsModel * settingsModel(void);
        JveSourcesModel  * sourcesModel(void);
        JveTreeModel     * treeModel(void);
        JveStateModel    * stateModel(void);
    public:
        void setSettingsModel(JveSettingsModel *settingsModel);
        void setSourcesModel(JveSourcesModel *sourcesModel);
        void setTreeModel(JveTreeModel *treeModel);
        void setStateModel(JveStateModel *stateModel);
    public:
        void setHiddenModified(const bool status);
        void setModified(const bool status);
        void updateTranslations(void);
    public:
        void close(void);
        void loadNew(void);
        void load(const QString &filePath);
        void save(const QString &filePath);
    private:
        void setNewEnv(void);
        void setEnv(const QString &projectFilePath);
    private:
        // members
        JveApplication *mp_app;
        bool            mp_masterMode;
        // environment members
        QString mp_parentDirPath;
        QString mp_filePath;
        QString mp_fileName;
        // data members
        QDomDocument         mp_domDocument;
        JveProjectRootModel *mp_rootModel;
        // shared data members
        JveHistory       *mp_history;
        JveSettingsModel *mp_settingsModel;
        JveSourcesModel  *mp_sourcesModel;
        JveTreeModel     *mp_treeModel;
        JveStateModel    *mp_stateModel;
};


#endif // JVEPROJECT_H


