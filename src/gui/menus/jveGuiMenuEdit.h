

#ifndef JVEGUIMENUEDIT_H
#define JVEGUIMENUEDIT_H


#include <QMenu>
#include <QEvent>


#include "../elements/jveGuiAction.h"


class jveGuiMenuEdit : public QMenu
{
    Q_OBJECT
    public:
        explicit  jveGuiMenuEdit(QWidget *parent);
        virtual  ~jveGuiMenuEdit(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateState(const int state, const int guiState);
        void updateTranslations(void);
    private slots:
        void slotSetState(const int state);
        void slotSetGuiState(const int state);
        void slotSetHistoryActionsState(
            const bool canUndo,
            const bool canRedo
        );
    public:
        // members
        jveGuiAction actionUndo;
        jveGuiAction actionRedo;
        jveGuiAction actionCut;
        jveGuiAction actionCopy;
        jveGuiAction actionPaste;
        jveGuiAction actionRemove;
        jveGuiAction actionAddProjectSourcesMediaItems;
        jveGuiAction actionAddProjectSourcesImagesSequenceItem;
        jveGuiAction actionPreferences;
    private:
        // members
        int  mp_state;
        int  mp_guiState;
        bool mp_disabled;
        bool mp_canUndo;
        bool mp_canRedo;
        bool mp_canCut;
        bool mp_canCopy;
        bool mp_canPaste;
        bool mp_canRemove;
};


#endif // JVEGUIMENUEDIT_H


