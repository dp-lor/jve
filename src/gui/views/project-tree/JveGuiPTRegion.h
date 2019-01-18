

#ifndef JVEGUIPTREGION_H
#define JVEGUIPTREGION_H


#include "JveGuiPTItem.h"


class JveGuiPTRegion : public JveGuiPTItem
{
    public:
        explicit JveGuiPTRegion(
            const int          width,
            const int          offset,
                  JveGuiPTItem *parent
        );
        virtual  ~JveGuiPTRegion(void);
    public:
        QRectF boundingRect(void) const;
        void   paint(
                  QPainter                 *painter,
            const QStyleOptionGraphicsItem *option,
                  QWidget                  *widget = nullptr
        );
};


#endif // JVEGUIPTREGION_H


