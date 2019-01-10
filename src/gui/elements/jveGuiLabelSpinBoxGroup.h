

#ifndef JVEGUILABELSPINBOXGROUP_H
#define JVEGUILABELSPINBOXGROUP_H


#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>


#include "jveGuiSpinBox.h"


class jveGuiLabelSpinBoxGroup : public QWidget
{
    Q_OBJECT
    public:
        explicit  jveGuiLabelSpinBoxGroup(QWidget *parent);
        virtual  ~jveGuiLabelSpinBoxGroup(void);
    public:
        // members
        QLabel        label;
        jveGuiSpinBox spinBox;
    private:
        // members
        QHBoxLayout mp_layout;
};


#endif // JVEGUILABELSPINBOXGROUP_H


