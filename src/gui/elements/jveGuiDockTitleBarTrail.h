

#ifndef JVEGUIDOCKTITLEBARTRAIL_H
#define JVEGUIDOCKTITLEBARTRAIL_H


#include <QWidget>
#include <QPixmap>
#include <QBitmap>


class QEvent;
class QPaintEvent;


class jveGuiDockTitleBarTrail : public QWidget
{
    Q_OBJECT
    public:
        explicit  jveGuiDockTitleBarTrail(QWidget *parent);
        virtual  ~jveGuiDockTitleBarTrail(void);
    protected:
        void changeEvent(QEvent *event);
        void paintEvent(QPaintEvent *event);
    protected:
        void updateTrailColor(void);
    protected:
        // members
        QPixmap mp_pixmap;
        QBitmap mp_mask;
        QBrush  mp_brush;
};


#endif // JVEGUIDOCKTITLEBARTRAIL_H


