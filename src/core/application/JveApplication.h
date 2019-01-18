

#ifndef JVEAPPLICATION_H
#define JVEAPPLICATION_H


#include <QObject>
#include <QString>


#include "JveProject.h"


class JveApplication : public QObject
{
    Q_OBJECT
    public:
        explicit  JveApplication(void);
        virtual  ~JveApplication(void);
    public:
        bool isProjectOpened(void) const;
        bool isProjectNew(void) const;
        bool isProjectHiddenModified(void) const;
        bool isProjectModified(void) const;
    public:
        void setProjectClosedState(void);
        void setProjectOpenedState(void);
        void setNewProjectOpenedState(void);
        void setProjectHiddenModifiedState(const bool status);
        void setProjectModifiedState(const bool status);
    private:
        void justCloseProject(void);
        void closeProject(
                const int      options,
                const QString &loadingProjectUrl
        );
        void loadNewProject(void);
        void loadProject(const QString &loadingProjectUrl);
        void saveProject(
                const int      options,
                const QString &loadingProjectUrl,
                const QString &savingProjectUrl
        );
    private:
        void routeOptions(
            const int      options,
            const QString &loadingProjectUrl,
            const QString &savingProjectUrl
        );
    private slots:
        void watchUiChangeEventType(const int eventType);
        void slotExit(void);
        void slotCloseProject(void);
        void slotLoadNewProject(void);
        void slotLoadProject(const QString &loadingProjectUrl);
        void slotSaveProject(
                const int      options,
                const QString &loadingProjectUrl
        );
        void slotSaveProjectAs(const QString &savingProjectUrl);
        void slotRouteOptions(
                const int      options,
                const QString &loadingProjectUrl,
                const QString &savingProjectUrl
        );
    private:
        // members
        int        mp_state;
        JveProject mp_project;
};


#endif // JVEAPPLICATION_H


