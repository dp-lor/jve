

#ifndef JVEGUIPROJECTTREEDOCK_H
#define JVEGUIPROJECTTREEDOCK_H


#include "JveGuiDock.h"
#include "../views/JveGuiProjectTreeView.h"


class QAction;


class JveGuiProjectTreeDock : public JveGuiDock
{
    Q_OBJECT
    public:
        explicit  JveGuiProjectTreeDock(QMainWindow *parent);
        virtual  ~JveGuiProjectTreeDock(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateTranslations(void);
    private:
        // members
        JveGuiProjectTreeView mp_view;
};


#endif // JVEGUIPROJECTTREEDOCK_H


