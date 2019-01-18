

#ifndef JVEGUIHISTORYDOCK_H
#define JVEGUIHISTORYDOCK_H


#include "JveGuiWindowableDock.h"


#include "../views/JveGuiHistoryView.h"


class QEvent;


class JveGuiHistoryDock : public JveGuiWindowableDock
{
    Q_OBJECT
    public:
        explicit  JveGuiHistoryDock(QMainWindow *parent);
        virtual  ~JveGuiHistoryDock(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateTranslations(void);
    private:
        // members
        JveGuiHistoryView mp_view;
};


#endif // JVEGUIHISTORYDOCK_H


