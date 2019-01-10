

#ifndef JVEGUIDOCKTITLEBAR_H
#define JVEGUIDOCKTITLEBAR_H


#include <QWidget>
#include <QHBoxLayout>


#include "jveGuiDockTitleBarTrail.h"


class QEvent;


class jveGuiDockTitleBar : public QWidget
{
    Q_OBJECT
    public:
        explicit  jveGuiDockTitleBar(QWidget *parent);
        virtual  ~jveGuiDockTitleBar(void);
    protected:
        void changeEvent(QEvent *event);
    public:
        void toggleTabifiedMode(const bool toTabified);
    private:
        void updateTranslations(void);
    protected:
        // members
        QHBoxLayout             mp_layout;
        jveGuiDockTitleBarTrail mp_trail;
};


#endif // JVEGUIDOCKTITLEBAR_H


