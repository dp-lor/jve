

#ifndef JVEAPPLICATION_H
#define JVEAPPLICATION_H


#include <QObject>
#include <QString>


#include "jveProject.h"


class jveApplication : public QObject
{
    Q_OBJECT
    public:
        explicit  jveApplication(void);
        virtual  ~jveApplication(void);
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
        jveProject mp_project;
};


#endif // JVEAPPLICATION_H


