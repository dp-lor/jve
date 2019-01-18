

#ifndef JVEGUITIMEFRAMESSPINSGROUP_H
#define JVEGUITIMEFRAMESSPINSGROUP_H


#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>


#include "JveGuiTimeSpinBox.h"
#include "JveGuiFramesSpinBox.h"


class JveGuiTimeFramesSpinsGroup : public QWidget
{
    Q_OBJECT
    public:
        explicit  JveGuiTimeFramesSpinsGroup(QWidget *parent);
        virtual  ~JveGuiTimeFramesSpinsGroup(void);
    public:
        void resetSpins(void);
    public:
        // members
        JveGuiTimeSpinBox   timeSpin;
        JveGuiFramesSpinBox framesSpin;
    private:
        // members
        QHBoxLayout mp_layout;
        QLabel      mp_betweenLabel;
};


#endif // JVEGUITIMEFRAMESSPINSGROUP_H


