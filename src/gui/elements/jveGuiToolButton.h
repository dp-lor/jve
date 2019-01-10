

#ifndef JVEGUITOOLBUTTON_H
#define JVEGUITOOLBUTTON_H


#include <QToolButton>
#include <QString>
#include <QPixmap>
#include <QBitmap>


class QEvent;


class jveGuiToolButton : public QToolButton
{
    Q_OBJECT
    public:
        explicit  jveGuiToolButton(QWidget *parent, const QString &iconPath);
        virtual  ~jveGuiToolButton(void);
    protected:
        void changeEvent(QEvent *event);
    protected:
        void updateIcon(void);
    protected:
        // members
        QPixmap mp_pixmap;
        QBitmap mp_mask;
};


#endif // JVEGUITOOLBUTTON_H


