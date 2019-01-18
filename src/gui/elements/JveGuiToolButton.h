

#ifndef JVEGUITOOLBUTTON_H
#define JVEGUITOOLBUTTON_H


#include <QToolButton>
#include <QString>
#include <QPixmap>
#include <QBitmap>


class QEvent;


class JveGuiToolButton : public QToolButton
{
    Q_OBJECT
    public:
        explicit  JveGuiToolButton(QWidget *parent, const QString &iconPath);
        virtual  ~JveGuiToolButton(void);
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


