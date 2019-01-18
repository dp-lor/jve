

#ifndef JVEGUIPROJECTSOURCESWINDOW_H
#define JVEGUIPROJECTSOURCESWINDOW_H


#include "JveGuiDockableWindow.h"


class QEvent;


class JveGuiProjectSourcesWindow : public JveGuiDockableWindow
{
    Q_OBJECT
    public:
        explicit  JveGuiProjectSourcesWindow(QWidget *parent);
        virtual  ~JveGuiProjectSourcesWindow(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateTranslations(void);
};


#endif // JVEGUIPROJECTSOURCESWINDOW_H


