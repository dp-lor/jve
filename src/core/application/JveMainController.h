

#ifndef JVEMAINCONTROLLER_H
#define JVEMAINCONTROLLER_H


#include <QObject>
#include <QString>
#include <QStringList>


class JveMainController : public QObject
{
    Q_OBJECT
    public:
        explicit  JveMainController(void);
        virtual  ~JveMainController(void);
    private:
        bool isLoadingProjectProcessRejected(void) const;
        void resetLoadingProjectProcess(void);
    private:
        void justCloseProject(void);
        void closeProject(
                const int      options,
                const QString &loadingFilePath
        );
        void loadNewProject(void);
        void loadProject(const QString &loadingFilePath);
        void saveProject(
                const int      options,
                const QString &loadingFilePath,
                const QString &savingFilePath
        );
    private:
        void routeOptions(
            const int      options,
            const QString &loadingFilePath,
            const QString &savingFilePath
        );
    private:
        void addSourcesItems(const QStringList &resourcesList);
    private slots:
        void watchUiChangeEventType(const int eventType);
        void slotQuit(void);
        void slotCloseProject(void);
        void slotLoadNewProject(void);
        void slotLoadProject(const QString &loadingFilePath);
        void slotSaveProject(
                const int      options,
                const QString &loadingFilePath
        );
        void slotSaveProjectAs(const QString &savingFilePath);
        void slotRouteOptions(
                const int      options,
                const QString &loadingFilePath,
                const QString &savingFilePath
        );
    private slots:
        void slotAddSourcesItems(const QStringList &resourcesList);
    private:
        // members
        int mp_loadingProjectProgress;
};


#endif // JVEMAINCONTROLLER_H


