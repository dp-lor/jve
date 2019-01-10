

#ifndef JVEGUIHISTORYDOCK_H
#define JVEGUIHISTORYDOCK_H


#include "jveGuiWindowableDock.h"


#include "../views/jveGuiHistoryView.h"


class QEvent;


class jveGuiHistoryDock : public jveGuiWindowableDock
{
    Q_OBJECT
    public:
        explicit  jveGuiHistoryDock(QMainWindow *parent);
        virtual  ~jveGuiHistoryDock(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateTranslations(void);
    private:
        // members
        jveGuiHistoryView mp_view;
};


#endif // JVEGUIHISTORYDOCK_H


