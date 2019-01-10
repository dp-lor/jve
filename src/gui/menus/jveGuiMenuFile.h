

#ifndef JVEGUIMENUFILE_H
#define JVEGUIMENUFILE_H


#include <QMenu>
#include <QEvent>


#include "../elements/jveGuiAction.h"
#include "jveGuiMenuRecent.h"


class jveGuiMenuFile : public QMenu
{
    Q_OBJECT
    public:
        explicit  jveGuiMenuFile(QWidget *parent);
        virtual  ~jveGuiMenuFile(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateTranslations(void);
    private slots:
        void slotStateChanged(const int state);
    public:
        // members
        jveGuiAction     actionNew;
        jveGuiAction     actionOpen;
        jveGuiMenuRecent menuRecent;
        jveGuiAction     actionSave;
        jveGuiAction     actionSaveAs;
        jveGuiAction     actionRender;
        jveGuiAction     actionClose;
        jveGuiAction     actionExit;
};


#endif // JVEGUIMENUFILE_H


