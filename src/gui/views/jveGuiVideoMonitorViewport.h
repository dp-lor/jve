

#ifndef JVEGUIVIDEOMONITORVIEWPORT_H
#define JVEGUIVIDEOMONITORVIEWPORT_H


#include <QWidget>
#include <QVBoxLayout>


class QResizeEvent;


class jveGuiVideoMonitorViewport : public QWidget
{
    Q_OBJECT
    public:
        explicit  jveGuiVideoMonitorViewport(QWidget *parent);
        virtual  ~jveGuiVideoMonitorViewport(void);
    protected:
        void resizeEvent(QResizeEvent *event);
    private:
        // members
        QVBoxLayout mp_layout;
        QWidget     mp_frameWrapper;
        QWidget     mp_frame;
        int         mp_originalWidth;
        int         mp_originalHeight;
};


#endif // JVEGUIVIDEOMONITORVIEWPORT_H


