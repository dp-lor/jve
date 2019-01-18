

#ifndef JVEGUIPTREGIONJOINT_H
#define JVEGUIPTREGIONJOINT_H


#include "JveGuiPTItem.h"


class JveGuiPTRegionJoint : public JveGuiPTItem
{
    public:
        explicit  JveGuiPTRegionJoint(JveGuiPTItem *parent);
        virtual  ~JveGuiPTRegionJoint(void);
    public:
        QRectF boundingRect(void) const;
        void   paint(
                  QPainter                 *painter,
            const QStyleOptionGraphicsItem *option,
                  QWidget                  *widget = nullptr
        );
};


#endif // JVEGUIPTREGIONJOINT_H


