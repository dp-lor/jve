

#ifndef JVEGUIWINDOWMANAGER_H
#define JVEGUIWINDOWMANAGER_H


#include <QObject>
#include <QString>


#include "../../core/application/JveReport.h"
#include "../../core/structures/JveSourcesItemStruct.h"


class JveGuiMainWindow;


class JveGuiWindowManager : public QObject
{
    Q_OBJECT
    public:
        explicit  JveGuiWindowManager(void);
        virtual  ~JveGuiWindowManager(void);
    public:
        void populateGui(void);
        void depopulateGui(void);
    private slots:
        void slotQuitAccepted(void);
        void slotStateChanged(const int state);
        void slotShowReport(const JveReport &report);
        void slotShowModifiedProjectWarning(
                const int      options,
                const QString &loadingProjectUrl
        );
        void slotShowSaveProjectDialog(
                const int      options,
                const QString &loadingProjectUrl
        );
        void slotShowOpenProjectDialog(void);
        void slotShowAddProjectSourcesMediaItemsDialog(void);
        void slotShowAddProjectSourcesImagesSequenceItemDialog(void);
        void slotShowProjectSourcesItemPropertiesDialog(
            const JveSourcesItemStruct &itemStruct
        );
        void slotShowPreferencesDialog(void);
        void slotShowKeyboardShortcutsInfo(void);
        void slotShowAboutJveDialog(void);
    private:
        // members
        bool mp_isPopulated;
        bool mp_isBusy;
    private:
        // members
        JveGuiMainWindow *mp_mainWindow;
};


#endif // JVEGUIWINDOWMANAGER_H


