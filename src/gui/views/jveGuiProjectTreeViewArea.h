

#ifndef JVEGUIPROJECTTREEVIEWAREA_H
#define JVEGUIPROJECTTREEVIEWAREA_H


#include <QGraphicsView>
//#include <QResizeEvent>
//#include <QWheelEvent>


#include "jveGuiProjectTreeViewScene.h"


class jveGuiProjectTreeViewArea : public QGraphicsView
{
    Q_OBJECT
    public:
        explicit  jveGuiProjectTreeViewArea(QWidget *parent);
        virtual  ~jveGuiProjectTreeViewArea();
    private:
        // members
        jveGuiProjectTreeViewScene mp_scene;
};


#endif // JVEGUIPROJECTTREEVIEWAREA_H


