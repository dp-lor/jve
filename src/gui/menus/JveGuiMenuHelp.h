

#ifndef JVEGUIMENUHELP_H
#define JVEGUIMENUHELP_H


#include <QMenu>
#include <QEvent>


#include "../elements/JveGuiAction.h"


class JveGuiMenuHelp : public QMenu
{
    Q_OBJECT
    public:
        explicit  JveGuiMenuHelp(QWidget *parent);
        virtual  ~JveGuiMenuHelp(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateTranslations(void);
    public:
        // members
        JveGuiAction actionKeyboardShortcuts;
        JveGuiAction actionAboutJve;
        JveGuiAction actionAboutQt;
};


#endif // JVEGUIMENUHELP_H


