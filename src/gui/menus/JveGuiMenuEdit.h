

#ifndef JVEGUIMENUEDIT_H
#define JVEGUIMENUEDIT_H


#include <QMenu>
#include <QEvent>


#include "../elements/JveGuiAction.h"


class JveGuiMenuEdit : public QMenu
{
    Q_OBJECT
    public:
        explicit  JveGuiMenuEdit(QWidget *parent);
        virtual  ~JveGuiMenuEdit(void);
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
        JveGuiAction actionUndo;
        JveGuiAction actionRedo;
        JveGuiAction actionCut;
        JveGuiAction actionCopy;
        JveGuiAction actionPaste;
        JveGuiAction actionRemove;
        JveGuiAction actionAddProjectSourcesMediaItems;
        JveGuiAction actionAddProjectSourcesImagesSequenceItem;
        JveGuiAction actionPreferences;
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


