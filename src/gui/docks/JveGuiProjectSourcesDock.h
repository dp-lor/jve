

#ifndef JVEGUIPROJECTSOURCESDOCK_H
#define JVEGUIPROJECTSOURCESDOCK_H


#include "JveGuiWindowableDock.h"


#include "../views/JveGuiProjectSourcesView.h"


class QEvent;


class JveGuiProjectSourcesDock : public JveGuiWindowableDock
{
    Q_OBJECT
    public:
        explicit  JveGuiProjectSourcesDock(QMainWindow *parent);
        virtual  ~JveGuiProjectSourcesDock(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateTranslations(void);
    private:
        // members
        JveGuiProjectSourcesView mp_view;
};


#endif // JVEGUIPROJECTSOURCESDOCK_H


