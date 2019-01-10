

#ifndef JVEGUIPROJECTSOURCESDOCK_H
#define JVEGUIPROJECTSOURCESDOCK_H


#include "jveGuiWindowableDock.h"


#include "../views/jveGuiProjectSourcesView.h"


class QEvent;


class jveGuiProjectSourcesDock : public jveGuiWindowableDock
{
    Q_OBJECT
    public:
        explicit  jveGuiProjectSourcesDock(QMainWindow *parent);
        virtual  ~jveGuiProjectSourcesDock(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateTranslations(void);
    private:
        // members
        jveGuiProjectSourcesView mp_view;
};


#endif // JVEGUIPROJECTSOURCESDOCK_H


