

#ifndef JVEPROJECTSIGNALSPRIVATE_H
#define JVEPROJECTSIGNALSPRIVATE_H


#include <QObject>
#include <QString>


class jveProjectSignalsPrivate : public QObject
{
    Q_OBJECT
    public:
        explicit  jveProjectSignalsPrivate(void);
        virtual  ~jveProjectSignalsPrivate(void);

    signals:

        // global
        void projectNameChanged(const QString &projectName);
        void wantAddProjectUrlToRecentItems(const QString &recentProjectUrl);

        // project dialogs
        void wantShowModifiedProjectWarning(
                const int      options,
                const QString &loadingProjectUrl
        );
        void wantShowSaveProjectDialog(
                const int      options           = 0,
                const QString &loadingProjectUrl = Q_NULLPTR
        );
        void wantShowOpenProjectDialog(void);

        // project actions
        void wantCloseProject(void);
        void wantSaveProject(
                const int      options           = 0,
                const QString &loadingProjectUrl = Q_NULLPTR
        );
        void wantSaveProjectAs(const QString &savingProjectUrl);
        void wantLoadNewProject(void);
        void wantLoadProject(const QString &loadingProjectUrl);
        void wantRouteOptions(
                const int      options,
                const QString &loadingProjectUrl,
                const QString &savingProjectUrl
        );

        // render project context
        void wantRenderProject(void);
        void wantShowRenderProjectDialog(void);
};


#endif // JVEPROJECTSIGNALSPRIVATE_H


