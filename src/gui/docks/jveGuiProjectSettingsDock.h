

#ifndef JVEGUIPROJECTSETTINGSDOCK_H
#define JVEGUIPROJECTSETTINGSDOCK_H


#include "jveGuiWindowableDock.h"


#include <QScrollArea>


#include "../views/jveGuiProjectSettingsView.h"


class QEvent;


class jveGuiProjectSettingsDock : public jveGuiWindowableDock
{
    Q_OBJECT
    public:
        explicit  jveGuiProjectSettingsDock(QMainWindow *parent);
        virtual  ~jveGuiProjectSettingsDock(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateTranslations(void);
    private:
        // members
        QScrollArea               mp_scrollArea;
        jveGuiProjectSettingsView mp_view;
};


#endif // JVEGUIPROJECTSETTINGSDOCK_H


