

#ifndef JVEPROJECTSIGNALSPRIVATE_H
#define JVEPROJECTSIGNALSPRIVATE_H


#include <QObject>
#include <QString>


class JveProjectSignalsPrivate : public QObject
{
    Q_OBJECT
    public:
        explicit  JveProjectSignalsPrivate(void);
        virtual  ~JveProjectSignalsPrivate(void);

    signals:

        // global
        void nameChanged(const QString &projectName);
        void loadingProgressUpdated(const int value);
        void loadingProcessCompleted(void);

        // recent
        void wantAddToRecentItems(const QString &filePath);

        // project dialogs
        void wantShowModifiedProjectWarning(
                const int      options,
                const QString &loadingProjectUrl
        );
        void wantShowSaveProjectDialog(
                const int      options           = 0,
                const QString &loadingProjectUrl = nullptr
        );
        void wantShowOpenProjectDialog(void);
        void wantShowLoadingProjectProgress(void);

        // project actions
        void wantCloseProject(void);
        void wantSaveProject(
                const int      options           = 0,
                const QString &loadingProjectUrl = nullptr
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


