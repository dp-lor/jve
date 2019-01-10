

#ifndef JVEGUITWOLABELSGROUP_H
#define JVEGUITWOLABELSGROUP_H


#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>


class jveGuiTwoLabelsGroup : public QWidget
{
    Q_OBJECT
    public:
        explicit  jveGuiTwoLabelsGroup(QWidget *parent);
        virtual  ~jveGuiTwoLabelsGroup(void);
    public:
        // members
        QLabel labelOne;
        QLabel labelTwo;
    private:
        // members
        QHBoxLayout mp_layout;
};


#endif // JVEGUITWOLABELSGROUP_H


