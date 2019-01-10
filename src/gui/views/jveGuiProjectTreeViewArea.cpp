

#include "jveGuiProjectTreeViewArea.h"


jveGuiProjectTreeViewArea::jveGuiProjectTreeViewArea(QWidget *parent)
    : QGraphicsView(parent),
        mp_scene(this)
{
    // properties
    setFocusPolicy(Qt::NoFocus);
    setSizePolicy(
        QSizePolicy::Expanding,
        QSizePolicy::Expanding
    );
    setAlignment(Qt::AlignLeft | Qt::AlignTop);

    // surface properties
    setRenderHint(QPainter::Antialiasing, false);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    //setDragMode(QGraphicsView::RubberBandDrag);
    //setOptimizationFlags(QGraphicsView::DontSavePainterState); // ???
    setViewportUpdateMode(QGraphicsView::SmartViewportUpdate); // ???

    setScene(&mp_scene);
}

jveGuiProjectTreeViewArea::~jveGuiProjectTreeViewArea()
{
}


