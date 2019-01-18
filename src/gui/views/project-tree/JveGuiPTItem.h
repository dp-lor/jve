

#ifndef JVEGUIPTITEM_H
#define JVEGUIPTITEM_H


#include <QGraphicsItem>


class JveGuiPTItem : public QGraphicsItem
{
    public:
        explicit  JveGuiPTItem(JveGuiPTItem *parent);
        virtual  ~JveGuiPTItem(void);
    public:
        QRectF boundingRect(void) const;
        void   paint(
                  QPainter                 *painter,
            const QStyleOptionGraphicsItem *option,
                  QWidget                  *widget = nullptr
        );
        int width(void) const;
        int offset(void) const;
    protected:
        // members
        JveGuiPTItem *mp_parent;
        int          mp_width;
        int          mp_offset;
};


#endif // JVEGUIPTITEM_H


