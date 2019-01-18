

#ifndef JVEGUIPROJECTSETTINGSWINDOW_H
#define JVEGUIPROJECTSETTINGSWINDOW_H


#include "JveGuiDockableWindow.h"


class QEvent;


class JveGuiProjectSettingsWindow : public JveGuiDockableWindow
{
    Q_OBJECT
    public:
        explicit  JveGuiProjectSettingsWindow(QWidget *parent);
        virtual  ~JveGuiProjectSettingsWindow(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateTranslations(void);
};


#endif // JVEGUIPROJECTSETTINGSWINDOW_H


