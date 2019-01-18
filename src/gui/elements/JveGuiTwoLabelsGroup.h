

#ifndef JVEGUITWOLABELSGROUP_H
#define JVEGUITWOLABELSGROUP_H


#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>


class JveGuiTwoLabelsGroup : public QWidget
{
    Q_OBJECT
    public:
        explicit  JveGuiTwoLabelsGroup(QWidget *parent);
        virtual  ~JveGuiTwoLabelsGroup(void);
    public:
        // members
        QLabel labelOne;
        QLabel labelTwo;
    private:
        // members
        QHBoxLayout mp_layout;
};


#endif // JVEGUITWOLABELSGROUP_H


