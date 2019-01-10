

#ifndef JVEGUIHISTORYWINDOW_H
#define JVEGUIHISTORYWINDOW_H


#include "jveGuiDockableWindow.h"


class QEvent;


class jveGuiHistoryWindow : public jveGuiDockableWindow
{
    Q_OBJECT
    public:
        explicit  jveGuiHistoryWindow(QWidget *parent);
        virtual  ~jveGuiHistoryWindow(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateTranslations(void);
};


#endif // JVEGUIHISTORYWINDOW_H


