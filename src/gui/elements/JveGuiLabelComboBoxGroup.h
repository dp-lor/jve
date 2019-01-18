

#ifndef JVEGUILABELCOMBOBOXGROUP_H
#define JVEGUILABELCOMBOBOXGROUP_H


#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>


class JveGuiLabelComboBoxGroup : public QWidget
{
    Q_OBJECT
    public:
        explicit  JveGuiLabelComboBoxGroup(QWidget *parent);
        virtual  ~JveGuiLabelComboBoxGroup(void);
    public:
        // members
        QLabel    label;
        QComboBox comboBox;
    private:
        // members
        QHBoxLayout mp_layout;
};


#endif // JVEGUILABELCOMBOBOXGROUP_H


