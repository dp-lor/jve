

#ifndef JVEGUIPROJECTSETTINGSWINDOW_H
#define JVEGUIPROJECTSETTINGSWINDOW_H


#include "jveGuiDockableWindow.h"


class QEvent;


class jveGuiProjectSettingsWindow : public jveGuiDockableWindow
{
    Q_OBJECT
    public:
        explicit  jveGuiProjectSettingsWindow(QWidget *parent);
        virtual  ~jveGuiProjectSettingsWindow(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateTranslations(void);
};


#endif // JVEGUIPROJECTSETTINGSWINDOW_H


