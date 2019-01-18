

#ifndef JVEGUIDOCKTITLEBAR_H
#define JVEGUIDOCKTITLEBAR_H


#include <QWidget>
#include <QHBoxLayout>


#include "JveGuiDockTitleBarTrail.h"


class QEvent;


class JveGuiDockTitleBar : public QWidget
{
    Q_OBJECT
    public:
        explicit  JveGuiDockTitleBar(QWidget *parent);
        virtual  ~JveGuiDockTitleBar(void);
    protected:
        void changeEvent(QEvent *event);
    public:
        void toggleTabifiedMode(const bool toTabified);
    private:
        void updateTranslations(void);
    protected:
        // members
        QHBoxLayout             mp_layout;
        JveGuiDockTitleBarTrail mp_trail;
};


#endif // JVEGUIDOCKTITLEBAR_H


