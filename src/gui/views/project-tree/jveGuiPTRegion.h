

#ifndef JVEGUIPTREGION_H
#define JVEGUIPTREGION_H


#include "jveGuiPTItem.h"


class jveGuiPTRegion : public jveGuiPTItem
{
    public:
        explicit jveGuiPTRegion(
            const int          width,
            const int          offset,
                  jveGuiPTItem *parent
        );
        virtual  ~jveGuiPTRegion(void);
    public:
        QRectF boundingRect(void) const;
        void   paint(
                  QPainter                 *painter,
            const QStyleOptionGraphicsItem *option,
                  QWidget                  *widget = Q_NULLPTR
        );
};


#endif // JVEGUIPTREGION_H


