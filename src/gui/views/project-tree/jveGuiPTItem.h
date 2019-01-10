

#ifndef JVEGUIPTITEM_H
#define JVEGUIPTITEM_H


#include <QGraphicsItem>


class jveGuiPTItem : public QGraphicsItem
{
    public:
        explicit  jveGuiPTItem(jveGuiPTItem *parent);
        virtual  ~jveGuiPTItem(void);
    public:
        QRectF boundingRect(void) const;
        void   paint(
                  QPainter                 *painter,
            const QStyleOptionGraphicsItem *option,
                  QWidget                  *widget = Q_NULLPTR
        );
        int width(void) const;
        int offset(void) const;
    protected:
        // members
        jveGuiPTItem *mp_parent;
        int          mp_width;
        int          mp_offset;
};


#endif // JVEGUIPTITEM_H


