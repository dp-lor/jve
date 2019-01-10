

#ifndef JVEGUILABELCOMBOBOXGROUP_H
#define JVEGUILABELCOMBOBOXGROUP_H


#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>


class jveGuiLabelComboBoxGroup : public QWidget
{
    Q_OBJECT
    public:
        explicit  jveGuiLabelComboBoxGroup(QWidget *parent);
        virtual  ~jveGuiLabelComboBoxGroup(void);
    public:
        // members
        QLabel    label;
        QComboBox comboBox;
    private:
        // members
        QHBoxLayout mp_layout;
};


#endif // JVEGUILABELCOMBOBOXGROUP_H


