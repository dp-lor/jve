

#ifndef JVEGUIPROJECTSOURCESWINDOW_H
#define JVEGUIPROJECTSOURCESWINDOW_H


#include "jveGuiDockableWindow.h"


class QEvent;


class jveGuiProjectSourcesWindow : public jveGuiDockableWindow
{
    Q_OBJECT
    public:
        explicit  jveGuiProjectSourcesWindow(QWidget *parent);
        virtual  ~jveGuiProjectSourcesWindow(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateTranslations(void);
};


#endif // JVEGUIPROJECTSOURCESWINDOW_H


