

#ifndef JVEGUIMENURECENT_H
#define JVEGUIMENURECENT_H


#include <QMenu>
#include <QEvent>
#include <QString>
#include <QFileInfo>
#include <QStringList>
#include <QList>


#include "../elements/jveGuiAction.h"


class jveGuiMenuRecent : public QMenu
{
    Q_OBJECT
    public:
        explicit  jveGuiMenuRecent(QWidget *parent);
        virtual  ~jveGuiMenuRecent(void);
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
        QList<jveGuiAction *> mp_recentActions;
        jveGuiAction          mp_actionClear;
};


#endif // JVEGUIMENURECENT_H


