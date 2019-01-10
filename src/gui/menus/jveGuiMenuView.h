

#ifndef JVEGUIMENUVIEW_H
#define JVEGUIMENUVIEW_H


#include <QMenu>
#include <QEvent>
#include <QActionGroup>


#include "../elements/jveGuiAction.h"


class jveGuiMenuView : public QMenu
{
    Q_OBJECT
    public:
        explicit  jveGuiMenuView(QWidget *parent);
        virtual  ~jveGuiMenuView(void);
    protected:
        void changeEvent(QEvent *event);
    public:
        void addTransportBarFeatures(void);
        void addRulerFeatures(void);
        void addToggleStatusBarAction(void);
        void addToggleFullScreenAction(void);
    private:
        void updateTranslations(void);
    private slots:
        void slotSetUpTransportBarFeatures(const bool position);
        void slotSetUpRulerFeatures(const bool checked, const int type);
        void slotResendWantSetTransportBarPosition(QAction *action);
        void slotResendWantToggleRuler(const bool status);
        void slotResendWantSetRulerType(QAction *action);
    public:
        // members
        jveGuiAction actionToggleTransportBar;
        QActionGroup mp_tbPositionGroup;
        jveGuiAction actionTbTop;
        jveGuiAction actionTbBottom;
        jveGuiAction actionToggleRuler;
        QActionGroup mp_rulerTypeGroup;
        jveGuiAction actionRulerTypeTF;
        jveGuiAction actionRulerTypeT;
        jveGuiAction actionRulerTypeF;
        jveGuiAction actionToggleStatusBar;
        jveGuiAction actionToggleFullScreen;
};


#endif // JVEGUIMENUVIEW_H


