

#ifndef JVEGUIPROJECTSETTINGSDOCK_H
#define JVEGUIPROJECTSETTINGSDOCK_H


#include "JveGuiWindowableDock.h"


#include <QScrollArea>


#include "../views/JveGuiProjectSettingsView.h"


class QEvent;


class JveGuiProjectSettingsDock : public JveGuiWindowableDock
{
    Q_OBJECT
    public:
        explicit  JveGuiProjectSettingsDock(QMainWindow *parent);
        virtual  ~JveGuiProjectSettingsDock(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateTranslations(void);
    private:
        // members
        QScrollArea               mp_scrollArea;
        JveGuiProjectSettingsView mp_view;
};


#endif // JVEGUIPROJECTSETTINGSDOCK_H


