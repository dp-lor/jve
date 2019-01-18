

#ifndef JVEGUIVIDEOMONITORVIEWPORT_H
#define JVEGUIVIDEOMONITORVIEWPORT_H


#include <QWidget>
#include <QVBoxLayout>


class QResizeEvent;


class JveGuiVideoMonitorViewport : public QWidget
{
    Q_OBJECT
    public:
        explicit  JveGuiVideoMonitorViewport(QWidget *parent);
        virtual  ~JveGuiVideoMonitorViewport(void);
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


