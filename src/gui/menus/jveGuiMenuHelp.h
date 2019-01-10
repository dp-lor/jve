

#ifndef JVEGUIMENUHELP_H
#define JVEGUIMENUHELP_H


#include <QMenu>
#include <QEvent>


#include "../elements/jveGuiAction.h"


class jveGuiMenuHelp : public QMenu
{
    Q_OBJECT
    public:
        explicit  jveGuiMenuHelp(QWidget *parent);
        virtual  ~jveGuiMenuHelp(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateTranslations(void);
    public:
        // members
        jveGuiAction actionKeyboardShortcuts;
        jveGuiAction actionAboutJve;
        jveGuiAction actionAboutQt;
};


#endif // JVEGUIMENUHELP_H


