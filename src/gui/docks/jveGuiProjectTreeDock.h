

#ifndef JVEGUIPROJECTTREEDOCK_H
#define JVEGUIPROJECTTREEDOCK_H


#include "jveGuiDock.h"
#include "../views/jveGuiProjectTreeView.h"


class QAction;


class jveGuiProjectTreeDock : public jveGuiDock
{
    Q_OBJECT
    public:
        explicit  jveGuiProjectTreeDock(QMainWindow *parent);
        virtual  ~jveGuiProjectTreeDock(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateTranslations(void);
    private:
        // members
        jveGuiProjectTreeView mp_view;
};


#endif // JVEGUIPROJECTTREEDOCK_H


