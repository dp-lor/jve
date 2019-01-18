

#ifndef JVEGUIMENURECENT_H
#define JVEGUIMENURECENT_H


#include <QMenu>
#include <QEvent>
#include <QString>
#include <QFileInfo>
#include <QStringList>
#include <QList>


#include "../elements/JveGuiAction.h"


class JveGuiMenuRecent : public QMenu
{
    Q_OBJECT
    public:
        explicit  JveGuiMenuRecent(QWidget *parent);
        virtual  ~JveGuiMenuRecent(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void truncateRecentItems(const bool toEmpty = false);
        void updateMenuActionState(void);
        void updateTranslations(void);
    private slots:
        void slotStateChanged(const int state);
        void slotUpdateRecentItems(void);
        void slotAddRecentItem(const QString &projectFilePath);
        void slotCatchWantLoadProject(void);
        void slotClearRecentItems(void);
    private:
        // members
        int                   mp_state;
        QFileInfo             mp_fileInfo;
        QStringList           mp_recentItems;
        QList<JveGuiAction *> mp_recentActions;
        JveGuiAction          mp_actionClear;
};


#endif // JVEGUIMENURECENT_H


