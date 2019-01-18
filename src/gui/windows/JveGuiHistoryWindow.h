

#ifndef JVEGUIHISTORYWINDOW_H
#define JVEGUIHISTORYWINDOW_H


#include "JveGuiDockableWindow.h"


class QEvent;


class JveGuiHistoryWindow : public JveGuiDockableWindow
{
    Q_OBJECT
    public:
        explicit  JveGuiHistoryWindow(QWidget *parent);
        virtual  ~JveGuiHistoryWindow(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateTranslations(void);
};


#endif // JVEGUIHISTORYWINDOW_H


