

#ifndef JVEGUITIMEFRAMESSPINSGROUP_H
#define JVEGUITIMEFRAMESSPINSGROUP_H


#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>


#include "jveGuiTimeSpinBox.h"
#include "jveGuiFramesSpinBox.h"


class jveGuiTimeFramesSpinsGroup : public QWidget
{
    Q_OBJECT
    public:
        explicit  jveGuiTimeFramesSpinsGroup(QWidget *parent);
        virtual  ~jveGuiTimeFramesSpinsGroup(void);
    public:
        void resetSpins(void);
    public:
        // members
        jveGuiTimeSpinBox   timeSpin;
        jveGuiFramesSpinBox framesSpin;
    private:
        // members
        QHBoxLayout mp_layout;
        QLabel      mp_betweenLabel;
};


#endif // JVEGUITIMEFRAMESSPINSGROUP_H


