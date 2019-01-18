

#ifndef JVEGUILABELSPINBOXGROUP_H
#define JVEGUILABELSPINBOXGROUP_H


#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>


#include "JveGuiSpinBox.h"


class JveGuiLabelSpinBoxGroup : public QWidget
{
    Q_OBJECT
    public:
        explicit  JveGuiLabelSpinBoxGroup(QWidget *parent);
        virtual  ~JveGuiLabelSpinBoxGroup(void);
    public:
        // members
        QLabel        label;
        JveGuiSpinBox spinBox;
    private:
        // members
        QHBoxLayout mp_layout;
};


#endif // JVEGUILABELSPINBOXGROUP_H


