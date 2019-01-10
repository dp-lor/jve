

#ifndef JVEGUITIMESPINBOX_H
#define JVEGUITIMESPINBOX_H


#include <QTimeEdit>
#include <QFocusEvent>


class jveGuiTimeSpinBox : public QTimeEdit
{
    Q_OBJECT
    public:
        explicit  jveGuiTimeSpinBox(QWidget *parent);
        virtual  ~jveGuiTimeSpinBox();
    protected:
        void focusInEvent(QFocusEvent *event);
        void focusOutEvent(QFocusEvent *event);
    signals:
        void wantSetExternalValue(const int frameNumber);
    public slots:
        void setFps(const double fps);
        void setExternalValue(const int frameNumber);
    protected slots:
        void catchEditingFinished(void);
    protected:
        // members
        QTime  mp_timeHelper;
        double mp_fps;
        int    mp_frameNumber;
};


#endif // JVEGUITIMESPINBOX_H


