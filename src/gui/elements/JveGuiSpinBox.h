

#ifndef JVEGUISPINBOX_H
#define JVEGUISPINBOX_H


#include <QSpinBox>
#include <QFocusEvent>


class JveGuiSpinBox : public QSpinBox
{
    Q_OBJECT
    public:
        explicit  JveGuiSpinBox(QWidget *parent);
        virtual  ~JveGuiSpinBox();
    protected:
        void focusInEvent(QFocusEvent *event);
        void focusOutEvent(QFocusEvent *event);
    signals:
        void wantSetExternalValue(const int value);
    public slots:
        void setExternalValue(const int value);
    protected slots:
        void catchEditingFinished(void);
};


#endif // JVEGUISPINBOX_H


