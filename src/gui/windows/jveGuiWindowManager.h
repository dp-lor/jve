

#ifndef JVEGUIWINDOWMANAGER_H
#define JVEGUIWINDOWMANAGER_H


#include <QObject>
#include <QString>


#include "../../core/application/jveReport.h"
#include "../../core/structures/jveProjectSourcesItemStruct.h"


class jveGuiMainWindow;


class jveGuiWindowManager : public QObject
{
    Q_OBJECT
    public:
        explicit  jveGuiWindowManager(void);
        virtual  ~jveGuiWindowManager(void);
    public:
        void populateGui(void);
        void depopulateGui(void);
    private slots:
        void slotQuitAccepted(void);
        void slotStateChanged(const int state);
        void slotShowReport(const jveReport &report);
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
            const jveProjectSourcesItemStruct &itemStruct
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
        jveGuiMainWindow *mp_mainWindow;
};


#endif // JVEGUIWINDOWMANAGER_H


