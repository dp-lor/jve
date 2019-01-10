

#ifndef JVEGUIPTREGIONJOINT_H
#define JVEGUIPTREGIONJOINT_H


#include "jveGuiPTItem.h"


class jveGuiPTRegionJoint : public jveGuiPTItem
{
    public:
        explicit  jveGuiPTRegionJoint(jveGuiPTItem *parent);
        virtual  ~jveGuiPTRegionJoint(void);
    public:
        QRectF boundingRect(void) const;
        void   paint(
                  QPainter                 *painter,
            const QStyleOptionGraphicsItem *option,
                  QWidget                  *widget = Q_NULLPTR
        );
};


#endif // JVEGUIPTREGIONJOINT_H


