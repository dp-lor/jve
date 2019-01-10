

#ifndef JVEAPPLICATION_H
#define JVEAPPLICATION_H


#include <QObject>
#include <QString>
#include <QDomDocument>


class jveHistory;
class jveProject;
class jveProjectSettings;
class jveProjectState;
class jveProjectSources;


class jveApplication : public QObject
{
    Q_OBJECT
    public:
        explicit  jveApplication(void);
        virtual  ~jveApplication(void);
    public:
        jveHistory * history(void);
    public:
        void setHistory(jveHistory *history);
    public:
        jveProjectSettings * projectSettings(void);
        jveProjectState    * projectState(void);
        jveProjectSources  * projectSources(void);
    public:
        void setProjectHiddenModified(const bool status);
        void setProjectModified(const bool status);
    public:
        void setProjectSettings(jveProjectSettings *settings);
        void setProjectState(jveProjectState *state);
        void setProjectSources(jveProjectSources *sources);
    public:
        QString projectDirPath(void) const;
    private:
        void clear(void);
        void setProjectFileEnv(const QString &projectFilePath);
        void closeProjectProcess(void);
        void saveProjectProcess(const QString &savingProjectUrl);
        void loadProjectProcess(const QString &loadingProjectUrl);
        void closeProject(
                const int      options,
                const QString &loadingProjectUrl
        );
        void saveProject(
                const int      options,
                const QString &loadingProjectUrl,
                const QString &savingProjectUrl
        );
        void loadProject(const QString &loadingProjectUrl);
        void loadNewProject(void);
        void routeOptions(
            const int      options,
            const QString &loadingProjectUrl,
            const QString &savingProjectUrl
        );
    public slots:
        void watchUiChangeEventType(const int eventType);
    private slots:
        void slotExit(void);
        void slotCloseProject(void);
        void slotSaveProject(
                const int      options,
                const QString &loadingProjectUrl
        );
        void slotSaveProjectAs(const QString &savingProjectUrl);
        void slotLoadNewProject(void);
        void slotLoadProject(const QString &loadingProjectUrl);
        void slotRouteOptions(
                const int      options,
                const QString &loadingProjectUrl,
                const QString &savingProjectUrl
        );
    private:
        // members
        jveHistory *mp_history;
        int         mp_state;
        // project environment members
        QString mp_projectDirPath;
        QString mp_projectFilePath;
        QString mp_projectName;
        // project data members
        QDomDocument  mp_projectDom;
        jveProject   *mp_project;
        // project data shared members
        jveProjectSettings *mp_projectSettings;
        jveProjectState    *mp_projectState;
        jveProjectSources  *mp_projectSources;
};


#endif // JVEAPPLICATION_H


