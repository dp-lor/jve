

#ifndef JVEGUIMENUFILE_H
#define JVEGUIMENUFILE_H


#include <QMenu>
#include <QEvent>


#include "../elements/JveGuiAction.h"
#include "JveGuiMenuRecent.h"


class JveGuiMenuFile : public QMenu
{
    Q_OBJECT
    public:
        explicit  JveGuiMenuFile(QWidget *parent);
        virtual  ~JveGuiMenuFile(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateTranslations(void);
    private slots:
        void slotStateChanged(const int state);
    public:
        // members
        JveGuiAction     actionNew;
        JveGuiAction     actionOpen;
        JveGuiMenuRecent menuRecent;
        JveGuiAction     actionSave;
        JveGuiAction     actionSaveAs;
        JveGuiAction     actionRender;
        JveGuiAction     actionClose;
        JveGuiAction     actionExit;
};


#endif // JVEGUIMENUFILE_H


