

#ifndef JVEGUIPROJECTTREEVIEWAREA_H
#define JVEGUIPROJECTTREEVIEWAREA_H


#include <QGraphicsView>
//#include <QResizeEvent>
//#include <QWheelEvent>


#include "JveGuiProjectTreeViewScene.h"


class JveGuiProjectTreeViewArea : public QGraphicsView
{
    Q_OBJECT
    public:
        explicit  JveGuiProjectTreeViewArea(QWidget *parent);
        virtual  ~JveGuiProjectTreeViewArea();
    private:
        // members
        JveGuiProjectTreeViewScene mp_scene;
};


#endif // JVEGUIPROJECTTREEVIEWAREA_H


